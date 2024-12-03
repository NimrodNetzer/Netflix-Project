#include <iostream>
#include <memory> // For smart pointers
#include "ConsoleMenu.h"
#include "ICommand.h"
#include "add.h"
#include "app.h"
#include "help.h"
#include <map>
#include <vector>

// Helper function to initialize commands
std::map<std::string, ICommand*> initializeCommands(std::vector<Movie>& movies, std::vector<User>& users) {
    std::map<std::string, ICommand*> commands;
    commands["add"] = new add(movies, users);
    commands["help"] = new Help();
    return commands;
}

int main() {
    try {
        // Create sample vectors of movies and users
        std::vector<Movie> movies;
        std::vector<User> users;

        // Initialize commands
        std::map<std::string, ICommand*> commands = initializeCommands(movies, users);

        // Create a ConsoleMenu instance
        ConsoleMenu menu;

        // Create the application instance
        App application(menu, commands, movies, users);

        // Run the application
        application.run();

        // Clean up dynamically allocated commands
        for (auto& command : commands) {
            delete command.second;
        }

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Return non-zero to indicate failure
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1; // Return non-zero to indicate failure
    }

    return 0; // Return zero to indicate success
}
