//
// Created by orlib on 02/12/2024.
//
#ifndef MY_TEST_ADD_H
#define MY_TEST_ADD_H

#include <vector>
#include "movie.h"
#include "user.h"

class add {
public:
    // Constructor that initializes the class with vectors of movies and users
    add(const std::vector<Movie>& movies, const std::vector<User>& users);

    // Method to execute some functionality with the movies and users
    void execute(std::string s) const;

private:
    std::vector<Movie> m_movies;  // Vector to store movies
    std::vector<User> m_users;    // Vector to store users
};

#endif //MY_TEST_ADD_H
