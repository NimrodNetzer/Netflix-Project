#include "../Commands/add.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "../Data/DataManager.h"
#include <unordered_set>

// Constructor for the 'add' class
add::add() {}

// Validates the input string for the 'add' command
void add::validateString(std::string s) {
    std::istringstream iss(s);
    int userID;

    // Trim leading/trailing whitespace (optional, depending on your environment)
    s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
    s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check if the input is empty
    if (s.empty()) {
        throw std::invalid_argument("");
    }

    // Check if userID exists and is valid
    if (!(iss >> userID)) {
        throw std::invalid_argument("");
    }

    // Validate that the userID is non-negative
    if (userID < 0) {
        throw std::invalid_argument("");
    }

    // Ensure there is at least one movie ID
    std::vector<int> movieIDs;
    int movieID;

    while (iss >> movieID) {
        // Validate that movieID is non-negative
        if (movieID < 0) {
            throw std::invalid_argument("");
        }
        movieIDs.push_back(movieID);
    }

    // Check if no movie IDs were found
    if (movieIDs.empty()) {
        throw std::invalid_argument("");
    }

    // Ensure no additional invalid characters are present
    if (!iss.eof()) {
        throw std::invalid_argument("");
    }

    // Validate the size of the command string (optional, if limits are defined)
    if (s.size() > 1024) { // Example limit: 1024 characters
        throw std::invalid_argument("");
    }

    // Additional domain-specific validations (if applicable)
    // For example, you can check for duplicate movie IDs or unreasonable user/movie ID ranges.
    std::unordered_set<int> uniqueMovieIDs(movieIDs.begin(), movieIDs.end());
    if (uniqueMovieIDs.size() != movieIDs.size()) {
        throw std::invalid_argument("");
    }
}


// Executes the 'add' command
void add::execute(std::string s) {
    try {
        validateString(s);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
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

    // Check if user exists, create if not
    if (!data_manager.hasUser(userID)) {
        data_manager.addUser(User(userID));
    }

    // Add movies to the user
    for (int movieID : movieIDs) {
        if (data_manager.userWatchedMovie(userID, movieID)) {
            continue;
        }

        if (!data_manager.hasMovie(movieID)) {
            data_manager.addMovie(Movie(movieID));
        }

        data_manager.addUserWatchedMovie(userID, movieID);
    }

    // Save changes
    data_manager.save();
}
