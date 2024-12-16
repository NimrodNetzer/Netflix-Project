#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include "IMenu.h"
#include <iostream>
#include <string>
#include <vector>

// Derived class implementing the IMenu interface
class ConsoleMenu : public IMenu {
public:
    // Default constructor
    ConsoleMenu() = default;

    // Override all virtual methods from IMenu

    // Method to prompt the user for a command and read the input
    int nextCommand() override {
        std::cout << "Enter command: "; // Display prompt
        std::getline(std::cin, m_lastInput); // Get user input

        // If input is empty, throw an exception (could be extended to handle specific cases)
        if (m_lastInput.empty()){
            throw std::invalid_argument("Input cannot be empty.");
        }
        return 0; // Returning 0 as a placeholder (this could be adjusted based on your needs)
    }

    // Method to display an error message to the user
    void displayError(const std::string& message) override {
        std::cerr << "Error: " << message << std::endl; // Print error to standard error
    }

    // Method to return the last input received from the user
    const std::string& getLastInput() const override {
        return m_lastInput; // Return the stored last input
    }

    // Method to display a general message to the user
    void displayMessage(const std::string& message) override {
        std::cout << message << std::endl; // Output message to standard output (console)
    }

    // Method to display a list of movie IDs (represented as integers)
    void displayMovieList(const std::vector<int>& movies) override {
        for (size_t i = 0; i < movies.size(); ++i) { // Loop through all movie IDs
            std::cout << movies[i]; // Print each movie ID

            // If not the last movie in the list, add a comma separator
            if (i < movies.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl; // End the line after the list
    }

private:
    // Member variable to store the last input string from the user
    std::string m_lastInput;
};

#endif // CONSOLEMENU_H
