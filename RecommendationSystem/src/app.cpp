#include "app.h"
#include <iostream>
#include <sstream>

app::app(const std::map<std::string, ICommand*>& commands,
         std::vector<Movie>& movies,
         std::vector<User>& users)
        : m_commands(commands), m_movies(movies), m_users(users) {}

void app::run() {
    std::string commandLine;
    while (true) {
        std::cout << "Enter command (or 'exit' to quit): ";
        std::getline(std::cin, commandLine);

        if (commandLine == "exit") {
            break;
        }

        std::istringstream iss(commandLine);
        std::string commandID;
        iss >> commandID;

        if (commandID.empty()) {
            std::cout << "No command entered." << std::endl;
            continue;
        }

        auto it = m_commands.find(commandID);
        if (it != m_commands.end()) {
            std::string arguments;
            std::getline(iss, arguments);
            it->second->execute(arguments);
        } else {
            std::cout << "Invalid command ID." << std::endl;
        }
    }
}
