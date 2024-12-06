#include "gtest/gtest.h"
#include "../src/User.h"
#include "../src/add.h"
#include "../src/FilePersistence.h"
#include <algorithm>  // For std::find_if

TEST(Command, add) {
    // Create some sample movies and users
    std::vector<Movie> movies = {Movie(100), Movie(200), Movie(300), Movie(400)};
    std::vector<User> users = { User(10), User(20), User(30), User(40) };
    IPersistence* persistence = new FilePersistence("data");
    // Create the 'add' command instance
    add addCommand(movies, users, persistence);

    // Case 1: Add movies to an existing user (User ID 10)
    addCommand.execute("10 100 200");
    auto it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 10;
    });
    EXPECT_NE(it, users.end()) << "User with ID 10 not found in the list";

    std::vector<int> userMovies;
    for (const auto& movie : it->getMoviesWatched()) {
        userMovies.push_back(movie.getMovieID());
    }
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({100, 200})) << "User ID 10's movie list does not match the expected list";

    // Case 2: Add a movie to an existing user (User ID 20)
    addCommand.execute("20 300");
    it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 20;
    });
    EXPECT_NE(it, users.end()) << "User with ID 20 not found in the list";
    userMovies.clear();
    for (const auto& movie : it->getMoviesWatched()) {
        userMovies.push_back(movie.getMovieID());
    }
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({300})) << "User ID 20's movie list does not match the expected list";

    // Case 3: Create a new user (User ID 50) and add movies
    addCommand.execute("50 400");
    it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 50;
    });
    EXPECT_NE(it, users.end()) << "User with ID 50 was not created";
    userMovies.clear();
    for (const auto& movie : it->getMoviesWatched()) {
        userMovies.push_back(movie.getMovieID());
    }
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({400})) << "User ID 50's movie list does not match the expected list";

    // Case 4: Add duplicate movie IDs to an existing user
    addCommand.execute("10 100 100");
    it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 10;
    });
    EXPECT_NE(it, users.end()) << "User with ID 10 not found in the list";
    userMovies.clear();
    for (const auto& movie : it->getMoviesWatched()) {
        userMovies.push_back(movie.getMovieID());
    }
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({100, 200})) << "User ID 10's movie list should still match the expected list despite duplicates";

    // Case 5: Add movies to a user with an empty movie list (User ID 30)
    addCommand.execute("30 300 400");
    it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 30;
    });
    EXPECT_NE(it, users.end()) << "User with ID 30 not found in the list";
    userMovies.clear();
    for (const auto& movie : it->getMoviesWatched()) {
        userMovies.push_back(movie.getMovieID());
    }
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({300, 400})) << "User ID 30's movie list does not match the expected list";

    // Case 6: Command with no movie IDs
    addCommand.execute("40");
    it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 40;
    });
    EXPECT_NE(it, users.end()) << "User with ID 40 not found in the list";
    EXPECT_TRUE(it->getMoviesWatched().empty()) << "User ID 40's movie list should be empty when no movie IDs are provided";

    // Case 7: Add a movie ID that doesn't exist in the movie list
    addCommand.execute("10 999");
    it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 10;
    });
    EXPECT_NE(it, users.end()) << "User with ID 10 not found in the list";
    userMovies.clear();
    for (const auto& movie : it->getMoviesWatched()) {
        userMovies.push_back(movie.getMovieID());
    }
    std::sort(userMovies.begin(), userMovies.end());
    EXPECT_EQ(userMovies, std::vector<int>({100, 200, 999})) << "User ID 10's movie list should not have changed with an invalid movie ID";
}
