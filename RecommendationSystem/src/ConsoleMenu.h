#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include <iostream>  // For std::cin and std::cout
#include <limits>    // For std::numeric_limits

class ConsoleMenu {
public:
    // Displays a prompt and waits for user input
    int nextCommand() {
        int command;
        std::cout << "Enter a command: ";
        std::cin >> command;

        // Validate input and handle invalid input
        if (std::cin.fail()) {
            std::cin.clear(); // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore extra input
            throw std::invalid_argument("Invalid input. Please enter a number.");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore trailing input
        return command;
    }
};

#endif // CONSOLEMENU_H
