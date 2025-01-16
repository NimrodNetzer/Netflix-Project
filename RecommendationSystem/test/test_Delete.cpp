#include "test_Delete.h"
#include <gtest/gtest.h>
#include "../src/Data/DataManager.h"
#include "../src/Commands/Delete.h"
#include "../src/objects/User.h"
#include "../src/objects/Movie.h"
#include "../src/Data/FilePersistence.h"
#include "../src/Interfaces/IPersistence.h"
#include <algorithm>
#include <filesystem>
#include "../src/Menus/ConsoleMenu.h"

namespace fs = std::filesystem;
const fs::path BASE_DIR = fs::path("test") / "test_data";

TEST(Command, Delete) {
    DataManager& dataManager = DataManager::getInstance();
    std::filesystem::path path = BASE_DIR / "save";
    IPersistence* persistence = new FilePersistence(path.string());

    // Reset DataManager state before running tests
    dataManager.reset();
    dataManager.setPersistenceStrategy(persistence);
    fs::path data_dir = BASE_DIR / "save";

    // Add initial users and movies
    dataManager.addUser(User(10));
    dataManager.addUser(User(20));
    dataManager.addUser(User(30));
    dataManager.addMovie(Movie(100));
    dataManager.addMovie(Movie(200));
    dataManager.addMovie(Movie(300));
    dataManager.addMovie(Movie(400));

    // Add movies to users (this is where the link between movies and users is made)
    dataManager.addUserWatchedMovie(10, 100);
    dataManager.addUserWatchedMovie(10, 200);
    dataManager.addUserWatchedMovie(20, 200);
    dataManager.addUserWatchedMovie(20, 300);
    dataManager.addUserWatchedMovie(30, 300);
    dataManager.addUserWatchedMovie(30, 400);

    // Create the 'Delete' command instance
    ConsoleMenu menu;
    Delete deleteCommand(menu);

    // Case 1: Delete movies from an existing user (User ID 10)
    deleteCommand.execute("10 100 200");
    std::vector<int> userMovies = dataManager.getMoviesWatchedByUser(10);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>()) << "User ID 10's movie list should be empty after deletion";

    // Case 2: Delete a movie from an existing user (User ID 20)
    deleteCommand.execute("20 200");
    userMovies = dataManager.getMoviesWatchedByUser(20);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({300})) << "User ID 20's movie list does not match after deleting movie 200";

    // Case 3: Delete a non-existing user
    deleteCommand.execute("50 100");
    bool userExists = dataManager.hasUser(50);
    EXPECT_TRUE(!userExists) << "User ID 50 should not exist and should have an empty movie list";

//    // Case 4: Try deleting a movie that is not in the user's movie list (User ID 30)
//    deleteCommand.execute("30 999");
//    userMovies = dataManager.getMoviesWatchedByUser(30);
//    EXPECT_TRUE(userMovies.empty()) << "User ID 30's movie list should remain empty after trying to delete a non-existent movie";

    // Case 5: Delete multiple movies from a user (User ID 10)
    deleteCommand.execute("10 100 200 300");
    userMovies = dataManager.getMoviesWatchedByUser(10);
    EXPECT_TRUE(userMovies.empty()) << "User ID 10's movie list should be empty after deleting multiple movies";

    // Case 6: Delete movies without any movie IDs (Just user ID)
    deleteCommand.execute("20");
    userMovies = dataManager.getMoviesWatchedByUser(20);
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({300})) << "User ID 20's movie list should be empty after deletion of movies";



    delete persistence;
}
