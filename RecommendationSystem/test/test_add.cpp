#include "gtest/gtest.h"
#include "../src/user.h"
#include "test_add.h"
#include "../src/add.h"
#include <algorithm>  // For std::find_if

TEST(Command, add) {
    // Create some sample movies and users
    std::vector<Movie> movies = {};
    std::vector<User> users = {User{10}, User{20}, User{30}, User{40}};  // Example users

    // Create the 'add' command instance
    add addCommand(movies, users);
    addCommand.execute("10 100 200");

    // Find user with the value 10 in the users list
    auto it = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.getUserID() == 10;  // Assuming User class has a getUserID() method
    });

    // Ensure the user was found
    EXPECT_NE(it, users.end()) << "User with value 10 not found in the list";

    // Extract the found user
    User foundUser = *it;

    // Retrieve the movies watched by the user
    std::vector<int> user1Movies;
    foundUser.getMoviesWatched();  // Assuming this method returns a vector of movies

    for (auto movie : it->getMoviesWatched()) {
        user1Movies.push_back(movie.getMovieID());  // Assuming getMovieID() exists
    }

    // Sort the movie IDs
    std::sort(user1Movies.begin(), user1Movies.end());

    // Define the expected movie IDs
    std::vector<int> expectedMovies = {100, 200};

    // Compare the user's movie list with the expected list
    EXPECT_EQ(user1Movies, expectedMovies);
}
