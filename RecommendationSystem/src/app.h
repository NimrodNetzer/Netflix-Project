#ifndef APP_H
#define APP_H

#include <map>
#include <vector>
#include <string>
#include "ICommand.h"
#include "movie.h"
#include "user.h"

// The `app` class serves as the main application interface.
// It manages commands, movies, and users, and runs the application loop.
class app {
public:
    // Constructor to initialize the app with commands, movies, and users.
    app(const std::map<std::string, ICommand*>& commands,
        std::vector<Movie>& movies,
        std::vector<User>& users);

    // Main application loop to process commands interactively.
    void run();

private:
    // A map of command strings to their corresponding command objects.
    std::map<std::string, ICommand*> m_commands;

    // A vector holding all movies in the application.
    std::vector<Movie> m_movies;

    // A vector holding all users in the application.
    std::vector<User> m_users;
};

#endif // APP_H
