#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <queue>
#include <condition_variable>
#include <string>
#include <cstring>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#define PORT 8100
#define MAX_CLIENTS 3
#define BUFFER_SIZE 1024

#include "Server.h"

#include "ClientHandler.h"
#include "Core/app.h"
#include "Commands/Delete.h"
#include "Menus/SocketMenu.h"
#include "Commands/add.h"
#include "Commands/help.h"
#include "Commands/recommend.h"
#include "Commands/patch.h"
#include "Commands/post.h"

void Server::handleClient(int client_sock) {
    ClientHandler handler(client_sock);
    executor.execute(handler);
}


void Server::run() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Ensure proper conversion
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;


    while (true) {
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) < 0) {
            perror("Accept failed");
            continue;
        }

        std::cout << "New connection: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

        // Add client socket to the thread pool
        handleClient(clientSocket);
    }

    close(serverSocket);
}