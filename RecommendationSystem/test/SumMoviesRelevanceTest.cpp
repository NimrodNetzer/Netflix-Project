#include "gtest/gtest.h"
#include "../src/movie.h"
#include "../src/user.h"
#include "../src/recommendAlgo.h"

TEST(SumMoviesRelevanceTest, CalculatesCorrectRelevance) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102
    Movie movie3(103);  // Movie ID 103
    Movie movie4(104);  // Movie ID 104

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2
    User user3(3);  // User ID 3

    // Step 3: Assign watched movies to users
    user1.addMovieWatched(movie1);  // User 1 watches movie 101
    user1.addMovieWatched(movie2);  // User 1 also watches movie 102
    user2.addMovieWatched(movie2);  // User 2 watches movie 102
    user2.addMovieWatched(movie3);  // User 2 also watches movie 103
    user3.addMovieWatched(movie1);
    user3.addMovieWatched(movie2);
    user3.addMovieWatched(movie4);  // User 3 watches movie 104

    // Step 4: Create the list of all users
    std::vector<User> allUsers = {user1, user2, user3};

    // Step 5: Create the commonMoviesCount map (users who watched a common movie)
    std::unordered_map<int, int> commonMoviesCount = {
            {2, 1},  // User 1 has 2 common movies with others
            {3, 2},  // User 2 has 1 common movie with others
    };

    // Step 6: Call the function to sum relevance of movies
    std::unordered_map<int, int> result = sumMoviesRelevance(commonMoviesCount, allUsers, user1);

    // Step 7: Perform assertions
    ASSERT_EQ(result.size(), 3);  // There should be 3 movies with relevance scores

    // Check relevance of each movie
    ASSERT_EQ(result[101], 1);  // Movie 101 relevance should be 1 (only user 1 watched it)
    ASSERT_EQ(result[102], 2);  // Movie 102 relevance should be 2 (user 1 and user 2 watched it)
    ASSERT_EQ(result[103], 1);  // Movie 103 relevance should be 1 (only user 2 watched it)
    ASSERT_TRUE(result.find(104) == result.end());  // Movie 104 should not appear (only user 3 watched it)
}

TEST(SumMoviesRelevanceTest, HandlesEmptyInputs) {
    // Step 1: Empty inputs
    std::unordered_map<int, int> commonMoviesCount;  // No common movies
    std::vector<User> allUsers;  // No users

    // Step 2: Call the function
    std::unordered_map<int, int> result = sumMoviesRelevance(commonMoviesCount, allUsers, User(0));

    // Step 3: Perform assertions
    ASSERT_TRUE(result.empty());  // The result should be empty
}

TEST(SumMoviesRelevanceTest, HandlesNoCommonMovies) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2

    // Step 3: Assign watched movies to users
    user1.addMovieWatched(movie1);  // User 1 watches movie 101
    user2.addMovieWatched(movie2);  // User 2 watches movie 102

    // Step 4: Create the list of all users
    std::vector<User> allUsers = {user1, user2};

    // Step 5: Create the commonMoviesCount map with no matching users
    std::unordered_map<int, int> commonMoviesCount = {
            {3, 1},  // User ID 3 does not exist in allUsers
    };

    // Step 6: Call the function
    std::unordered_map<int, int> result = sumMoviesRelevance(commonMoviesCount, allUsers, user1);

    // Step 7: Perform assertions
    ASSERT_TRUE(result.empty());  // The result should be empty since no movies are shared
}

TEST(SumMoviesRelevanceTest, HandlesDuplicateMoviesInUsers) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2

    // Step 3: Assign duplicate watched movies to users
    user1.addMovieWatched(movie1);  // User 1 watches movie 101
    user1.addMovieWatched(movie1);  // Duplicate movie (should not inflate relevance)
    user2.addMovieWatched(movie2);  // User 2 watches movie 102

    // Step 4: Create the list of all users
    std::vector<User> allUsers = {user1, user2};

    // Step 5: Create the commonMoviesCount map
    std::unordered_map<int, int> commonMoviesCount = {
            {1, 1},  // User 1 has 1 common movie with user 2 (movie 1)
    };

    // Step 6: Call the function
    std::unordered_map<int, int> result = sumMoviesRelevance(commonMoviesCount, allUsers, user1);

    // Step 7: Perform assertions
    ASSERT_EQ(result.size(), 1);  // Only one unique movie (movie1)
    ASSERT_EQ(result[101], 1);    // Movie 101 relevance should be 1 (not inflated by duplicates)
}
