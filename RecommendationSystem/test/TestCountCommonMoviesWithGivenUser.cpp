#include "gtest/gtest.h"
#include "../src/movie.h"
#include "../src/user.h"
#include "../src/recommendAlgo.h"  // Assuming the function is in this header file

// Test the countCommonMoviesWithGivenUser function
TEST(CountCommonMoviesWithGivenUserTest, IdentifiesCommonMoviesCorrectly) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102
    Movie movie3(103);  // Movie ID 103
    Movie movie4(104);  // Movie ID 104

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2
    User user3(3);  // User ID 3

    // Step 3: Add watched movies to each user
    user1.addMovieWatched(movie1);  // User 1 watches movie 101
    user1.addMovieWatched(movie2);  // User 1 also watches movie 102
    user2.addMovieWatched(movie2);  // User 2 watches movie 102
    user2.addMovieWatched(movie3);  // User 2 also watches movie 103
    user3.addMovieWatched(movie3);  // User 3 watches movie 103
    user3.addMovieWatched(movie4);  // User 3 also watches movie 104

    // Step 4: Create a list of users who have watched the given movie (movie 102)
    std::vector<User> usersWhoWatchedMovie = {user1, user2};  // Only user1 and user2 watched movie 102

    // Step 5: Call the function with user1 as the given user
    std::unordered_map<int, int> result = countCommonMoviesWithGivenUser(usersWhoWatchedMovie, user1);

    // Step 6: Perform assertions
    ASSERT_EQ(result.size(), 1);  // Only user2 should have common movies with user1
    ASSERT_TRUE(result.find(2) != result.end());  // User 2 should be in the result (common movie is 102)
    ASSERT_EQ(result[2], 1);  // User 2 and User 1 should have 1 common movie (movie 102)

    // Step 7: Test when user has no common movies with anyone
    result = countCommonMoviesWithGivenUser(usersWhoWatchedMovie, user3);
    ASSERT_EQ(result.size(), 1);  // User 3 has no common movies with user1 (doesn't have movie 102)

    // Step 8: Test when no users watched the given movie
    std::vector<User> emptyUsersList;
    result = countCommonMoviesWithGivenUser(emptyUsersList, user1);
    ASSERT_EQ(result.size(), 0);  // No users have watched the given movie, so the result should be empty
}
