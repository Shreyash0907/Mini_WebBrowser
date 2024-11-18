#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <filesystem>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>

namespace fs = std::filesystem;

#define BUFFER_SIZE 1024

string notFound = "<!DOCTYPE html>\n<html>    <head>    <title>Not Found</title></head><body>    <h2>404 URL Not Found</h2></body></html>";

// Helper function to write fetched data to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchAndCachePage( const std::string& url) {
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
            return notFound;
        } else {
            std::cout << "Fetched and cached: " << pageName << std::endl;
            std::cout << "Content of " << pageName << ":\n" << readBuffer << "\n\n";

            // Write the fetched content to the cache
            // std::ofstream outFile(readBuffer);
            // outFile << readBuffer;
            if(readBuffer.find("Error response") != std::string::npos){
                readBuffer = notFound;
            }
        }
        
        curl_easy_cleanup(curl);
    }
    cout<<"hfere"<<std::flush;
    return readBuffer;
}

void fetch_html_and_send(int socket_fd, int parentSocket) {
    char buff[1024];
    ssize_t s;
    if ((s = read(parentSocket, &buff, sizeof(buff))) == -1) {
        perror("read");
        return;
    }
    buff[s] = '\0';  // Null-terminate the string
    std::string url(buff);  // Convert to std::string

    std::cout<<"url to be used "<<url<<std::endl;
    // std::string pageName = fetchAndCachePage(url) ;
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

            // Write the fetched content to the cache
            // std::ofstream outFile(readBuffer);
            // outFile << readBuffer;
        }
        
        curl_easy_cleanup(curl);
    }
    // cout<<"hfere"<<std::flush;


    cout<<"till shere"<<std::flush;
;    // Read the HTML content from a file
    std::cout<<readBuffer<<" "<<std::flush;
    // std::ifstream file(pageName);
    // if (!file) {
    //     perror("Error opening file");
    //     exit(1);
    // }

    // std::stringstream buffer;
    // buffer << file.rdbuf();  // Read the entire file into the stringstream
    // std::string html_content = buffer.str();
    std::string html_content = readBuffer;
    size_t content_length = html_content.size();
    size_t total_sent = 0;

    if (write(socket_fd, &content_length, sizeof(content_length)) == -1) {
        perror("write");
        return;
    }

    // Send the HTML content in chunks
    while (total_sent < content_length) {
        size_t chunk_size = BUFFER_SIZE;
        if (content_length - total_sent < BUFFER_SIZE) {
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

// int main() {
//     std::string url = "http://localhost:8000/html_page_1.html";
//     // std::cout << "Enter the URL to fetch: ";
//     // std::cin >> url;

//     // Extract the page name from the URL (everything after the last '/')
    

//     // Create cache directory if it doesn't exist
//     if (!fs::exists("cache")) {
//         fs::create_directory("cache");
//     }

//     // Initialize libcurl
//     curl_global_init(CURL_GLOBAL_DEFAULT);

//     // Fetch and cache the provided URL
//     fetchAndCachePage( url);

//     // Cleanup libcurl
//     curl_global_cleanup();

//     return 0;
// }
