#ifndef MY_TEST_ADD_H
#define MY_TEST_ADD_H

#include <vector>
#include "movie.h"
#include "user.h"
#include "icommand.h"  // Include the ICommand interface

class add : public ICommand {
public:
    // Constructor that initializes the add class with vectors of movies and users
    add(std::vector<Movie>& movies, std::vector<User>& users);

    // Method to execute some functionality with the movies and users
    void execute(std::string s);

private:
    std::vector<Movie>& m_movies;  // Reference to the vector of movies
    std::vector<User>& m_users;    // Reference to the vector of users
};

#endif // MY_TEST_ADD_H
