#include "DataManager.h"

#include <algorithm>
#include <stdexcept>

// Singleton instance of DataManager
DataManager& DataManager::getInstance() {
    static DataManager instance; // Ensures only one instance is created
    return instance;
}

// Adds a new user to the system
void DataManager::addUser(const User& user) {
    // Add the user to the 'users' map
    users.emplace(user.getUserID(), user);

    // Initialize the list of movies watched by this user
    moviesWatchedByUser[user.getUserID()] = {};
}

// Adds a new movie to the system
void DataManager::addMovie(const Movie& movie) {
    // Add the movie to the 'movies' map
    movies.emplace(movie.getMovieID(), movie);

    // Initialize the list of users who watched this movie
    usersWhoWatchedMovie[movie.getMovieID()] = {};
}

// Records that a user has watched a specific movie
void DataManager::addUserWatchedMovie(int userId, int movieId) {
    // Add the movie to the user's watched movies list
    moviesWatchedByUser[userId].push_back(movieId);

    // Add the user to the list of users who watched this movie
    usersWhoWatchedMovie[movieId].push_back(userId);
}

// Records that a user has watched multiple movies
void DataManager::addUserWatchedMovies(int userId, const std::vector<int>& movieIds) {
    for (int movieId : movieIds) {
        // Add each movie to the user's watched movies list
        moviesWatchedByUser[userId].push_back(movieId);

        // Add the user to the list of users who watched this movie
        usersWhoWatchedMovie[movieId].push_back(userId);
    }
}

// Retrieves a user by their ID
const User& DataManager::getUser(int userId) const {
    return users.at(userId); // Throws std::out_of_range if userId doesn't exist
}

// Retrieves a movie by its ID
const Movie& DataManager::getMovie(int movieId) const {
    return movies.at(movieId); // Throws std::out_of_range if movieId doesn't exist
}

// Checks if a user exists in the system
bool DataManager::hasUser(int userId) const {
    return users.find(userId) != users.end();
}

// Checks if a movie exists in the system
bool DataManager::hasMovie(int movieId) const {
    return movies.find(movieId) != movies.end();
}

// Checks if a specific user has watched a specific movie
bool DataManager::userWatchedMovie(int userId, int movieId) const {
    // Verify the user exists in the moviesWatchedByUser map
    auto userIt = moviesWatchedByUser.find(userId);
    if (userIt == moviesWatchedByUser.end()) {
        return false; // User not found, so they can't have watched the movie
    }

    // Check if the movie is in the user's watched movies list
    const auto& watchedMovies = userIt->second;
    return std::find(watchedMovies.begin(), watchedMovies.end(), movieId) != watchedMovies.end();
}

// Retrieves the list of movie IDs watched by a specific user
std::vector<int> DataManager::getMoviesWatchedByUser(int userId) const {
    return moviesWatchedByUser.at(userId); // Throws std::out_of_range if userId doesn't exist
}

// Retrieves the list of user IDs who have watched a specific movie
std::vector<int> DataManager::getUsersWhoWatchedMovie(int movieId) const {
    return usersWhoWatchedMovie.at(movieId); // Throws std::out_of_range if movieId doesn't exist
}

// Retrieves a list of all user IDs
std::vector<int> DataManager::getUserIds() const {
    std::vector<int> userIds;
    for (const auto& pair : users) {
        userIds.push_back(pair.first); // Collect all user IDs
    }
    return userIds;
}

// Retrieves a list of all movie IDs
std::vector<int> DataManager::getMovieIds() const {
    std::vector<int> movieIds;
    for (const auto& pair : movies) {
        movieIds.push_back(pair.first); // Collect all movie IDs
    }
    return movieIds;
}

// Resets the DataManager by clearing all stored data
void DataManager::reset() {
    users.clear(); // Clear all users
    movies.clear(); // Clear all movies
    moviesWatchedByUser.clear(); // Clear user-movie relationships
    usersWhoWatchedMovie.clear(); // Clear movie-user relationships
    persistence = nullptr; // Reset persistence strategy
}

// Sets the persistence strategy (e.g., saving/loading data to/from a file)
void DataManager::setPersistenceStrategy(IPersistence* persistence) {
    DataManager::persistence = persistence;
}

// Saves the data using the persistence strategy
void DataManager::save() const {
    if (!persistence) {
        throw std::runtime_error("Persistence object is not initialized."); // Ensure persistence is set
    }
    persistence->Save(); // Delegate the save operation to the persistence object
}

// Loads the data using the persistence strategy
void DataManager::load() const {
    if (!persistence) {
        throw std::runtime_error("Persistence object is not initialized."); // Ensure persistence is set
    }
    persistence->Load(); // Delegate the load operation to the persistence object
}
