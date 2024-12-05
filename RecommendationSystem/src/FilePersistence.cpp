#include "FilePersistence.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
namespace fs = std::filesystem;

// Gets vectors of movies and users in the system and saves them to files.
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
    fs::path dataDir = this->folderName;
    fs::path moviesDir = dataDir / "movies";
    fs::path usersDir = dataDir / "users";
    if (!fs::exists(moviesDir) || !fs::exists(usersDir)) {
        return;
    }
    // Load movies
    std::map<int, Movie> moviesMap; // store movies in map so we can attach them to users
    for (const auto& filePath : fs::directory_iterator(moviesDir)) {
        int id = atoi(filePath.path().filename().string().c_str());
        Movie movie(id);
        moviesMap.insert({id, movie});
        movies.push_back(movie);
    }
    // Load Users
    for (const auto& filePath : fs::directory_iterator(usersDir)) {
        int id = atoi(filePath.path().filename().string().c_str());
        User user(id);
        std::ifstream userFile(usersDir /  std::to_string(id));
        std::string line;
        std::getline(userFile, line);
        std::istringstream stream(line);
        int movieID;

        // Process each movie id
        while (stream >> movieID) {
            user.addMovieWatched(moviesMap[movieID]);
        }
        users.push_back(user);

    }

}
