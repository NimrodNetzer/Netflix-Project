#include "FilePersistence.h"

#include "DataManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
namespace fs = std::filesystem;

// Gets vectors of movies and users in the system and saves them to files.
void FilePersistence::Save() {
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
    DataManager& data_manager = DataManager::getInstance();
    // Save movies
    for (const int movieId : data_manager.getMovieIds()) {
        int id =  movieId;
        std::ofstream movieFile(moviesDir /  std::to_string(id));
        movieFile.close();
    }
    // Save users
    for (const int userId : data_manager.getUserIds()) {
        int id = userId;
        std::ofstream userFile(usersDir /  std::to_string(id));
        bool first = true;
        for (const Movie& movie : data_manager.getMoviesWatchedByUser(userId)) {
            if(!first) {
                userFile << " ";
            }
            first = false;
            userFile << movie.getMovieID();
        }
        userFile.close();
    }
}

void FilePersistence::Load() {
    fs::path dataDir = this->folderName;
    fs::path moviesDir = dataDir / "movies";
    fs::path usersDir = dataDir / "users";
    if (!fs::exists(moviesDir) || !fs::exists(usersDir)) {
        return;
    }
    DataManager& data_manager = DataManager::getInstance();
    // Load movies
    for (const auto& filePath : fs::directory_iterator(moviesDir)) {
        int id = atoi(filePath.path().filename().string().c_str());
        Movie movie(id);
        data_manager.addMovie(movie);
    }
    // Load Users
    for (const auto& filePath : fs::directory_iterator(usersDir)) {
        int id = atoi(filePath.path().filename().string().c_str());
        User user(id);
        std::ifstream userFile(usersDir /  std::to_string(id));
        std::string line;
        std::getline(userFile, line);
        std::istringstream stream(line);
        data_manager.addUser(user);

        int movieID;
        // Process each movie id
        while (stream >> movieID) {
            data_manager.addUserWatchedMovie(user.getUserID(), movieID);
        }

    }

}
