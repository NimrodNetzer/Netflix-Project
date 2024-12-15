#include "recommend.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "DataManager.h"
#include "recommendAlgo.h"

// Constructor for the 'recommend' class
recommend::recommend() {}

// Validates the input string for the 'recommend' command
void recommend::validateString(std::string s) {
    std::istringstream iss(s);
    int userID, movieID;

    // Trim leading/trailing whitespace
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

    // Check if movieID exists and is valid
    if (!(iss >> movieID)) {
        throw std::invalid_argument("");
    }

    // Validate that the movieID is non-negative
    if (movieID < 0) {
        throw std::invalid_argument("");
    }

    // Ensure no additional invalid characters are present
    std::string extra;
    if (iss >> extra) {
        throw std::invalid_argument("");
    }

    // Additional domain-specific validations (if applicable)
    // Example: Validate if userID or movieID ranges are reasonable.
    if (userID > 1'000'000 || movieID > 1'000'000) {  // Example range check
        throw std::invalid_argument("");
    }
}

// Executes the 'recommend' command
void recommend::execute(std::string s) {
    try {
        validateString(s);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    DataManager& data_manager = DataManager::getInstance();
    std::istringstream iss(s);
    int userID, movieID;
    iss >> userID >> movieID;

    // Check if user exists
    if (!data_manager.hasUser(userID)) {
        return;
    }

    // Check if movie exists
    if (!data_manager.hasMovie(movieID)) {
        return;
    }

    // Calculate recommendations
    std::vector<int> sortedMovies = combineAndCalculateMoviesRelevance(
            data_manager.getUser(userID), data_manager.getMovie(movieID));

    // Output the sorted list of movie IDs
    for (size_t i = 0; i < sortedMovies.size(); ++i) {
        std::cout << sortedMovies[i];
        if (i < sortedMovies.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
