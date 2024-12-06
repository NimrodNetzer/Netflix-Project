#include "DataManager.h"

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

void DataManager::addUser(const User& user) {
    users.emplace(user.getUserID(), user);
}

void DataManager::addMovie(const Movie& movie) {
    movies.emplace(movie.getMovieID(), movie);
}

void DataManager::addUserWatchedMovie(int userId, int movieId) {
    moviesWatchedByUser[userId].push_back(movieId);
    usersWhoWatchedMovie[movieId].push_back(userId);
}

const User& DataManager::getUser(int userId) const {
    return users.at(userId);
}

const Movie& DataManager::getMovie(int movieId) const {
    return movies.at(movieId);
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

