#include <iostream>
#include "ICommand.h"
#include "add.h"
#include "app.h"
#include "help.h"
#include <map>
#include <vector>

int main() {
    // Create sample vectors of movies and users
    std::vector<Movie> movies = {};
    std::vector<User> users = {};

    // Create a map to associate command IDs with ICommand instances
    std::map<std::string, ICommand*> commands;

    // Create the 'add' command instance and add it to the commands map
    ICommand* addCommand = new add(movies, users);
    commands["add"] = addCommand;

    // Create the 'help' command instance and add it to the commands map
    ICommand* helpCommand = new Help();
    commands["help"] = helpCommand;

    // Create the application instance with the command map, movies, and users
    app application(commands, movies, users);
    application.run();

    // Clean up dynamically allocated commands to prevent memory leaks
    delete addCommand;
    delete helpCommand;

    return 0;
}
