#include "add.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <optional>  // For std::optional

// Constructor implementation that initializes the 'add' command with lists of movies and users
add::add(std::vector<Movie>& movies, std::vector<User>& users)
        : m_movies(movies), m_users(users) {}

// Helper function to search for a movie by its ID in the provided list of movies.
// Returns a pointer to the movie if found, or nullptr if not found.
Movie* findMovie(std::vector<Movie>& movies, int movieID) {
    for (auto& movie : movies) {
        if (movie.getMovieID() == movieID) {
            return &movie;  // Return a pointer to the movie if its ID matches
        }
    }
    return nullptr;  // Return nullptr if no matching movie is found
}

// Main execute method that processes the command string to add movies to a user.
// The command format should include a user ID followed by one or more movie IDs.
void add::execute(std::string s) {
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

    // Search for the user with the specified user ID in the list of users
    auto it = std::find_if(m_users.begin(), m_users.end(), [userID](const User& user) {
        return user.getUserID() == userID;  // Check if the current user has the specified ID
    });

    User* foundUser = nullptr;  // Pointer to hold the found user

    // If the user was found in the list, set the foundUser pointer to the user's address
    if (it != m_users.end()) {
        foundUser = &(*it);
    } else {
        // If the user wasn't found, create a new user and add them to the list
        std::cout << "User with ID " << userID << " not found. Creating a new user." << std::endl;
        m_users.push_back(User(userID));  // Create a new User object and add it to the list
        foundUser = &m_users.back();  // Set the foundUser pointer to the new user
    }

    // Iterate through each movie ID provided in the command
    for (int movieID : movieIDs) {
        bool existMovieUser = false;
        // Add the found or newly created movie to the user's list of watched movies
        for (Movie movie : foundUser->getMoviesWatched()) {
            if (movie.getMovieID() == movieID)
                existMovieUser = true;
        }
        if (existMovieUser == true)
            continue;
        // Search for the movie in the list of existing movies
        Movie* result = findMovie(m_movies, movieID);
        if (!result) {
            // If the movie wasn't found, create a new movie and add it to the list
            std::cout << "Movie ID " << movieID << " not found. Creating a new movie." << std::endl;
            m_movies.push_back(Movie(movieID));  // Create a new Movie object and add it to the list
            result = &m_movies.back();  // Set the result pointer to the new movie
        }


        foundUser->addMovieWatched(*result);
        std::cout << "Added Movie ID " << movieID << " to User ID " << userID << "." << std::endl;
    }
}
