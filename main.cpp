#include <QApplication>
#include "renderHTML.cpp"  // Include the file that contains the MainWindow definition
#include "parser.cpp"
// #include "lex.cpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "nlhomann.hpp"
#include "fetch_html.cpp"
#include <QThread>
#include <QProcess>
#include <QSettings>

#define BUFFER_SIZE 1024
using json = nlohmann::json;

/// @brief Function used to create the token from input file. 
extern int yylex(void);
extern FILE *yyin;

/// @brief Function used to parse the input token and creates the AST.
extern int yyparse(void);

/// @brief Function returns the root Node of the AST after the completion of parsing.
/// @return Object of Node.
extern Node* getRoot();

Node* Root;
int parentSocket;

int parentToChild1[2], child1ToChild2[2], child2ToParent[2];

class FetchHtmlWorker : public QObject {
    // Q_OBJECT

public:
    FetchHtmlWorker(int socket_fd, int parentSocket, QObject *parent = nullptr)
        : QObject(parent), socket_fd(socket_fd), parentSocket(parentSocket) {}
     ~FetchHtmlWorker() override {};

public slots:
    void run() {
        fetch_html_and_send(socket_fd, parentSocket);
    }


private:
    int socket_fd;
    int parentSocket;

    void fetch_html_and_send(int socket_fd, int parentSocket) {
        char buff[1024];
        ssize_t s;
        if ((s = read(parentSocket, &buff, sizeof(buff))) == -1) {
            perror("read");
            return;
        }
        buff[s] = '\0';  // Null-terminate the string
        std::string url(buff);  // Convert to std::string

        std::cout << "url to be used: " << url << std::endl;

        std::string pageName = url.substr(url.find_last_of('/') + 1);
        if (pageName.empty() || pageName.find('.') == std::string::npos) {
            pageName = "index"; // Default to 'index' if no file name is present
        } else {
            pageName = pageName.substr(0, pageName.find_last_of('.')); // Remove extension
        }

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Failed to fetch " << url << ": " << curl_easy_strerror(res) << std::endl;
                readBuffer = notFound;
            } else {
                std::cout << "Fetched and cached: " << pageName << std::endl;
                std::cout << "Content of " << pageName << ":\n" << readBuffer << "\n\n";

                if(readBuffer.find("Error response") != std::string::npos){
                readBuffer = notFound;
            }
            }
            
            curl_easy_cleanup(curl);
        }

        std::string html_content = readBuffer;
        size_t content_length = html_content.size();
        size_t total_sent = 0;

        if (write(socket_fd, &content_length, sizeof(content_length)) == -1) {
            perror("write");
            return;
        }

        while (total_sent < content_length) {
            size_t chunk_size = 1024;
            if (content_length - total_sent < 1024) {
                chunk_size = content_length - total_sent; // Adjust chunk size for the last chunk
            }

            if (write(socket_fd, html_content.c_str() + total_sent, chunk_size) < 0) {
                perror("Error writing to socket");
                exit(1);
            }

            total_sent += chunk_size;
        }

        std::cout << "Child (PID: " << total_sent << ") sent the entire HTML content from the file through the socket" << std::endl;

    }
};


class NetworkWorker : public QObject {
    // Q_OBJECT

public:
    NetworkWorker(int socket_fd, int parentSocket, QObject *parent = nullptr)
        : QObject(parent), socket_fd(socket_fd), parentSocket(parentSocket) {}

public slots:
    void runSendData(const std::string& data) {
        sendData(socket_fd, data);
    }

    void runReceiveAndParseHtml() {
        receive_and_parse_html(socket_fd, parentSocket);
    }

signals:
    void finished();  // Signal to indicate task is complete

private:
    int socket_fd;
    int parentSocket;

    void sendData(int socket, const std::string& data) {
        size_t dataSize = data.size();
        if (write(socket, &dataSize, sizeof(dataSize)) == -1) {
            perror("write");
            return;
        }
        qDebug() << "Size sent to socket: " << dataSize;
        
        size_t bytesSent = 0;
        while (bytesSent < dataSize) {
            size_t chunkSize = std::min<size_t>(4096, dataSize - bytesSent);
            if (write(socket, data.c_str() + bytesSent, chunkSize) == -1) {
                perror("write");
                return;
            }
            
            bytesSent += chunkSize;
            qDebug() << bytesSent << "bytes sent";
        }
        qDebug() << "Send complete";
    }

