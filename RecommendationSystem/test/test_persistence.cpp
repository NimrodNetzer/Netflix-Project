#include "test_persistence.h"

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "Interfaces/IPersistence.h"
#include "DataManage/FilePersistence.h"
#include "DataManage/DataManager.h"
namespace fs = std::filesystem;
const fs::path BASE_DIR = fs::path("test") / "test_data";

// Delete all files and directories withing a directory
void cleanDirectory(const fs::path& dir_path) {
    try {
        if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
            for (const auto& entry : fs::directory_iterator(dir_path)) {
                const auto& path = entry.path();
                if (fs::is_directory(path)) {
                    cleanDirectory(path);
                    fs::remove_all(path);
                } else {
                    fs::remove(path);
                }
            }
            std::cout << "Directory cleaned: " << dir_path << std::endl;
        } else {
            std::cout << "The provided path is not a valid directory." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Test the save method
TEST(Persistence, Save) {
    fs::path data_dir = BASE_DIR / "save";
    fs::path movies_dir = data_dir / "movies";
    fs::path users_dir = data_dir / "users";

    // Generate test case
    cleanDirectory(data_dir); // clean the test folder
    IPersistence* persistence = new FilePersistence(data_dir);
    DataManager& data_manager = DataManager::getInstance();
    data_manager.reset();
    data_manager.setPersistenceStrategy(persistence);
    data_manager.addMovie(100);
    data_manager.addMovie(200);
    data_manager.addMovie(300);
    data_manager.addUser(10);
    data_manager.addUser(20);
    data_manager.addUser(30);
    data_manager.addUserWatchedMovie(10, 100);
    data_manager.addUserWatchedMovie(10, 200);
    data_manager.addUserWatchedMovie(20, 300);
    data_manager.addUserWatchedMovie(30, 300);
    data_manager.addUserWatchedMovie(30, 200);
    data_manager.save();

    // Assertions for existence of directories
    ASSERT_TRUE(fs::exists(movies_dir));
    ASSERT_TRUE(fs::exists(users_dir));

    // Check saved movies
    std::vector<int> saved_movies;
    for (auto const& dir_entry : fs::directory_iterator(movies_dir)) {
        saved_movies.push_back(atoi(dir_entry.path().filename().c_str()));
    }
    std::sort(saved_movies.begin(), saved_movies.end());
    std::vector<int> expected_movies = {100, 200, 300};
    EXPECT_EQ(saved_movies, expected_movies);

    // Check saved users
    std::vector<int> saved_users;
    for (auto const& dir_entry : fs::directory_iterator(users_dir)) {
        saved_users.push_back(atoi(dir_entry.path().filename().c_str()));
    }
    std::vector<int> expected_users = {10, 20, 30};
    std::sort(saved_users.begin(), saved_users.end());
    EXPECT_EQ(saved_users, expected_users);

    // Check contents of user 30's file
    fs::path user_file_30 = users_dir / "30";
    std::ifstream file(user_file_30);
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "300 200");
    file.close();

    // Check contents of user 20's file
    fs::path user_file_20 = users_dir / "20";
    std::ifstream file1(user_file_20);
    std::getline(file1, line);
    EXPECT_EQ(line, "300");
    file1.close();
    data_manager.reset();
    delete persistence;
}

// Test the load method
TEST(Persistence, Load) {
    std::string data_dir = BASE_DIR / "load";
    DataManager& data_manager = DataManager::getInstance();
    data_manager.reset();
    IPersistence* persistence = new FilePersistence(data_dir);
    data_manager.setPersistenceStrategy(persistence);
    // load movies and users from the file
    data_manager.load();
    std::vector<int> expected_users = {10, 20, 30};
    std::vector<int> expected_movies = {100, 200, 300};
    // check if data was loaded
    ASSERT_FALSE(data_manager.getUserIds().empty());
    ASSERT_FALSE(data_manager.getMovieIds().empty());
    // Extract user IDs
    std::vector<int> actual_user_ids = data_manager.getUserIds();
    sort(actual_user_ids.begin(), actual_user_ids.end());
    // Extract movie IDs
    std::vector<int> actual_movie_ids = data_manager.getMovieIds();
    sort(actual_movie_ids.begin(), actual_movie_ids.end());

    // Compare the vectors
    EXPECT_EQ(expected_users, actual_user_ids);
    EXPECT_EQ(expected_movies, actual_movie_ids);
    std::vector<int> user1_movies = data_manager.getMoviesWatchedByUser(10);
    sort(user1_movies.begin(), user1_movies.end());
    std::vector<int> expected_watched_movies = {100, 200};
    EXPECT_EQ(user1_movies, expected_watched_movies);
    data_manager.reset();
    delete persistence;
}

// Test save and load method
TEST(Persistence, SaveLoad) {
    std::string save_dir = BASE_DIR / "save";
    cleanDirectory(save_dir);
    std::string data_dir = BASE_DIR / "load";
    DataManager& data_manager = DataManager::getInstance();
    // load users and movies
    IPersistence* persistence = new FilePersistence(data_dir);
    data_manager.reset();
    data_manager.setPersistenceStrategy(persistence);
    data_manager.load();
    std::vector<int> users_from_original_save = data_manager.getUserIds();
    std::vector<int> movies_from_original_save = data_manager.getMovieIds();
    IPersistence* persistence2 = new FilePersistence(save_dir);
    data_manager.setPersistenceStrategy(persistence2);
    delete persistence;
    // save the loaded movies and users
    data_manager.save();
    // load the new save
    data_manager.reset();
    data_manager.setPersistenceStrategy(persistence2);
    data_manager.load();
    std::vector<int> users_from_generated_save = data_manager.getUserIds();
    std::vector<int> movies_from_generated_save = data_manager.getMovieIds();
    // insert user ids and movies ids to the vectors

    // Sort the ID vectors
    std::sort(users_from_original_save.begin(), users_from_original_save.end());
    std::sort(movies_from_original_save.begin(),movies_from_original_save.end());
    std::sort(users_from_generated_save.begin(), users_from_generated_save.end());
    std::sort(movies_from_generated_save.begin(), movies_from_generated_save.end());
    // Compare the vectors
    EXPECT_EQ(users_from_original_save, users_from_generated_save);
    EXPECT_EQ(movies_from_original_save, movies_from_generated_save);
    data_manager.reset();
    delete persistence2;
}
