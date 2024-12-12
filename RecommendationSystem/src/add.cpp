#include "add.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "DataManager.h"

// Constructor implementation that initializes the 'add' command with DataManager
add::add()  {}

// Main execute method that processes the command string to add movies to a user.
// The command format should include a user ID followed by one or more movie IDs.
void add::execute(std::string s) {
    DataManager& data_manager = DataManager::getInstance();
    std::istringstream iss(s);  // Create a string stream to parse the input command
    int userID;

    // Extract the user ID from the command string. If extraction fails, print an error and return.
    if (!(iss >> userID)) {
        std::cout << "Invalid command format: missing user ID." << std::endl;
        return;
    }

    std::vector<int> movieIDs;  // Vector to store the movie IDs extracted from the command
    int movieID;

    // Extract each movie ID from the command string and store it in the movieIDs vector
    while (iss >> movieID) {
        movieIDs.push_back(movieID);
    }

    // Check if any movie IDs were provided in the command; print an error and return if none were found
    if (movieIDs.empty()) {
        std::cout << "Invalid command format: at least one movie ID is required." << std::endl;
        return;
    }

    // Retrieve or create the user
    bool foundUser = data_manager.hasUser(userID);
    if (!foundUser) {
        std::cout << "User with ID " << userID << " not found. Creating a new user." << std::endl;
        data_manager.addUser(User(userID));
    }

    // Iterate through each movie ID provided in the command
    for (int movieID : movieIDs) {
        // Check if the user already has the movie associated with them
        if (data_manager.userWatchedMovie(userID, movieID)) {
            std::cout << "Movie ID " << movieID << " already associated with User ID " << userID << "." << std::endl;
            continue;
        }

        // Retrieve or create the movie
        bool foundMovie = data_manager.hasMovie(movieID);
        if (!foundMovie) {
            std::cout << "Movie ID " << movieID << " not found. Creating a new movie." << std::endl;
            data_manager.addMovie(Movie(movieID));
        }

        // Add the movie-user association via DataManager
        data_manager.addUserWatchedMovie(userID, movieID);
        std::cout << "Added Movie ID " << movieID << " to User ID " << userID << "." << std::endl;
    }

    // Save the changes through DataManager
    data_manager.save();
}