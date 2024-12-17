#include "SocketMenu.h"
#include <winsock2.h>

// Constructor to initialize the socket
SocketMenu::SocketMenu(int clientSocket) : m_socket(clientSocket) {
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Invalid socket." << std::endl;
        exit(1);  // Exit the program if socket is invalid
    }
}

// Method to prompt the user for a command and read the input from the socket
int SocketMenu::nextCommand() {
    char buffer[1024];
    int bytesReceived = recv(m_socket, buffer, sizeof(buffer) - 1, 0); // Receive data from the server
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Null-terminate the received data
        m_lastInput = std::string(buffer); // Store the input as the last received message
        return 0;
    } else if (bytesReceived == 0) {
        std::cerr << "Connection closed by the server." << std::endl;
        return -1; // Connection closed
    } else {
        std::cerr << "Error receiving data from the server." << std::endl;
        return -1; // Error occurred
    }
}

// Method to display an error message to the user
void SocketMenu::displayError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}

// Method to return the last input received from the user (over socket)
const std::string& SocketMenu::getLastInput() const {
    return m_lastInput;
}

// Method to display a general message to the user
void SocketMenu::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}

// Method to display a list of movie IDs (represented as integers)
void SocketMenu::displayMovieList(const std::vector<int>& movies) {
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << movies[i];
        if (i < movies.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
