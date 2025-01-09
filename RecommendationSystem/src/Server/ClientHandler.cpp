//
// Created by ido on 12/18/24.
//

#include "ClientHandler.h"
#include "../Core/app.h"
#include "Commands/add.h"
#include "Commands/help.h"
#include "Commands/recommend.h"
#include "Commands/post.h"
#include "Commands/patch.h"
#include "Commands/Delete.h"

#include <iostream>
#include <cstring>
#include <unistd.h>

#include "Commands/help.h"
#include "Menus/SocketMenu.h"

std::map<std::string, ICommand*> ClientHandler::initializeCommands(IMenu& menu) {
    std::map<std::string, ICommand*> commands;
    commands["HELP"] = new Help(menu);
    commands["GET"] = new recommend(menu);
    commands["POST"] = new post(menu);
    commands["PATCH"] = new patch(menu);
    commands["DELETE"] = new Delete(menu);
    return commands;
}

void ClientHandler::run() {
    try {
        SocketMenu menu(clientSocket); // Menu linked to client socket

        // Initialize commands using the menu
        std::map<std::string, ICommand*> commands = initializeCommands(menu);

        // Create the application and run it
        App application(menu, commands);
        application.run();

        // Clean up commands after execution
        for (auto& command : commands) {
            delete command.second;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error handling client: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred while handling client." << std::endl;
    }
    std::cout << "closing connection" << std::endl;
    // Close the client socket
    close(clientSocket);
}
