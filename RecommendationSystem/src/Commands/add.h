#ifndef MY_TEST_ADD_H
#define MY_TEST_ADD_H

#include <vector>
#include "../objects/Movie.h"
#include "../objects/User.h"
#include "../Interfaces/ICommand.h"  // Include the ICommand interface
#include "../Interfaces/IPersistence.h"

class add : public ICommand {
public:
    // Constructor that initializes the add class with vectors of movies and users
    add();

    // Method to execute some functionality with the movies and users
    void execute(std::string s) override;

    void validateString(std::string s);
};

#endif // MY_TEST_ADD_H
