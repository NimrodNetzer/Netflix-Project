//
// Created by ido on 12/6/24.
//

#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <unordered_map>

#include "IPersistence.h"
#include "User.h"


class DataManager {
public:
    static DataManager& getInstance();
    
    void addUser(const User& user);
    void addMovie(const Movie& movie);
    void addUserWatchedMovie(int userId, int movieId);

    const User& getUser(int userId) const;
    const Movie& getMovie(int movieId) const;

    std::vector<int> getMoviesWatchedByUser(int userId) const;
    std::vector<int> getUsersWhoWatchedMovie(int movieId) const;

    std::vector<int> getUserIds() const;
    std::vector<int> getMovieIds() const;
    void reset();
    void addUserWatchedMovies(int userId, const std::vector<int> &movieIds);

    void reset();
    void setPersistenceStrategy(IPersistence* persistence);
    void save() const;
    void load() const;

private:
    DataManager() = default;

    std::unordered_map<int, User> users;
    std::unordered_map<int, Movie> movies;
    std::unordered_map<int, std::vector<int>> moviesWatchedByUser;
    std::unordered_map<int, std::vector<int>> usersWhoWatchedMovie;
    IPersistence* persistence = nullptr;
    // Delete copy and assignment
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

};




#endif //DATAMANAGER_H
