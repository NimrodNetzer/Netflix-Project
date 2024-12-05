//
// Created by orlib on 05/12/2024.
//

#ifndef RECOMMENDATIONSYSTEM_RECOMMEND_H
#define RECOMMENDATIONSYSTEM_RECOMMEND_H


#include <vector>
#include "ICommand.h"
#include "Movie.h"
#include "User.h"

class recommend : public ICommand {
public:
    recommend(std::vector<Movie>& movies, std::vector<User>& users);

    // Method to execute some functionality with the movies and users
    void execute(std::string s) override;

private:
    std::vector<Movie>& m_movies;  // Reference to the vector of movies
    std::vector<User>& m_users;    // Reference to the vector of users
};


#endif //RECOMMENDATIONSYSTEM_RECOMMEND_H
