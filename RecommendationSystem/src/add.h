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
    add();

    // Method to execute some functionality with the movies and users
    void execute(std::string s) override;

    void validateString(std::string s);
};

#endif // MY_TEST_ADD_H
