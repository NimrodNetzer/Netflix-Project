#ifndef HELP_H
#define HELP_H

#include "ICommand.h"
#include <iostream>

// Help class that implements the ICommand interface
class Help : public ICommand {
public:
    // Method to execute the command and display help information
    void execute(std::string s) override {
        std::cout << "add [userid] [movieid1] [movieid2]..." << std::endl;
        std::cout << "recommend [userid] [movieid]" << std::endl;
        std::cout << "help" << std::endl;
    }
};

#endif // HELP_H
