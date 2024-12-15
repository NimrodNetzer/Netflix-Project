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
    recommend();

    // Method to execute some functionality with the movies and users
    void execute(std::string s) override;

    void validateString(std::string s);
};


#endif //RECOMMENDATIONSYSTEM_RECOMMEND_H
