#include "Delete.h"
#include <sstream>
#include <iostream>
#include <unordered_set>
#include "../Data/DataManager.h"

Delete::Delete(IMenu& menu) : m_menu(menu) {}

// Validates the input string for the 'Delete' command
void Delete::validateString(const std::string& s) {
    std::istringstream iss(s);
    int userID;

    // Trim leading/trailing whitespace (optional, depending on your environment)
    std::string trimmed = s;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check if the input is empty
    if (trimmed.empty()) {
        throw std::invalid_argument("Input string is empty.");
    }

    // Check if userID exists and is valid
    if (!(iss >> userID)) {
        throw std::invalid_argument("Invalid user ID.");
    }

    // Validate that the userID is non-negative
    if (userID < 0) {
        throw std::invalid_argument("User ID cannot be negative.");
    }

    // Ensure there is at least one movie ID
    std::vector<int> movieIDs;
    int movieID;

    while (iss >> movieID) {
        // Validate that movieID is non-negative
        if (movieID < 0) {
            throw std::invalid_argument("Movie ID cannot be negative.");
        }
        movieIDs.push_back(movieID);
    }

    // Check if no movie IDs were found
    if (movieIDs.empty()) {
        throw std::invalid_argument("At least one movie ID is required.");
    }

    // Ensure no additional invalid characters are present
    if (!iss.eof()) {
        throw std::invalid_argument("Invalid characters found after movie IDs.");
    }

    // Validate the size of the command string (optional, if limits are defined)
    if (s.size() > 1024) { // Example limit: 1024 characters
        throw std::invalid_argument("Input string exceeds maximum length.");
    }

    // Additional domain-specific validations (if applicable)
    // For example, you can check for duplicate movie IDs or unreasonable user/movie ID ranges.
    std::unordered_set<int> uniqueMovieIDs(movieIDs.begin(), movieIDs.end());
    if (uniqueMovieIDs.size() != movieIDs.size()) {
        throw std::invalid_argument("Duplicate movie IDs found.");
    }
}

void Delete::execute(std::string s) {
    // Validate the input string (e.g., ensure it's not empty)
    try {
        validateString(s); // This handles validation of the input
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        m_menu.displayBadRequestError("400 Bad Request");
        return;
    }

    // Extract the user ID and movie IDs from the input string
    DataManager& data_manager = DataManager::getInstance();
    std::istringstream iss(s);
    int userID;
    std::vector<int> movieIds;

    // Extract user ID from the string
    iss >> userID;

    // Extract movie IDs from the string
    int movieId;
    while (iss >> movieId) {
        movieIds.push_back(movieId);
    }

    // Check if the user exists
    if (!data_manager.hasUser(userID)) {
        std::cout << "User does not exist." << std::endl;
        m_menu.displayLogicError("404 Not Found");
        return;
    }

    // Check if the movie IDs exist in the user's watched movies list
    std::vector<int> nonExistentMovies;
    for (int movieId : movieIds) {
        if (!data_manager.userWatchedMovie(userID, movieId)) {
            nonExistentMovies.push_back(movieId);
        }
    }

    if (!nonExistentMovies.empty()) {
        std::cout << "The following movie IDs do not exist in the user's watched list: ";
        for (int nonExistentMovie : nonExistentMovies) {
            std::cout << nonExistentMovie << " ";
        }
        std::cout << std::endl;
        m_menu.displayLogicError("404 Not Found");
        return;
    }

    // Execute the deletion of the movies from the user's watched list
    try {
        data_manager.deleteUserMovies(userID, movieIds);
    } catch (const std::exception& e) {
        // Handle any exceptions thrown by the data manager
        std::cout << "Error deleting movies: " << e.what() << std::endl;
        m_menu.displayBadRequestError("400 Bad Request");
        return;
    }

    // Success response
    m_menu.displayMessage("204 No Content");
}
