#include "SocketMenu.h"
#include <netinet/in.h>
#include <arpa/inet.h>

// Constructor to initialize the socket
SocketMenu::SocketMenu(int clientSocket) : m_socket(clientSocket) {
    //if (clientSocket == INVALID_SOCKET) {
    //    std::cerr << "Invalid socket." << std::endl;
    //    exit(1);  // Exit the program if socket is invalid
    //}
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


// Method to return the last input received from the user (over socket)
const std::string& SocketMenu::getLastInput() const {
    return m_lastInput;
}

// Method to display a general message to the user
void SocketMenu::displayMessage(const std::string& message) {
    send(m_socket, message.c_str(), message.size(), 0);
    std::cout << message << std::endl;
}

// Method to display a list of movie IDs (represented as integers)
void SocketMenu::displayMovieList(const std::vector<int>& movies) {
    std::string movieList;
    std::cout << movies.size() << std::endl;
    // Construct the movie list as a comma-separated string
    for (size_t i = 0; i < movies.size(); ++i) {
        movieList += std::to_string(movies[i]);
        if (i < movies.size() - 1) {
            movieList += ", ";
        }
    }
    movieList += "\n200 OK";
    // Send the movie list over the socket
    send(m_socket, movieList.c_str(), movieList.size(), 0);

    // Optionally, print to console for debugging
    std::cout << "Sent to socket: " << movieList << std::endl;
}



void SocketMenu::displayLogicError(const std::string& message) {
    send(m_socket, message.c_str(), message.size(), 0);
}

// displayBadRequestError implementation
void SocketMenu::displayBadRequestError(const std::string& message) {
    send(m_socket, message.c_str(), message.size(), 0);
}