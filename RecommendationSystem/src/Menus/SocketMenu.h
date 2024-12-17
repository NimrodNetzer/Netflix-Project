#ifndef SOCKETMENU_H
#define SOCKETMENU_H

#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h> // For Winsock functions (Windows)

class SocketMenu {
public:
    // Constructor that accepts the client socket number (integer)
    SocketMenu(int clientSocket);

    // Method to prompt the user for a command and read the input from the socket
    int nextCommand();

    // Method to display an error message to the user
    void displayError(const std::string& message);

    // Method to return the last input received from the user (over socket)
    const std::string& getLastInput() const;

    // Method to display a general message to the user
    void displayMessage(const std::string& message);

    // Method to display a list of movie IDs (represented as integers)
    void displayMovieList(const std::vector<int>& movies);

private:
    int m_socket;            // Socket number (integer) for communication
    std::string m_lastInput; // Stores the last received input
};

#endif // SOCKETMENU_H