    void receive_and_parse_html(int socket_fd, int parentSocket) {
        char buffer[1024];
        cout<<"inside function "<<std::flush;
        memset(buffer, 0, sizeof(buffer));
        size_t total_received = 0;
        FILE* temp_file = tmpfile();
        if (!temp_file) {
            perror("Error creating temporary file");
            exit(1);
        }
        cout<<"tolllll here "<<std::flush;
        size_t dataSize;
        if (read(socket_fd, &dataSize, sizeof(dataSize)) == -1) {
            perror("read");
            return ;
        }
        cout<<"size read "<<std::flush;
        while (true) {
            qDebug() << "Waiting for data...";
            ssize_t bytes_read = read(socket_fd, buffer, sizeof(buffer));
            qDebug() << "Read: " << bytes_read;
            if (bytes_read < 0) {
                perror("Error reading from socket");
                exit(1);
            } else if (bytes_read == 0) {
                // End of data
                break;
            }

            total_received += bytes_read;
            cout << "Parent received chunk: " << total_received<<std::endl;
            fwrite(buffer, 1, bytes_read, temp_file);

            memset(buffer, 0, sizeof(buffer));
            if (total_received == dataSize) {
                break;
            }
        }

        qDebug() << "Parent received the entire HTML content: " << total_received << "bytes";

        rewind(temp_file);  // Reset file pointer

        yyin = temp_file;  // Set the input stream for Flex

        yyparse();  // Call the lexer/parser

        Node* temp = getRoot();
        
        std::string jsonSerializedTree = serializeTreeToJson(temp);
        sendData(parentSocket, jsonSerializedTree);
    }
    std::string serializeTreeToJson(Node* root) {
        json j = nodeToJson(root);
        return j.dump(); // Convert JSON to a string
    }

    json nodeToJson(Node* node) {
        if (!node) return nullptr;

        json j;
        j["type"] = node->getType();
        j["value"] = *node->getValue();
        j["productions"] = json::array();

        for (Node* child : node->productions) {
            j["productions"].push_back(nodeToJson(child));
        }

        return j;
    }
};

class RenderWorker : public QObject {
    
public:
    RenderWorker(int socket, int parentSocket, string url, QObject *parent = nullptr) : 
    QObject(parent), socket_fd(socket), parentSocket(parentSocket), url(url){}

public slots:
    
    void receiveDataFromParser() {
        receiveData(socket_fd);
    }

    void sendUrlToFetcher(){
        sendUrl(url, parentSocket);
    }
    


signals:
   
    void urlSent(bool success); 

private :
    int socket_fd;
    int parentSocket;
    string url;

    void receiveData(int socket){
        size_t dataSize;
        std::cout << "to be received from socket: " << socket << std::endl;
        if (read(socket, &dataSize, sizeof(dataSize)) == -1) {
            perror("read");

            return;
        }
        std::cout << "size received" << std::flush;

        // Receive the data in chunks
        std::string data;
        data.resize(dataSize);
        size_t bytesReceived = 0;
        while (bytesReceived < dataSize) {
            size_t chunkSize = std::min<size_t>(4096, dataSize - bytesReceived);
            ssize_t result = read(socket, &data[bytesReceived], chunkSize);

            if (result == -1) {
                perror("read");

                return;
            }

            bytesReceived += result;
        }

        // Deserialize the received data (example)
        Root = deserializeTreeFromJson(data);

    }

    Node* deserializeTreeFromJson(const std::string& data) {
        json j = json::parse(data);
        return jsonToNode(j);
    }

    void sendUrl(const std::string& url, int parentSocket){
        if (write(parentSocket, url.c_str(), url.size()) == -1) {
            perror("write");

        } else {
            std::cout << "URL sent" << std::flush;

        }
    }

    Node* jsonToNode(const json& j) {
        if (j.is_null()) return nullptr;

        Node* node = new Node(static_cast<type>(j["type"].get<int>()));
        node->setValue(new std::string(j["value"].get<std::string>()));
        cout<<*node->getValue()<<" ";
        for (auto& child : j["productions"]) {
            node->productions.push_back(jsonToNode(child));
        }

        return node;
    }
};





