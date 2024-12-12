#include "DataManager.h"

#include <algorithm>
#include <stdexcept>

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

void DataManager::addUser(const User& user) {
    users.emplace(user.getUserID(), user);
    moviesWatchedByUser[user.getUserID()] = {};
}

void DataManager::addMovie(const Movie& movie) {
    movies.emplace(movie.getMovieID(), movie);
    usersWhoWatchedMovie[movie.getMovieID()] = {};
}

void DataManager::addUserWatchedMovie(int userId, int movieId) {
    moviesWatchedByUser[userId].push_back(movieId);
    usersWhoWatchedMovie[movieId].push_back(userId);
}


void DataManager::addUserWatchedMovies(int userId, const std::vector<int>& movieIds) {
    for (int movieId : movieIds) {
        moviesWatchedByUser[userId].push_back(movieId);
        usersWhoWatchedMovie[movieId].push_back(userId);
    }
}

const User& DataManager::getUser(int userId) const {
    return users.at(userId);
}

const Movie& DataManager::getMovie(int movieId) const {
    return movies.at(movieId);
}

bool DataManager::hasUser(int userId) const {
    return users.find(userId) != users.end();
}

bool DataManager::hasMovie(int movieId) const {
    return movies.find(movieId) != movies.end();
}

bool DataManager::userWatchedMovie(int userId, int movieId) const {
    // Check if the user exists
    auto userIt = moviesWatchedByUser.find(userId);
    if (userIt == moviesWatchedByUser.end()) {
        return false; // User does not exist, so they haven't watched the movie
    }

    // Check if the movie is in the list of movies watched by the user
    const auto& watchedMovies = userIt->second;
    return std::find(watchedMovies.begin(), watchedMovies.end(), movieId) != watchedMovies.end();
}

std::vector<int> DataManager::getMoviesWatchedByUser(int userId) const {
    return moviesWatchedByUser.at(userId);
}

std::vector<int> DataManager::getUsersWhoWatchedMovie(int movieId) const {
    return usersWhoWatchedMovie.at(movieId);
}

std::vector<int> DataManager::getUserIds() const {
    std::vector<int> userIds;
    for (const auto& pair : users) {
        userIds.push_back(pair.first);
    }
    return userIds;
}

std::vector<int> DataManager::getMovieIds() const {
    std::vector<int> movieIds;
    for (const auto& pair : movies) {
        movieIds.push_back(pair.first);
    }
    return movieIds;
}

void DataManager::reset() {
    users.clear();
    movies.clear();
    moviesWatchedByUser.clear();
    usersWhoWatchedMovie.clear();
    persistence = nullptr;
}

void DataManager::setPersistenceStrategy(IPersistence *persistence) {
    DataManager::persistence = persistence;
}

void DataManager::save() const {
    if(!persistence)
        throw std::runtime_error("Persistence object is not initialized.");
    persistence->Save();
}

void DataManager::load() const {
    if(!persistence)
        throw std::runtime_error("Persistence object is not initialized.");
    persistence->Load();
}
