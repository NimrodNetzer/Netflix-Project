#include "test_persistence.h"

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>
#include "../src/IPersistence.h"
#include "../src/FilePersistence.h"
namespace fs = std::filesystem;

void clean_directory(const fs::path& dir_path) {
    try {
        if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
            for (const auto& entry : fs::directory_iterator(dir_path)) {
                const auto& path = entry.path();
                if (fs::is_directory(path)) {
                    clean_directory(path);
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
TEST(Save, MoviesUsers) {
    fs::path data_dir = "test/test_data";
    fs::path movies_dir = data_dir / "movies";
    fs::path users_dir = data_dir / "users";

    clean_directory(data_dir);
    IPersistence* persistence = new FilePersistence(data_dir);
    std::vector<Movie> movies = { Movie(100), Movie(200), Movie(300) };
    std::vector<User> users = { User(10), User(20), User(30) };

    users[0].addMovieWatched(movies[0]);
    users[0].addMovieWatched(movies[1]);
    users[1].addMovieWatched(movies[2]);
    users[2].addMovieWatched(movies[2]);
    users[2].addMovieWatched(movies[1]);
    persistence->Save(movies, users);

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
    delete persistence;
}