Node* jsonToNode(const json& j) {
    if (j.is_null()) return nullptr;

    Node* node = new Node(static_cast<type>(j["type"].get<int>()));
    node->setValue(new std::string(j["value"].get<std::string>()));

    for (auto& child : j["productions"]) {
        node->productions.push_back(jsonToNode(child));
    }

    return node;
}

Node* deserializeTreeFromJson(const std::string& data) {
        json j = json::parse(data);
        return jsonToNode(j);
    }


void sendUrl(const std::string& url, int parentSocket){
        if (write(parentSocket, url.c_str(), url.size()) == -1) {
            perror("write");

        } else {
            std::cout << "URL sent" << std::flush;

        }
    }


void sendData(int socket, const std::string& data) {
    // Send the size of the data first
    size_t dataSize = data.size();
    if (write(socket, &dataSize, sizeof(dataSize)) == -1) {
        perror("write");
        return;
    }
    cout<<"size sent "<<socket<<std::flush;
    // Send the data in chunks
    size_t bytesSent = 0;
    while (bytesSent < dataSize) {
        size_t chunkSize = std::min<size_t>(4096, dataSize - bytesSent);
        if (write(socket, data.c_str() + bytesSent, chunkSize) == -1) {
            perror("write");
            return;
        }
        
        bytesSent += chunkSize;
        cout<<bytesSent<<" sent "<<std::flush;
    }
    cout<<"sent complete "<<std::flush;
}







void receiveData(int socket) {
    // Receive the size of the data first
    size_t dataSize;
    cout<<"to be receive "<<socket<<std::endl;
    if (read(socket, &dataSize, sizeof(dataSize)) == -1) {
        perror("read");
        return ;
    }
    cout<<"size received "<<dataSize<<std::endl;
    // Receive the data in chunks
    std::string data;
    data.resize(dataSize);
    size_t bytesReceived = 0;
    while (bytesReceived < dataSize) {
        size_t chunkSize = std::min<size_t>(4096, dataSize - bytesReceived);
        ssize_t result = read(socket, &data[bytesReceived], chunkSize);

        if (result == -1) {
            perror("read");
            return ;
        }
        
        bytesReceived += result;
    }
    Root = deserializeTreeFromJson(data);
    

    return ;
}

void MainWindow::addTab() {
        
        
        QString url = lineEdit->text();
        string URL = url.toStdString();

        if(URL == ""){
            return;
        }


        FetchHtmlWorker *worker = new FetchHtmlWorker(child1ToChild2[1],  parentToChild1[0]);
        QThread *workerThread = new QThread;

        worker->moveToThread(workerThread);  
        connect(workerThread, &QThread::started, worker, &FetchHtmlWorker::run);

       


        NetworkWorker *worker1 = new NetworkWorker(child1ToChild2[0], child2ToParent[1]);
        QThread *workerThread1 = new QThread();

        worker1->moveToThread(workerThread1);

        connect(workerThread1, &QThread::started, worker1, &NetworkWorker::runReceiveAndParseHtml);

        sendUrl(URL, parentToChild1[1]);
        workerThread->start();

        
        workerThread1->start();

        receiveData(child2ToParent[0]);







        if(Root == NULL){
            cout<<"nulll herer";
        }
        Node* temp = Root;
        RenderTabWidget* newTab = new RenderTabWidget(Root,this);
        string title = RenderTabWidget::getTitle(temp);
        cout<<title<<"title";
        QString qtitle = QString::fromStdString(title);
        int tabIndex = tabWidget->count();
        Time currentTime = std::chrono::system_clock::now();

        if(title != "Not Found"){
            tabMap.push_back(make_pair(qtitle, make_pair(URL,currentTime)));
        }
        tabWidget->addTab( newTab, qtitle);
        tabWidget->setCurrentIndex(tabIndex);
        tabWidget->setProperty("url", QVariant(QUrl(QString::fromStdString(URL))));
        urlMap[title] = URL;
        refereshHistoryTab();
    }

Node* getHead(){
    return Root;
}

