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

void MainWindow::addTab() {
        Node* temp = Root;
        RenderTabWidget* newTab = new RenderTabWidget(Root);
        string title = RenderTabWidget::getTitle(temp);
        QString qtitle = QString::fromStdString(title);
        tabWidget->addTab( newTab, qtitle); // Add a new tab with the next index
    }


void receive_and_parse_html(int socket_fd) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    size_t total_received = 0;
    FILE* temp_file = tmpfile();
    if (!temp_file) {
        perror("Error creating temporary file");
        exit(1);
    }
    // Read the HTML content in chunks
    while (true) {
        ssize_t bytes_read = read(socket_fd, buffer, sizeof(buffer));
        if (bytes_read < 0) {
            perror("Error reading from socket");
            exit(1);
        } else if (bytes_read == 0) {
            // End of data
            break;
        }

        total_received += bytes_read;
        std::cout << "Parent received chunk: " << buffer << std::endl;
        fwrite(buffer, 1, bytes_read, temp_file);


        // Clear the buffer for the next chunk
        memset(buffer, 0, sizeof(buffer));
    }

    std::cout << "Parent received the entire HTML content: " << total_received << " bytes" << std::endl;
    

    // Now, we'll feed the content to yylex (Flex lexer)
    // Set the input stream for Flex to the stringstream buffer
    rewind(temp_file);

    char file_content[BUFFER_SIZE];  // Buffer to read and print file content
    size_t bytes_read;

    // Rewind the file to the beginning before printing
    rewind(temp_file);

    while ((bytes_read = fread(file_content, 1, sizeof(file_content), temp_file)) > 0) {
        // Print the contents of the file
        std::cout.write(file_content, bytes_read);
    }

    // Now set the Flex input stream to the temporary file
    rewind(temp_file); 

    // Set the Flex input stream to the temporary file
    yyin = temp_file;

    // Now call the lexer to process the HTML content from the temp file
    yyparse();

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
Node* jsonToNode(const json& j) {
    if (j.is_null()) return nullptr;

    Node* node = new Node(static_cast<type>(j["type"].get<int>()));
    node->setValue(new std::string(j["value"].get<std::string>()));

    for (const auto& child : j["productions"]) {
        node->productions.push_back(jsonToNode(child));
    }

    return node;
}

std::string serializeTreeToJson(Node* root) {
    json j = nodeToJson(root);
    return j.dump(); // Convert JSON to a string
}

// Helper function to deserialize a tree from JSON string
Node* deserializeTreeFromJson(const std::string& data) {
    json j = json::parse(data);
    return jsonToNode(j);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const char* inputFile = "html_page_1.html";
    FILE *inputPtr;
    inputPtr = fopen(inputFile, "r");
    extern FILE *yyin;
    yyin = inputPtr;
    yyparse();
    // Node* temp = getRoot();
    Root = getRoot();

    // std::string jsonSerializedTree = serializeTreeToJson(temp);
    // std::cout << "Serialized Tree (JSON): " << jsonSerializedTree << std::endl;

    // // Deserialize the tree from JSON
    // Node* deserializedRoot = deserializeTreeFromJson(jsonSerializedTree);
    // std::cout << "Deserialized Tree Root Value: " << *deserializedRoot->getValue() << std::endl;

    

    
    MainWindow window;
    window.show();

    return app.exec();

    // int socket_pair[2];
    // pid_t pid, pid2;

    // if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) < 0) {
    //     perror("Socket creation failed");
    //     return 1;
    // }
    // if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) < 0) {
    //     perror("Socket creation failed");
    //     return 1;
    // }

    // // Fork: create one child process
    // pid = fork();
    // if (pid < 0) {
    //     perror("Fork failed");
    //     return 1;
    // } else if (pid == 0) {
    //     // Child process
    //     close(socket_pair[0]);  // Close the unused end of the socket
    //     fetch_html_and_send(socket_pair[1]);
    //     close(socket_pair[1]);  // Close the used end of the socket
    //     exit(0);
    // } else {
    //     // Parent process
    //     close(socket_pair[1]);  // Close the unused end of the socket
    //     receive_and_parse_html(socket_pair[0]);
    //     close(socket_pair[0]);  // Close the used end of the socket

    //     // Wait for the child to finish
    //     wait(NULL);
    // }
    return 0;

}
