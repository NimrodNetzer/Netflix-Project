#include <sys/socket.h>  // For send()
#include <cstring>       // For strlen()
#include "Commands/patch.h"
#include "Data/DataManager.h"

// Executes the 'PATCH' command and communicates via the socket
void patch::execute(std::string s, int clientSocket) {
    std::string response;

    try {
        // Validate input string
        validateString(s);
    } catch (const std::invalid_argument& e) {
        // Send a "400 Bad Request" response
        response = "400 Bad Request\n";
        send(clientSocket, response.c_str(), response.size(), 0);
        return;
    }

    DataManager& data_manager = DataManager::getInstance();
    std::istringstream iss(s);
    int userID;
    iss >> userID;

    std::vector<int> movieIDs;
    int movieID;
    while (iss >> movieID) {
        movieIDs.push_back(movieID);
    }

    // Check if the user exists
    if (!data_manager.hasUser(userID)) {
        response = "409 Conflict: User does not exist\n";
        send(clientSocket, response.c_str(), response.size(), 0);
        return;
    }

    // Check if all movies exist
    for (int movieID : movieIDs) {
        if (!data_manager.hasMovie(movieID)) {
            response = "409 Conflict: Movie ID " + std::to_string(movieID) + " does not exist\n";
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
    }

    // If validation passes, reuse the 'add' command logic
    add addCommand;
    addCommand.execute(s, clientSocket);
}
