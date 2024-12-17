#ifndef SOCKETMENU_H
#define SOCKETMENU_H

#include <iostream>
#include <string>
#include <vector>
#include "IMenu.h"

class SocketMenu : public IMenu{
public:
    // Constructor that accepts the client socket number (integer)
    SocketMenu(int clientSocket);

    // Method to prompt the user for a command and read the input from the socket
    int nextCommand();

    // Method to return the last input received from the user (over socket)
    const std::string& getLastInput() const;

    // Method to display a general message to the user
    void displayMessage(const std::string& message);

    // Method to display a list of movie IDs (represented as integers)
    void displayMovieList(const std::vector<int>& movies);

    // Method to display a logic error message to the user
    void displayLogicError(const std::string& message) override;

// Method to display a bad request error message to the user
    void displayBadRequestError(const std::string& message) override;

private:
    int m_socket;            // Socket number (integer) for communication
    std::string m_lastInput; // Stores the last received input
};

#endif // SOCKETMENU_H
