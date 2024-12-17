
#include "Data/DataManager.h"
#include <iostream>
#include <memory> // For smart pointers
#include "Menus/ConsoleMenu.h"
#include "Interfaces/ICommand.h"
#include "Commands/add.h"
#include "Core/app.h"
#include "Commands/help.h"
#include <map>
#include <vector>
#include "Interfaces/IPersistence.h"
#include "Data/FilePersistence.h"
#include "Commands/recommendAlgo.h"
#include "Commands/recommend.h"
#include "Commands/post.h"
#include "Commands/patch.h"
#include "Commands/Delete.h"

std::map<std::string, ICommand*> initializeCommands(IMenu& menu) {
    std::map<std::string, ICommand*> commands;
    commands["add"] = new add();           // No change for add
    commands["help"] = new Help(menu);    // Pass menu to Help
    commands["get"] = new recommend(menu); // Pass menu to recommend
    commands["post"] = new post(menu);
    commands["patch"] = new patch(menu);
    commands["delete"] = new Delete(menu);

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


