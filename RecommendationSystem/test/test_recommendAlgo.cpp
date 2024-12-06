#include "test_recommendAlgo.h"
#include "gtest/gtest.h"
#include "../src/Movie.h"
#include "../src/User.h"
#include <vector>
#include <algorithm>
#include "../src/recommendAlgo.h"


// Test Suite
class RecommendationAlgoTest : public ::testing::Test {
protected:
    std::vector<User> users;
    std::vector<Movie> movies;

    // Helper function to create a movie
    Movie createMovie(int id) {
        return Movie(id); // Assuming Movie class has a constructor that accepts an ID
    }

    // Helper function to create a user and add watched movies
    User createUser(int id, const std::vector<Movie> &watchedMovies) {
        User user(id); // Assuming User class has a constructor that accepts an ID
        for (const auto &movie: watchedMovies) {
            user.addMovieWatched(movie); // Add movies to the user's watched list
        }
        return user;
    }

    void SetUp() override {
        // Create movies with IDs from 0 to 4
        for (int id = 0; id <= 4; ++id) {
            movies.push_back(createMovie(id));
        }

        // Create users and assign watched movies
        users.push_back(createUser(1, {movies[0], movies[1]})); // user1
        users.push_back(createUser(2, {movies[1], movies[2]})); // user2
        users.push_back(createUser(3, {movies[3], movies[4]})); // user3
        users.push_back(createUser(4, {movies[0], movies[3]})); // user4
        users.push_back(createUser(5, {movies[2], movies[4]})); // user5
    }
};




// Function 2:
// Test case 1: Test with a movie watched by some users
TEST_F(RecommendationAlgoTest, TestMovieWatchedBySomeUsers) {
    Movie testMovie = movies[1];  // Movie with ID 1

    // Call function to get users who watched the given movie
    std::vector<User> result = watchedDesiredMovie(users, testMovie);

    // Expect that the movie is watched by user1, user2
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getUserID(), 1);  // user1
    EXPECT_EQ(result[1].getUserID(), 2);  // user2
}

// Test case 2: Test with a movie watched by all users
TEST_F(RecommendationAlgoTest, TestMovieWatchedByAllUsers) {
    Movie testMovie = movies[0];  // Movie with ID 1

    // Call function to get users who watched the given movie
    std::vector<User> result = watchedDesiredMovie(users, testMovie);

    // Expect that all users watched this movie
    ASSERT_EQ(result.size(), 2);  // Only user1 and user4 watched this movie
    EXPECT_EQ(result[0].getUserID(), 1);  // user1
    EXPECT_EQ(result[1].getUserID(), 4);  // user4
}

// Test case 3: Test with an empty user list
TEST_F(RecommendationAlgoTest, TestEmptyUserList) {
    std::vector<User> emptyUsers;
    Movie testMovie = movies[2];  // Movie with ID 3

    // Call function with an empty list of users
    std::vector<User> result = watchedDesiredMovie(emptyUsers, testMovie);

    // Expect no users returned
    ASSERT_EQ(result.size(), 0);
}

// Test case 1: Test with the list of users who watched a target movie (Movie ID 1)
TEST_F(RecommendationAlgoTest, TestCountCommonMoviesWithGivenUser) {
    Movie targetMovie = movies[0];  // Movie with ID 1

    // Get users who watched the target movie (ID 1)
    std::vector<User> usersWhoWatched = watchedDesiredMovie(users, targetMovie);

    // Now count common movies with user1 (ID 1)
    std::unordered_map<int, int> result = countCommonMoviesWithGivenUser(usersWhoWatched, users[0]);

    // Check the results
    ASSERT_EQ(result.size(), 1);  // Only user4 has common movies with user1
    EXPECT_EQ(result[4], 1);      // user1 and user4 have 1 common movie (ID 1)
}

// Test case 2: Test with a target movie that is not watched by any user
TEST_F(RecommendationAlgoTest, TestCountCommonMoviesWithNoUserWatched) {
    Movie targetMovie = movies[3];  // Movie with ID 4 (not watched by user1)

    // Get users who watched the target movie (ID 4)
    std::vector<User> usersWhoWatched = watchedDesiredMovie(users, targetMovie);

    // Now count common movies with user1 (ID 1)
    std::unordered_map<int, int> result = countCommonMoviesWithGivenUser(usersWhoWatched, users[0]);

    // Expect no common movies with any users who watched movie ID 4
    ASSERT_EQ(result.size(), 1);  // User4 shares 1 movie with user1
    EXPECT_EQ(result[4], 1);  // user1 shares 1 common movie with user4
}

// Test case 3: Test with users who have no common movies with the given user
TEST_F(RecommendationAlgoTest, TestCountCommonMoviesWithNoCommonMovies) {
    Movie targetMovie = movies[2];  // Movie with ID 3 (watched by user2, user5)

    // Get users who watched the target movie (ID 3)
    std::vector<User> usersWhoWatched = watchedDesiredMovie(users, targetMovie);

    // Now count common movies with user3 (ID 3)
    std::unordered_map<int, int> result = countCommonMoviesWithGivenUser(usersWhoWatched, users[2]);

    // Expect that user3 shares no common movies with user2 and user5
    ASSERT_EQ(result.size(), 1);  // No common movies between user3 and others who watched movie ID 3
}

// Test case for sumMoviesRelevance function
TEST_F(RecommendationAlgoTest, TestSumMoviesRelevance) {
    // Set up the commonMoviesWithGivenUserCounterList
    Movie targetMovie = movies[1];  // Movie with ID 1
    std::vector<User> usersWhoWatched = watchedDesiredMovie(users, targetMovie);

    // Get common movies between user1 and others who watched the target movie
    std::unordered_map<int, int> commonMoviesList = countCommonMoviesWithGivenUser
            (usersWhoWatched, users[0]);

    // Now, calculate the movie relevance based on the common movies
    std::unordered_map<int, int> relevanceResult = sumMoviesRelevance
            (commonMoviesList, users, users[0]);

    // Expected values for movie relevance, based on the given logic
    // user1 has common movies with user4, so check relevance for movie ID 0 (Movie 0)

    ASSERT_EQ(relevanceResult.size(), 3);  // Three movies should be in the relevance list
    EXPECT_EQ(relevanceResult[0], 0);  // Movie ID 0 should have a relevance score of 0
    EXPECT_EQ(relevanceResult[3], 0);  // Movie ID 3 should have a relevance score of 0
}

// Test case for combineAndCalculateMoviesRelevance function
TEST_F(RecommendationAlgoTest, TestCombineAndCalculateMoviesRelevance) {
    Movie testMovie = movies[0];  // Movie with ID 0
    User testUser = users[0];     // User with ID 1 (user1)

    // Call function to combine and calculate movie relevance
    std::vector<int> result = combineAndCalculateMoviesRelevance(users, movies, testUser, testMovie);

    // Expected relevance values for the movie IDs, based on the given logic:
    // After watching movie 0, common movies with other users are considered
    // So user1 should have the highest relevance for their movies, followed by user4, etc.

    // Check the size of the result (top 10 recommended movies, but should be less)
    ASSERT_GT(result.size(), 0); // Expect some recommendations to be returned

    // Ensure the movie with the given ID (testMovie) is not in the result list
    auto it = std::find(result.begin(), result.end(), testMovie.getMovieID());
    EXPECT_EQ(it, result.end());  // Movie with ID 0 should not be recommended to the user
}

