#include <sstream>
#include <iostream>
#include <algorithm>
#include "recommend.h"

#include <DataManager.h>

#include "recommendAlgo.h"
#include <vector>

// Constructor implementation that initializes the 'recommend' class with lists of movies and users
recommend::recommend() {}

// Executes the recommendation command based on a provided input string
void recommend::execute(std::string s) {
    DataManager& data_manager = DataManager::getInstance();
    std::istringstream iss(s);  // Create a string stream to parse the input command
    int userID;

    // Extract the user ID from the command string. If extraction fails, print an error and return.
    if (!(iss >> userID)) {
        std::cout << "Invalid command format: missing or invalid user ID." << std::endl;
        return;
    }

    // Search for the user with the specified user ID in the list of users
    bool userExists = data_manager.hasUser(userID);

    if (!userExists) {  // If user not found
        std::cout << "User with ID " << userID << " not found." << std::endl;
        return;
    }

    int movieID;

    // Extract the movie ID from the command string. If extraction fails, print an error and return.
    if (!(iss >> movieID)) {
        std::cout << "Invalid command format: missing or invalid movie ID." << std::endl;
        return;
    }

    // Search for the movie with the specified movie ID in the list of movies
    bool movieExists = data_manager.hasMovie(movieID);
    if (!movieExists) {  // If movie not found
        std::cout << "Movie with ID " << movieID << " not found." << std::endl;
        return;
    }

    // Combine and calculate the relevance of movies
    std::vector<int> sortedMovies = combineAndCalculateMoviesRelevance(data_manager.getUser(userID) ,data_manager.getMovie(movieID));

    // Output the sorted list of movie IDs
    for (size_t i = 0; i < sortedMovies.size(); ++i) {
        std::cout << sortedMovies[i];
        if (i < sortedMovies.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
