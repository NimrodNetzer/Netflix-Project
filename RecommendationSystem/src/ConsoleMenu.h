#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include "IMenu.h"
#include <iostream>
#include <string>
#include <vector>

// Derived class implementing the IMenu interface
class ConsoleMenu : public IMenu {
public:
    ConsoleMenu() = default;

    // Override all virtual methods
    int nextCommand() override {
        std::cout << "Enter command: ";
        std::getline(std::cin, m_lastInput);

        if (m_lastInput.empty()){
            throw std::invalid_argument("");
        }
        return 0;
    }

    void displayError(const std::string& message) override {
        std::cerr << "Error: " << message << std::endl;
    }

    const std::string& getLastInput() const override {
        return m_lastInput;
    }

    void displayMessage(const std::string& message) override {
        std::cout << message << std::endl;
    }

    void displayMovieList(const std::vector<int>& movies) override {
        for (size_t i = 0; i < movies.size(); ++i) {
            std::cout << movies[i];
            if (i < movies.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

private:
    std::string m_lastInput;
};

#endif // CONSOLEMENU_H
