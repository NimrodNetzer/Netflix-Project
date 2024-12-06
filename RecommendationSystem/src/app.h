#ifndef APP_H
#define APP_H

#include <map>        // For std::map to store command mappings
#include <vector>    // For std::vector to store movies and users
#include <string>    // For std::string to handle command and input strings
#include "ICommand.h" // Include ICommand interface for command execution
#include "Movie.h"    // Include Movie class definition
#include "User.h"     // Include User class definition
#include "IMenu.h"    // Include IMenu interface for menu interaction

// The App class manages the application logic, delegating interaction to IMenu.
class App {
public:
    // Constructor that initializes the App object with references to menu, commands, movies, and users.
    App(IMenu& menu, const std::map<std::string, ICommand*>& commands,
        std::vector<Movie>& movies, std::vector<User>& users);

    // Main method to run the application, processing commands in an interactive loop.
    void run();

private:
    // A reference to an IMenu instance used for user interaction and command input.
    IMenu& m_menu;

    // A map that associates command IDs (strings) with their corresponding command objects.
    std::map<std::string, ICommand*> m_commands;

    // A vector holding all Movie objects available in the application.
    std::vector<Movie> m_movies;

    // A vector holding all User objects available in the application.
    std::vector<User> m_users;
};

#endif // APP_H
