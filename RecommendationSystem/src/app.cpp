#include "app.h"
#include <sstream>    // For std::istringstream
#include <exception>  // For std::exception

// Constructor for the App class that initializes the menu, commands, movies, and users.
App::App(IMenu& menu, const std::map<std::string, ICommand*>& commands)
        : m_menu(menu), m_commands(commands) {}

// Main loop for the application, continuously accepting and executing commands.
void App::run() {
    while (true) {
        try {
            // Display the menu and get the user's command input.
            m_menu.nextCommand();

            // Retrieve the last input from the menu.
            const std::string& commandLine = m_menu.getLastInput();

            // Parse the command ID from the input.
            std::istringstream iss(commandLine);
            std::string commandID;
            iss >> commandID;

            // Search for the command in the command map.
            auto it = m_commands.find(commandID);
            if (it != m_commands.end()) {
                // If the command exists, extract any remaining arguments and execute the command.
                std::string arguments;
                std::getline(iss, arguments);
                it->second->execute(arguments);
            }
        } catch (const std::exception& e) {
            // Handle exceptions and display an error message using the menu.
            m_menu.displayError(e.what());
        }
    }
}
