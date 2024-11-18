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

signals:
    // void finished();  // Signal to indicate task is complete

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
        std::string pageName = fetchAndCachePage(url);  // Placeholder for page name
        std::ifstream file(pageName);
        if (!file) {
            perror("Error opening file");
            exit(1);
        }else{
            cout<<"file opened"<<std::flush;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();  // Read the entire file into the stringstream
        std::string html_content = buffer.str();
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
        // emit finished();  // Emit finished signal when the task is done
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
        // cout<<jsonSerializedTree<<std::endl;
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
    // void dataReceived(const std::string& data); // Signal when data is received
    void urlSent(bool success);  // Signal when the URL is successfully sent

private :
    int socket_fd;
    int parentSocket;
    string url;

    void receiveData(int socket){
        size_t dataSize;
        std::cout << "to be received from socket: " << socket << std::endl;
        if (read(socket, &dataSize, sizeof(dataSize)) == -1) {
            perror("read");
            // emit dataReceived("");  // Emit empty string on error
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
                // emit dataReceived("");  // Emit empty string on error
                return;
            }

            bytesReceived += result;
        }

        // Deserialize the received data (example)
        Root = deserializeTreeFromJson(data);

        // emit dataReceived(data);
    }

    Node* deserializeTreeFromJson(const std::string& data) {
        json j = json::parse(data);
        return jsonToNode(j);
    }

    void sendUrl(const std::string& url, int parentSocket){
        if (write(parentSocket, url.c_str(), url.size()) == -1) {
            perror("write");
            // emit urlSent(false);  // Emit failure signal
        } else {
            std::cout << "URL sent" << std::flush;
            // emit urlSent(true);  // Emit success signal
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

// void receiveData(int socket){
//         size_t dataSize;
//         std::cout << "to be received from socket: " << socket << std::endl;
//         if (read(socket, &dataSize, sizeof(dataSize)) == -1) {
//             perror("read");
//             // emit dataReceived("");  // Emit empty string on error
//             return;
//         }
//         std::cout << "size received" << std::flush;

//         // Receive the data in chunks
//         std::string data;
//         data.resize(dataSize);
//         size_t bytesReceived = 0;
//         while (bytesReceived < dataSize) {
//             size_t chunkSize = std::min<size_t>(4096, dataSize - bytesReceived);
//             ssize_t result = read(socket, &data[bytesReceived], chunkSize);

//             if (result == -1) {
//                 perror("read");
//                 // emit dataReceived("");  // Emit empty string on error
//                 return;
//             }

//             bytesReceived += result;
//         }

//         // Deserialize the received data (example)
//         Root = deserializeTreeFromJson(data);

//         // emit dataReceived(data);
//     }
// void sendUrl(string url){
//     // std::string url = "http://localhost:8000/html_dataset/html_page_2.html";
//     if (write(parentSocket, url.c_str(), url.size()) == -1) {
//         perror("write");
//         return;
//     } else {
//         std::cout << "URL sent" << std::flush;
//     }
// }



Node* jsonToNode(const json& j) {
    if (j.is_null()) return nullptr;

    Node* node = new Node(static_cast<type>(j["type"].get<int>()));
    node->setValue(new std::string(j["value"].get<std::string>()));
    // cout<<*node->getValue()<<" ";
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
            // emit urlSent(false);  // Emit failure signal
        } else {
            std::cout << "URL sent" << std::flush;
            // emit urlSent(true);  // Emit success signal
        }
    }
// Helper function to deserialize a tree from JSON string
// Node* deserializeTreeFromJson(const std::string& data) {
//     json j = json::parse(data);
//     return jsonToNode(j);
// }

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


// void receive_and_parse_html(int socket_fd, int parentSocket) {
//     char buffer[BUFFER_SIZE];
//     memset(buffer, 0, sizeof(buffer));
//     size_t total_received = 0;
//     FILE* temp_file = tmpfile();
//     if (!temp_file) {
//         perror("Error creating temporary file");
//         exit(1);
//     }

//     size_t dataSize;
//     if (read(socket_fd, &dataSize, sizeof(dataSize)) == -1) {
//         perror("read");
//         return ;
//     }

//     // Read the HTML content in chunks
//     while (true) {
//         cout<<"waiting "<<std::flush;
//         ssize_t bytes_read = read(socket_fd, buffer, sizeof(buffer));
//         cout<<"read "<<std::flush;
//         if (bytes_read < 0) {
//             perror("Error reading from socket");
//             exit(1);
//         } else if (bytes_read == 0) {
//             // End of data
//             break;
//         }

//         total_received += bytes_read;
//         std::cout << "Parent received chunk: " <<total_received<< std::endl;
//         fwrite(buffer, 1, bytes_read, temp_file);


//         // Clear the buffer for the next chunk
//         memset(buffer, 0, sizeof(buffer));
//         if(total_received == dataSize){
//             break;
//         }
//     }

//     std::cout << "Parent received the entire HTML content: " << total_received << " bytes" << std::endl;
    
    
//     // Now set the Flex input stream to the temporary file
//     rewind(temp_file); 

//     // Set the Flex input stream to the temporary file
//     yyin = temp_file;

//     // Now call the lexer to process the HTML content from the temp file
//     yyparse();

//     Node* temp = getRoot();
    
//     cout<<"jfksdj "<<std::flush;
//     std::string jsonSerializedTree = serializeTreeToJson(temp);
//     sendData(parentSocket, jsonSerializedTree);

// }






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
        // sendUrl(url.toStdString());
        string URL = url.toStdString();



        FetchHtmlWorker *worker = new FetchHtmlWorker(child1ToChild2[1],  parentToChild1[0]);
        QThread *workerThread = new QThread;

        worker->moveToThread(workerThread);  // Move worker to the new thread

        // Connect signals and slots
        connect(workerThread, &QThread::started, worker, &FetchHtmlWorker::run);
        // connect(worker, &FetchHtmlWorker::finished, workerThread, &QThread::quit);
        // connect(worker, &FetchHtmlWorker::finished, worker, &QObject::deleteLater);
        // connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

        // Start the worker thread
       


        NetworkWorker *worker1 = new NetworkWorker(child1ToChild2[0], child2ToParent[1]);
        QThread *workerThread1 = new QThread();

        worker1->moveToThread(workerThread1);

        connect(workerThread1, &QThread::started, worker1, &NetworkWorker::runReceiveAndParseHtml);
        // connect(worker1, &NetworkWorker::finished, workerThread1, &QThread::quit);
        // connect(worker1, &NetworkWorker::finished, worker1, &QObject::deleteLater);
        // connect(workerThread1, &QThread::finished, workerThread1, &QObject::deleteLater);

        

        // RenderWorker *worker2 = new RenderWorker(parentToChild1[0] , parentToChild1[1], URL);
        // QThread *workerThread2 = new QThread();

        // worker2->moveToThread(workerThread2);
        // connect(workerThread2, &QThread::started, worker2, &RenderWorker::sendUrlToFetcher);
        // connect(workerThread2, &QThread::started, worker2, &RenderWorker::receiveDataFromParser);
        sendUrl(URL, parentToChild1[1]);
        workerThread->start();
        // workerThread2->start();
        
        workerThread1->start();

        receiveData(child2ToParent[0]);







        if(Root == NULL){
            cout<<"nulll herer";
        }
        Node* temp = Root;
        RenderTabWidget* newTab = new RenderTabWidget(Root);
        string title = RenderTabWidget::getTitle(temp);
        cout<<title<<"title";
        QString qtitle = QString::fromStdString(title);
        int tabIndex = tabWidget->count();
        tabMap[qtitle] = newTab;
        tabWidget->addTab( newTab, qtitle);
        tabWidget->setCurrentIndex(tabIndex);
        refereshHistoryTab();
    }

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    
    // int parentToChild1[2], child1ToChild2[2];
    pid_t pid1, pid2;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, parentToChild1) < 0 || socketpair(AF_UNIX, SOCK_STREAM, 0, child1ToChild2) < 0 || socketpair(AF_UNIX, SOCK_STREAM, 0, child2ToParent) < 0) {
        perror("Socket creation failed");
        return 1;
    }
    

    // Fork: create one child process
    // pid1 = fork();
    // if (pid1 < 0) {
    //     perror("Fork failed");
    //     return 1;
    // } else if (pid1 == 0) {
    //     // Child process
    //     // close(parentToChild1[1]);  // Close the unused end of parent socket
    //     // while(true)
    //         fetch_html_and_send(child1ToChild2[1], parentToChild1[0]);
        
        
    //     // close(child1ToChild2[1]);  // Close the used end of the socket
    //     exit(0);
    // } else {
    //     // Parent process
        

    //     // Wait for the child to finish
    //     // wait(NULL);


    //     pid2 = fork();
    //     if(pid2 < 0){
    //         perror("Fork failed");
    //         return 1;
    //     }
    //     if(pid2 == 0){
    //         // while(true)
    //             receive_and_parse_html(child1ToChild2[0], parentToChild1[1]);
            
    //     }else{
    //         // close(parentToChild1[0]); 
    //         // close(child1ToChild2[1]);
            
    //         parentSocket = parentToChild1[1];
    //         sendUrl("http://localhost:8000/html_page_1.html");
    //         std::string jsonReceived = receiveData(parentToChild1[0]);
    //         cout<<"done hrer also "<<std::flush;
            
    //         // close(parentToChild1[1]);  // Close the used end of the socket
    //     }
    // }
    return app.exec();


}
