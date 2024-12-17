//
// Created by ido on 12/6/24.
//

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <unordered_map>
#include <vector>
#include "../Interfaces/IPersistence.h"
#include "../objects/User.h"
#include "../objects/Movie.h"

class DataManager {
public:
    // Returns the singleton instance of the DataManager
    static DataManager& getInstance();

    // Adds a new user to the system
    void addUser(const User& user);

    // Adds a new movie to the system
    void addMovie(const Movie& movie);

    // Records that a specific user has watched a specific movie
    void addUserWatchedMovie(int userId, int movieId);

    // Records that a user has watched multiple movies
    void addUserWatchedMovies(int userId, const std::vector<int>& movieIds);

    // Retrieves a user by their ID; throws an exception if the user doesn't exist
    const User& getUser(int userId) const;

    // Retrieves a movie by its ID; throws an exception if the movie doesn't exist
    const Movie& getMovie(int movieId) const;

    // Checks if a user exists in the system
    bool hasUser(int userId) const;

    // Checks if a movie exists in the system
    bool hasMovie(int movieId) const;

    // Checks if a user has watched a specific movie
    bool userWatchedMovie(int userId, int movieId) const;

    // Returns the list of movies watched by a specific user
    std::vector<int> getMoviesWatchedByUser(int userId) const;

    // Returns the list of users who have watched a specific movie
    std::vector<int> getUsersWhoWatchedMovie(int movieId) const;

    // Returns the list of all user IDs in the system
    std::vector<int> getUserIds() const;

    // Returns the list of all movie IDs in the system
    std::vector<int> getMovieIds() const;

    // Clears all stored data and resets the DataManager
    void reset();

    // Sets the persistence strategy (used for saving/loading data)
    void setPersistenceStrategy(IPersistence* persistence);

    // Saves data using the current persistence strategy
    void save() const;

    // Loads data using the current persistence strategy
    void load() const;

private:
    // Private constructor to enforce the singleton pattern
    DataManager() = default;

    // Map storing users by their IDs
    std::unordered_map<int, User> users;

    // Map storing movies by their IDs
    std::unordered_map<int, Movie> movies;

    // Map storing the list of movie IDs watched by each user
    std::unordered_map<int, std::vector<int>> moviesWatchedByUser;

    // Map storing the list of user IDs who watched each movie
    std::unordered_map<int, std::vector<int>> usersWhoWatchedMovie;

    // Pointer to the persistence strategy
    IPersistence* persistence = nullptr;

    // Deleted copy constructor and assignment operator to prevent copying
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;
};

#endif //DATAMANAGER_H
