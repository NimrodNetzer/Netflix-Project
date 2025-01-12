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
    std::unique_lock lock(dataMutex); // Lock for write access
    users.emplace(user.getUserID(), user);
    moviesWatchedByUser[user.getUserID()] = {};
}

// Adds a new movie to the system
void DataManager::addMovie(const Movie& movie) {
    std::unique_lock lock(dataMutex); // Lock for write access
    movies.emplace(movie.getMovieID(), movie);
    usersWhoWatchedMovie[movie.getMovieID()] = {};
}

// Records that a user has watched a specific movie
void DataManager::addUserWatchedMovie(int userId, int movieId) {
    std::unique_lock lock(dataMutex); // Lock for write access
    moviesWatchedByUser[userId].push_back(movieId);
    usersWhoWatchedMovie[movieId].push_back(userId);
}

// Records that a user has watched multiple movies
void DataManager::addUserWatchedMovies(int userId, const std::vector<int>& movieIds) {
    std::unique_lock lock(dataMutex); // Lock for write access
    for (int movieId : movieIds) {
        moviesWatchedByUser[userId].push_back(movieId);
        usersWhoWatchedMovie[movieId].push_back(userId);
    }
}

// Retrieves a user by their ID
const User& DataManager::getUser(int userId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    return users.at(userId); // Throws std::out_of_range if userId doesn't exist
}

// Retrieves a movie by its ID
const Movie& DataManager::getMovie(int movieId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    return movies.at(movieId); // Throws std::out_of_range if movieId doesn't exist
}

// Checks if a user exists in the system
bool DataManager::hasUser(int userId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    return users.find(userId) != users.end();
}

// Checks if a movie exists in the system
bool DataManager::hasMovie(int movieId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    return movies.find(movieId) != movies.end();
}

// Checks if a specific user has watched a specific movie
bool DataManager::userWatchedMovie(int userId, int movieId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    auto userIt = moviesWatchedByUser.find(userId);
    if (userIt == moviesWatchedByUser.end()) {
        return false;
    }
    const auto& watchedMovies = userIt->second;
    return std::find(watchedMovies.begin(), watchedMovies.end(), movieId) != watchedMovies.end();
}

// Retrieves the list of movie IDs watched by a specific user
std::vector<int> DataManager::getMoviesWatchedByUser(int userId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    return moviesWatchedByUser.at(userId);
}

// Retrieves the list of user IDs who have watched a specific movie
std::vector<int> DataManager::getUsersWhoWatchedMovie(int movieId) const {
    std::shared_lock lock(dataMutex); // Lock for read access
    return usersWhoWatchedMovie.at(movieId);
}

// Retrieves a list of all user IDs
std::vector<int> DataManager::getUserIds() const {
    std::shared_lock lock(dataMutex); // Lock for read access
    std::vector<int> userIds;
    for (const auto& pair : users) {
        userIds.push_back(pair.first);
    }
    return userIds;
}

// Retrieves a list of all movie IDs
std::vector<int> DataManager::getMovieIds() const {
    std::shared_lock lock(dataMutex); // Lock for read access
    std::vector<int> movieIds;
    for (const auto& pair : movies) {
        movieIds.push_back(pair.first);
    }
    return movieIds;
}

// Resets the DataManager by clearing all stored data
void DataManager::reset() {
    std::unique_lock lock(dataMutex); // Lock for write access
    users.clear();
    movies.clear();
    moviesWatchedByUser.clear();
    usersWhoWatchedMovie.clear();
    persistence = nullptr;
}

// Sets the persistence strategy
void DataManager::setPersistenceStrategy(IPersistence* persistence) {
    std::unique_lock lock(persistenceMutex); // Lock for write access
    DataManager::persistence = persistence;
}

// Saves the data using the persistence strategy
void DataManager::save() const {
    std::unique_lock lock(persistenceMutex); // Lock for read access
    if (!persistence) {
        throw std::runtime_error("Persistence object is not initialized.");
    }
    persistence->Save();
}

// Loads the data using the persistence strategy
void DataManager::load() const {
    std::unique_lock lock(persistenceMutex); // Lock for read access
    if (!persistence) {
        throw std::runtime_error("Persistence object is not initialized.");
    }
    persistence->Load();
}

// Function that removes one or more movies from the user's watched movies list
void DataManager::deleteUserMovies(int userId, const std::vector<int>& movieIds) {
    std::unique_lock dataLock(dataMutex);

    // Check if user exists directly from the users map
    auto userIt = users.find(userId);
    if (userIt != users.end()) {
        // For each movie, verify it exists, then remove relationships
        for (int movieId : movieIds) {
            auto movieIt = movies.find(movieId);
            if (movieIt != movies.end()) {
                // Remove the movie from this user's watched list
                auto& watchedMovies = moviesWatchedByUser[userId];
                auto it = std::find(watchedMovies.begin(), watchedMovies.end(), movieId);
                if (it != watchedMovies.end()) {
                    watchedMovies.erase(it);
                }

                // Remove the user from this movie's watchers list
                auto& usersWhoWatched = usersWhoWatchedMovie[movieId];
                usersWhoWatched.erase(
                    std::remove(usersWhoWatched.begin(), usersWhoWatched.end(), userId),
                    usersWhoWatched.end()
                );
            }
        }
    }

    // Release the data lock before acquiring the persistence lock
    dataLock.unlock();

    // Acquire exclusive (write) access to the persistence strategy
    std::unique_lock persistenceLock(persistenceMutex);

    // If persistence is initialized, save changes
    if (persistence) {
        persistence->Save();
    }
}

