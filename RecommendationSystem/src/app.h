#ifndef APP_H
#define APP_H

#include <map>
#include <vector>
#include "ICommand.h"
#include "movie.h"
#include "user.h"

class app {
public:
    // Constructor that initializes the app with command map, movies, and users
    app(const std::map<std::string, ICommand*>& commands,
        std::vector<Movie>& movies,
        std::vector<User>& users);

    // Method to start the application
    void run();

private:
    std::map<std::string, ICommand*> m_commands;  // Map of command IDs and their corresponding ICommand instances
    std::vector<Movie> m_movies;                  // Vector of movies
    std::vector<User> m_users;                    // Vector of users
};

#endif // APP_H
