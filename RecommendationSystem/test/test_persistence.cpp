//#include "test_persistence.h"
//
//#include <algorithm>
//#include <iostream>
//#include <filesystem>
//#include <fstream>
//
//#include <gtest/gtest.h>
//#include "../src/IPersistence.h"
//#include "../src/FilePersistence.h"
//namespace fs = std::filesystem;
//const fs::path BASE_DIR = fs::path("test") / "test_data";
//
//// Delete all files and directories withing a directory
//void cleanDirectory(const fs::path& dir_path) {
//    try {
//        if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
//            for (const auto& entry : fs::directory_iterator(dir_path)) {
//                const auto& path = entry.path();
//                if (fs::is_directory(path)) {
//                    cleanDirectory(path);
//                    fs::remove_all(path);
//                } else {
//                    fs::remove(path);
//                }
//            }
//            std::cout << "Directory cleaned: " << dir_path << std::endl;
//        } else {
//            std::cout << "The provided path is not a valid directory." << std::endl;
//        }
//    } catch (const std::exception& e) {
//        std::cout << "Error: " << e.what() << std::endl;
//    }
//}
//
//// Test the save method
//TEST(Persistence, Save) {
//    fs::path data_dir = BASE_DIR / "save";
//    fs::path movies_dir = data_dir / "movies";
//    fs::path users_dir = data_dir / "users";
//
//    // Generate test case
//    cleanDirectory(data_dir); // clean the test folder
//    IPersistence* persistence = new FilePersistence(data_dir);
//    std::vector<Movie> movies = { Movie(100), Movie(200), Movie(300) };
//    std::vector<User> users = { User(10), User(20), User(30) };
//
//    users[0].addMovieWatched(movies[0]);
//    users[0].addMovieWatched(movies[1]);
//    users[1].addMovieWatched(movies[2]);
//    users[2].addMovieWatched(movies[2]);
//    users[2].addMovieWatched(movies[1]);
//    persistence->Save(movies, users);
//
//    // Assertions for existence of directories
//    ASSERT_TRUE(fs::exists(movies_dir));
//    ASSERT_TRUE(fs::exists(users_dir));
//
//    // Check saved movies
//    std::vector<int> saved_movies;
//    for (auto const& dir_entry : fs::directory_iterator(movies_dir)) {
//        saved_movies.push_back(atoi(dir_entry.path().filename().c_str()));
//    }
//    std::sort(saved_movies.begin(), saved_movies.end());
//    std::vector<int> expected_movies = {100, 200, 300};
//    EXPECT_EQ(saved_movies, expected_movies);
//
//    // Check saved users
//    std::vector<int> saved_users;
//    for (auto const& dir_entry : fs::directory_iterator(users_dir)) {
//        saved_users.push_back(atoi(dir_entry.path().filename().c_str()));
//    }
//    std::vector<int> expected_users = {10, 20, 30};
//    std::sort(saved_users.begin(), saved_users.end());
//    EXPECT_EQ(saved_users, expected_users);
//
//    // Check contents of user 30's file
//    fs::path user_file_30 = users_dir / "30";
//    std::ifstream file(user_file_30);
//    std::string line;
//    std::getline(file, line);
//    EXPECT_EQ(line, "300 200");
//    file.close();
//
//    // Check contents of user 20's file
//    fs::path user_file_20 = users_dir / "20";
//    std::ifstream file1(user_file_20);
//    std::getline(file1, line);
//    EXPECT_EQ(line, "300");
//    file1.close();
//    delete persistence;
//}
//
//// Test the load method
//TEST(Persistence, Load) {
//    std::string data_dir = BASE_DIR / "load";
//    IPersistence* persistence = new FilePersistence(data_dir);
//    std::vector<Movie> movies;
//    std::vector<User> users;
//    // load movies and users from the file
//    persistence->Load(movies, users);
//    std::vector<int> expected_users = {10, 20, 30};
//    std::vector<int> expected_movies = {100, 200, 300};
//    // check if data was loaded
//    ASSERT_FALSE(users.empty());
//    ASSERT_FALSE(movies.empty());
//    // Extract user IDs
//    std::vector<int> actual_user_ids;
//    std::transform(users.begin(), users.end(), std::back_inserter(actual_user_ids),
//                   [](const User& user) { return user.getUserID(); });
//    sort(actual_user_ids.begin(), actual_user_ids.end());
//    // Extract movie IDs
//    std::vector<int> actual_movie_ids;
//    std::transform(movies.begin(), movies.end(), std::back_inserter(actual_movie_ids),
//                   [](const Movie& movie) { return movie.getMovieID(); });
//    sort(actual_movie_ids.begin(), actual_movie_ids.end());
//
//    // Compare the vectors
//    EXPECT_EQ(expected_users, actual_user_ids);
//    EXPECT_EQ(expected_movies, actual_movie_ids);
//    std::vector<int> user1_movies;
//    auto userIt = std::find_if(users.begin(), users.end(), [](const User& user) {
//    return user.getUserID() == 10;
//    });
//    for (auto const& movie : userIt->getMoviesWatched()) {
//        user1_movies.push_back(movie.getMovieID());
//    }
//    sort(user1_movies.begin(), user1_movies.end());
//    std::vector<int> expected_watched_movies = {100, 200};
//    EXPECT_EQ(user1_movies, expected_watched_movies);
//    delete persistence;
//}
//
//// Test save and load method
//TEST(Persistence, SaveLoad) {
//    std::string save_dir = BASE_DIR / "save";
//    cleanDirectory(save_dir);
//    std::string data_dir = BASE_DIR / "load";
//    // load users and movies
//    IPersistence* persistence = new FilePersistence(data_dir);
//    std::vector<Movie> movies_from_original_save;
//    std::vector<User> users_from_original_save;
//    persistence->Load(movies_from_original_save, users_from_original_save);
//    delete persistence;
//    // save the loaded movies and users
//    IPersistence* persistence2 = new FilePersistence(save_dir);
//    persistence2->Save(movies_from_original_save, users_from_original_save);
//    std::vector<Movie> movies_from_generated_save;
//    std::vector<User> users_from_generated_save;
//    // load the new save
//    persistence2->Load(movies_from_generated_save, users_from_generated_save);
//    delete persistence2;
//    std::vector<int> movie_ids1, movie_ids2, user_ids1, user_ids2;
//    // insert user ids and movies ids to the vectors
//    for (const auto& movie : movies_from_original_save) {
//        movie_ids1.push_back(movie.getMovieID());
//    }
//    for (const auto& movie : movies_from_generated_save) {
//        movie_ids2.push_back(movie.getMovieID());
//    }
//
//    for (const auto& user : users_from_original_save) {
//        user_ids1.push_back(user.getUserID());
//    }
//    for (const auto& user : users_from_generated_save) {
//        user_ids2.push_back(user.getUserID());
//    }
//
//    // Sort the ID vectors
//    std::sort(movie_ids1.begin(), movie_ids1.end());
//    std::sort(movie_ids2.begin(), movie_ids2.end());
//    std::sort(user_ids1.begin(), user_ids1.end());
//    std::sort(user_ids2.begin(), user_ids2.end());
//    // Compare the vectors
//    EXPECT_EQ(user_ids1, user_ids2);
//    EXPECT_EQ(movie_ids1, movie_ids2);
//
//}
