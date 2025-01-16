#include "patch.h"
#include <sstream>
#include <iostream>
#include "Data/DataManager.h"
#include "add.h"

// Constructor definition for the 'patch' class
patch::patch(IMenu& menu) : m_menu(menu) {}

void patch::execute(std::string s) {
    // Create an 'add' object for validation and execution (reuse add command if needed)
    add addCommand;

    // Validate the input string
    try {
        addCommand.validateString(s); // This handles validation of the input
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        m_menu.displayBadRequestError("400 Bad Request");
        return;
    }

    // Extract the user ID from the input string
    DataManager& data_manager = DataManager::getInstance();
    std::istringstream iss(s);
    int userID;
    iss >> userID;

    // Check if the user exists
    if (!data_manager.hasUser(userID)) {
        std::cout << "User not found." << std::endl;
        m_menu.displayLogicError("404 Not Found");
        return;
    }

    // Use a try-catch block only around the 'execute' method of add
    try {
        // Update the user and movie data (the actual patch operation)
        addCommand.execute(s);
    } catch (const std::exception& e) {
        // Catch any exceptions that may arise during the execution of the patch command
        std::cout << "Error executing patch command: " << e.what() << std::endl;
        m_menu.displayBadRequestError("400 Bad Request");
        return;
    }

    // Success response
    m_menu.displayMessage("204 No Content");
}
