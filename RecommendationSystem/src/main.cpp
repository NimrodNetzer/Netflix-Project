
#include <DataManager.h>
#include <iostream>
#include <memory> // For smart pointers
#include "ConsoleMenu.h"
#include "ICommand.h"
#include "add.h"
#include "app.h"
#include "help.h"
#include <map>
#include <vector>
#include "IPersistence.h"
#include "FilePersistence.h"
#include "recommendAlgo.h"
#include "recommend.h"

// Helper function to initialize commands
std::map<std::string, ICommand*> initializeCommands() {
    std::map<std::string, ICommand*> commands;
    commands["add"] = new add();
    commands["help"] = new Help();
    commands["recommend"] = new recommend();
    return commands;
}

int main() {
    try {
        // Create sample vectors of movies and users
        IPersistence* persistence = new FilePersistence("data");
        DataManager& data_manager = DataManager::getInstance();
        data_manager.setPersistenceStrategy(persistence);
        // Initialize commands
        std::map<std::string, ICommand*> commands = initializeCommands();

        // Create a ConsoleMenu instance
        ConsoleMenu menu;

        data_manager.load();

        // Create the application instance
        App application(menu, commands);

        // Run the application
        application.run();

        // Clean up dynamically allocated commands
        for (auto& command : commands) {
            delete command.second;
        }
        delete persistence;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Return non-zero to indicate failure
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1; // Return non-zero to indicate failure
    }

    return 0; // Return zero to indicate success
}