void MainWindow::renderHistory(string URL){

        if(URL == ""){
            URL = "dfsd";
        }
        cout<<URL<<" hrer url ";
        FetchHtmlWorker *worker = new FetchHtmlWorker(child1ToChild2[1],  parentToChild1[0]);
        QThread *workerThread = new QThread;

        worker->moveToThread(workerThread); 
        connect(workerThread, &QThread::started, worker, &FetchHtmlWorker::run);

        NetworkWorker *worker1 = new NetworkWorker(child1ToChild2[0], child2ToParent[1]);
        QThread *workerThread1 = new QThread();

        worker1->moveToThread(workerThread1);

        connect(workerThread1, &QThread::started, worker1, &NetworkWorker::runReceiveAndParseHtml);

        sendUrl(URL, parentToChild1[1]);
        workerThread->start();
        // workerThread2->start();
        
        workerThread1->start();

        receiveData(child2ToParent[0]);




        if(Root == NULL){
            cout<<"nulll herer";
        }
        Node* temp = Root;
        RenderTabWidget* newTab = new RenderTabWidget(Root, this);
        string title = RenderTabWidget::getTitle(temp);
        cout<<title<<"title";
        QString qtitle = QString::fromStdString(title);
        int tabIndex = tabWidget->count();
        Time currentTime = std::chrono::system_clock::now();

        if(title != "Not Found"){
            tabMap.push_back(make_pair(qtitle, make_pair(URL,currentTime)));
        }
        
        tabWidget->addTab(newTab, qtitle);
        tabWidget->setCurrentIndex(tabIndex);
        tabWidget->setProperty("url", QVariant(QUrl(QString::fromStdString(URL))));
        urlMap[title] = URL;
        refereshHistoryTab();
    }

void MainWindow::renderAnchor(string URL){
    if(URL == ""){
            URL = "dfsd";
        }
        cout<<URL<<"  ";
        static FetchHtmlWorker *worker = new FetchHtmlWorker(child1ToChild2[1],  parentToChild1[0]);
        QThread *workerThread = new QThread;

        worker->moveToThread(workerThread);  
        connect(workerThread, &QThread::started, worker, &FetchHtmlWorker::run);

        static NetworkWorker *worker1 = new NetworkWorker(child1ToChild2[0], child2ToParent[1]);
        QThread *workerThread1 = new QThread();

        worker1->moveToThread(workerThread1);

        connect(workerThread1, &QThread::started, worker1, &NetworkWorker::runReceiveAndParseHtml);

        sendUrl(URL, parentToChild1[1]);
        workerThread->start();

        
        workerThread1->start();

        receiveData(child2ToParent[0]);




        if(Root == NULL){
            cout<<"nulll herer";
        }
        Node* temp = Root;
        RenderTabWidget* newTab = new RenderTabWidget(Root, this);
        string title = RenderTabWidget::getTitle(temp);
        cout<<title<<"title";
        QString qtitle = QString::fromStdString(title);
        
        Time currentTime = std::chrono::system_clock::now();

        if(title != "Not Found"){
            tabMap.push_back(make_pair(qtitle, make_pair(URL,currentTime)));
        }
        
        
        tabWidget->addTab( newTab, qtitle);

        int curr = tabWidget->currentIndex();

        RenderTabWidget* retrievedTab = static_cast<RenderTabWidget*>(tabWidget->widget(curr));
        string retrievedTitle = tabWidget->tabText(curr).toStdString();
        tabWidget->removeTab(curr);
        tabWidget->insertTab( curr,newTab, qtitle);
        tabWidget->setCurrentIndex(curr);
        cout<<curr<<" current index"<<std::endl;
        newTab->undo.push(make_pair(retrievedTab,retrievedTitle));
        tabWidget->setProperty("url", QVariant(QUrl(QString::fromStdString(URL))));
        urlMap[title] = URL;
        refereshHistoryTab();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    


    if (socketpair(AF_UNIX, SOCK_STREAM, 0, parentToChild1) < 0 || socketpair(AF_UNIX, SOCK_STREAM, 0, child1ToChild2) < 0 || socketpair(AF_UNIX, SOCK_STREAM, 0, child2ToParent) < 0) {
        perror("Socket creation failed");
        return 1;
    }
    


    window.loadData();
    return app.exec();


}
