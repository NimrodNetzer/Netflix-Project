#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include "IMenu.h"
#include <iostream>
#include <string>
#include <vector>

class ConsoleMenu : public IMenu {
public:
    ConsoleMenu() = default;

    int nextCommand() override {
        std::cout << "Enter command: ";
        std::getline(std::cin, m_lastInput);

        if (m_lastInput.empty()) {
            std::cout << "Input cannot be empty. Please enter a valid command." << std::endl;
            return -1;  // Indicating invalid input
        }
        return 0;  // Successfully read a command
    }

    const std::string& getLastInput() const override {
        return m_lastInput;
    }

    void displayMessage(const std::string& message) override {
        std::cout << message << std::endl;
    }

    void displayMovieList(const std::vector<int>& movies) override {
        std::cout << "Movies List: ";
        for (size_t i = 0; i < movies.size(); ++i) {
            std::cout << movies[i];
            if (i < movies.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    void displayLogicError(const std::string& message) override {
        std::cout << "404 Not Found: " << message << std::endl;
    }

    void displayBadRequestError(const std::string& message) override {
        std::cout << "400 Bad Request: " << message << std::endl;
    }

private:
    std::string m_lastInput;
};

#endif // CONSOLEMENU_H
