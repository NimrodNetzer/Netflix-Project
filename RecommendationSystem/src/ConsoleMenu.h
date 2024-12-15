#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include "IMenu.h"            // Include the IMenu interface for menu interaction
#include <iostream>           // For standard I/O operations (e.g., std::cout, std::cerr)
#include <string>             // For handling strings
#include <limits>             // For std::numeric_limits used in input validation
#include <stdexcept>          // For throwing exceptions

// ConsoleMenu class implements the IMenu interface, providing a command-line interface for user interaction.
class ConsoleMenu : public IMenu {
public:
    // Prompts the user to enter a command and reads the input.
    // Throws an exception if the input is empty.
    int nextCommand() override {
        std::cout << "Enter a command: ";
        std::getline(std::cin, m_lastInput);  // Reads the full line of input from the user.

        // Check if the input is empty and throw an exception if it is.
        if (m_lastInput.empty()) {
            throw std::invalid_argument("");
        }
        return 0; // Return a dummy command ID for now (placeholder).
    }

    // Displays an error message to the standard error stream.
    void displayError(const std::string& message) override {
        std::cerr << "Error: " << message << std::endl; // Outputs the error message to std::cerr.
    }

    // Returns the last input string provided by the user.
    const std::string& getLastInput() const override {
        return m_lastInput; // Return the stored input.
    }

private:
    std::string m_lastInput; // Private member variable to store the last input from the user.
};

#endif // CONSOLEMENU_H
