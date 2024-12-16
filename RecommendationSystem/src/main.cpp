
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

std::map<std::string, ICommand*> initializeCommands(IMenu& menu) {
    std::map<std::string, ICommand*> commands;
    commands["add"] = new add();           // No change for add
    commands["help"] = new Help(menu);    // Pass menu to Help
    commands["recommend"] = new recommend(menu); // Pass menu to recommend
    return commands;
}

int main() {
    try {
        ConsoleMenu menu;

        // Initialize commands with ConsoleMenu
        std::map<std::string, ICommand*> commands = initializeCommands(menu);

        IPersistence* persistence = new FilePersistence("data");
        DataManager& data_manager = DataManager::getInstance();
        data_manager.setPersistenceStrategy(persistence);
        data_manager.load();

        App application(menu, commands);
        application.run();

        for (auto& command : commands) {
            delete command.second;
        }
        delete persistence;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}


