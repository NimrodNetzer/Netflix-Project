#ifndef HELP_H
#define HELP_H

#include "ICommand.h"
#include <iostream>

// Help class that implements the ICommand interface
class Help : public ICommand {
public:
    // Method to execute the command and display help information
    void execute(std::string s) override {
        std::cout << "Available commands:" << std::endl;
        std::cout << "add [userid] [movieid1] [movieid2] ... - Add movies to a user." << std::endl;
        std::cout << "recommend [userid] [movieid] - Recommend a movie to a user." << std::endl;
        std::cout << "help - Display this help information." << std::endl;
        std::cout << "exit - Exit the application." << std::endl;
    }
};

#endif // HELP_H
