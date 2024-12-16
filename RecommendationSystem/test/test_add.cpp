#include "gtest/gtest.h"
#include "objects/User.h"
#include "Commands/add.h"
#include "DataManage/FilePersistence.h"
#include "DataManage/DataManager.h"
#include <algorithm>  // For std::sort
#include <filesystem>


namespace fs = std::filesystem;
const fs::path BASE_DIR = fs::path("test") / "test_data";

TEST(Command, add) {
    DataManager& dataManager = DataManager::getInstance();
    IPersistence* persistence = new FilePersistence(BASE_DIR / "save");
    // Reset DataManager state before running tests
    dataManager.reset();
    dataManager.setPersistenceStrategy(persistence);
    fs::path data_dir = BASE_DIR / "save";

    // Add initial users and movies
    dataManager.addUser(User(10));
    dataManager.addUser(User(20));
    dataManager.addUser(User(30));
    dataManager.addUser(User(40));

    dataManager.addMovie(Movie(100));
    dataManager.addMovie(Movie(200));
    dataManager.addMovie(Movie(300));
    dataManager.addMovie(Movie(400));

    // Create the 'add' command instance
    add addCommand;

    // Case 1: Add movies to an existing user (User ID 10)
    addCommand.execute("10 100 200");
    std::vector<int> userMovies = dataManager.getMoviesWatchedByUser(10);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({100, 200})) << "User ID 10's movie list does not match the expected list";

    // Case 2: Add a movie to an existing user (User ID 20)
    addCommand.execute("20 300");
    userMovies = dataManager.getMoviesWatchedByUser(20);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({300})) << "User ID 20's movie list does not match the expected list";

    // Case 3: Create a new user (User ID 50) and add movies
    addCommand.execute("50 400");
    userMovies = dataManager.getMoviesWatchedByUser(50);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({400})) << "User ID 50's movie list does not match the expected list";

    // Case 4: Add duplicate movie IDs to an existing user
    addCommand.execute("10 100 100");
    userMovies = dataManager.getMoviesWatchedByUser(10);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({100, 200})) << "User ID 10's movie list should still match the expected list despite duplicates";

    // Case 5: Add movies to a user with an empty movie list (User ID 30)
    addCommand.execute("30 300 400");
    userMovies = dataManager.getMoviesWatchedByUser(30);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({300, 400})) << "User ID 30's movie list does not match the expected list";

    // Case 6: Command with no movie IDs
    addCommand.execute("40");
    userMovies = dataManager.getMoviesWatchedByUser(40);
    EXPECT_TRUE(userMovies.empty()) << "User ID 40's movie list should be empty when no movie IDs are provided";

    // Case 7: Add a movie ID that doesn't exist in the movie list
    addCommand.execute("10 999");
    userMovies = dataManager.getMoviesWatchedByUser(10);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({100, 200, 999})) << "User ID 10's movie list should include the non-existent movie ID 999";
    delete persistence;
}