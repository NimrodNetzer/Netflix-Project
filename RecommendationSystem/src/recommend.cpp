#include <sstream>
#include <iostream>
#include <algorithm>
#include "recommend.h"
#include "recommendAlgo.h"
#include <vector>

// Constructor implementation that initializes the 'recommend' class with lists of movies and users
recommend::recommend(std::vector<Movie>& movies, std::vector<User>& users)
        : m_movies(movies), m_users(users) {}

// Executes the recommendation command based on a provided input string
void recommend::execute(std::string s) {
    std::istringstream iss(s);  // Create a string stream to parse the input command
    int userID;

    // Extract the user ID from the command string. If extraction fails, print an error and return.
    if (!(iss >> userID)) {
        std::cout << "Invalid command format: missing or invalid user ID." << std::endl;
        return;
    }

    // Search for the user with the specified user ID in the list of users
    auto userIt = std::find_if(m_users.begin(), m_users.end(), [userID](const User &user) {
        return user.getUserID() == userID;  // Check if the current user has the specified ID
    });

    if (userIt == m_users.end()) {  // If user not found
        std::cout << "User with ID " << userID << " not found." << std::endl;
        return;
    }

    User *foundUser = &(*userIt);  // Pointer to the found user

    int movieID;

    // Extract the movie ID from the command string. If extraction fails, print an error and return.
    if (!(iss >> movieID)) {
        std::cout << "Invalid command format: missing or invalid movie ID." << std::endl;
        return;
    }

    // Search for the movie with the specified movie ID in the list of movies
    auto movieIt = std::find_if(m_movies.begin(), m_movies.end(), [movieID](const Movie &movie) {
        return movie.getMovieID() == movieID;  // Check if the current movie has the specified ID
    });

    if (movieIt == m_movies.end()) {  // If movie not found
        std::cout << "Movie with ID " << movieID << " not found." << std::endl;
        return;
    }

    Movie *foundMovie = &(*movieIt);  // Pointer to the found movie

    // Combine and calculate the relevance of movies
    std::vector<int> sortedMovies = combineAndCalculateMoviesRelevance(m_users, m_movies, *foundUser, *foundMovie);

    // Output the sorted list of movie IDs
    for (size_t i = 0; i < sortedMovies.size(); ++i) {
        std::cout << sortedMovies[i];
        if (i < sortedMovies.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
