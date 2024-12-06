#ifndef MY_TEST_ADD_H
#define MY_TEST_ADD_H

#include <vector>
#include "Movie.h"
#include "User.h"
#include "ICommand.h"  // Include the ICommand interface
#include "IPersistence.h"

class add : public ICommand {
public:
    // Constructor that initializes the add class with vectors of movies and users
    add(std::vector<Movie>& movies, std::vector<User>& users, IPersistence* persistence);

    // Method to execute some functionality with the movies and users
    void execute(std::string s) override;

private:
    std::vector<Movie>& m_movies;  // Reference to the vector of movies
    std::vector<User>& m_users;    // Reference to the vector of users
    IPersistence* m_persistence;
};

#endif // MY_TEST_ADD_H
