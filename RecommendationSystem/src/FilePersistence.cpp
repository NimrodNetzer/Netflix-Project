#include "FilePersistence.h"

#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;

void FilePersistence::Save(std::vector<Movie> &movies, std::vector<User> &users) {
    // Initialize folders
    fs::path dataDir = this->folderName;
    if (!fs::exists(dataDir)) {
        fs::create_directory(dataDir);
    }
    fs::path moviesDir = dataDir / "movies";
    fs::path usersDir = dataDir / "users";
    if (!fs::exists(moviesDir)) {
        fs::create_directory(moviesDir);
    }
    if (!fs::exists(usersDir)) {
        fs::create_directory(usersDir);
    }
    // Save movies
    for (const Movie& movie : movies) {
        int id =  movie.getMovieID();
        std::ofstream movieFile(moviesDir /  std::to_string(id));
        movieFile.close();
    }
    // Save users
    for (const User& user : users) {
        int id = user.getUserID();
        std::ofstream userFile(usersDir /  std::to_string(id));
        bool first = true;
        for (const Movie& movie : user.getMoviesWatched()) {
            if(!first) {
                userFile << " ";
            }
            first = false;
            userFile << movie.getMovieID();
        }
        userFile.close();
    }
}

void FilePersistence::Load(std::vector<Movie> &movies, std::vector<User> &users) {

}
