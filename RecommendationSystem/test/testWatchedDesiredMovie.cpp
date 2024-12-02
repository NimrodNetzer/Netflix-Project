#include "gtest/gtest.h"
#include "../src/movie.h"
#include "../src/user.h"
#include "../src/recommendAlgo.h"

// Test the watchedDesiredMovie function
TEST(WatchedDesiredMovieTest, IdentifiesUsersWhoWatchedGivenMovie) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102
    Movie movie3(103);  // Movie ID 103

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2
    User user3(3);  // User ID 3

    // Step 3: Add watched movies to each user
    user1.addMovieWatched(movie1);
    user1.addMovieWatched(movie2); // User 1 watches movie2
    user2.addMovieWatched(movie2); // User 2 watches movie2
    user3.addMovieWatched(movie3); // User 3 watches movie3

    // Step 4: Add all users to a vector
    std::vector<User> allUsers = {user1, user2, user3};

    // Step 5: Define the movie to search for
    Movie givenMovie(102);  // Target movie ID: 102

    // Step 6: Call the watchedDesiredMovie function to get users who watched the given movie
    std::vector<User> result = watchedDesiredMovie(allUsers, givenMovie);

    // Step 7: Perform assertions
    ASSERT_EQ(result.size(), 2);  // Two users should have watched movie 102
    ASSERT_EQ(result[0].getUserID(), 1);  // User 1 should be in the result
    ASSERT_EQ(result[1].getUserID(), 2);  // User 2 should be in the result
}
