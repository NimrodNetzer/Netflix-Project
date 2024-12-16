#ifndef USER_H
#define USER_H
#include <vector>
#include "objects/Movie.h"

// User class represents a user in the movie recommendation system
class User {
private:
    const int userID;  // Unique identifier for the user
    std::vector<Movie> moviesWatched;  // List of movies that the user has watched

public:
    // Constructor to initialize the user with a given ID
    // @param id: The unique identifier for the user
    User(const int id) : userID(id) {}

    // Copy constructor to create a new User object by copying another User object
    // @param other: The User object to copy from
    User(const User& other) : userID(other.userID), moviesWatched(other.moviesWatched) {}

    // Getter for the user ID
    // @return: The unique ID of the user
    int getUserID() const;

    // Adds a movie to the list of movies the user has watched
    // @param movie: The Movie object to add to the user's watched list
    void addMovieWatched(Movie movie);

    // Getter for the list of movies the user has watched
    // @return: A vector containing all the Movie objects the user has watched
    std::vector<Movie> getMoviesWatched() const;
};

#endif //USER_H
