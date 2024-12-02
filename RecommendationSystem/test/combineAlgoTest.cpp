#include "gtest/gtest.h"
#include "../src/user.h"
#include "../src/recommendAlgo.h"

TEST(CombineAndCalculateMoviesRelevanceTest, CalculatesCorrectRelevance) {
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
    user1.addMovieWatched(movie1);
    user1.addMovieWatched(movie2);
    user2.addMovieWatched(movie2);
    user2.addMovieWatched(movie3);
    user3.addMovieWatched(movie4);

    // Step 4: Create the list of all users and all movies
    std::vector<User> allUsers = {user1, user2, user3};
    std::vector<Movie> allMovies = {movie1, movie2, movie3, movie4};

    // Step 5: Create the given user and given movie for relevance calculation
    User givenUser(1);  // User ID 1
    Movie givenMovie(102);  // Movie ID 102

    // Step 6: Call the function
    std::map<int, int> result = combineAndCalculateMoviesRelevance(allUsers, allMovies, givenUser, givenMovie);

    // Step 7: Perform assertions
    ASSERT_EQ(result.size(), 2);  // Expect 2 movies to be returned

    // Check if the movies are sorted by relevance (descending)
    ASSERT_EQ(result.begin()->first, 102);  // Movie 102 should be first
    ASSERT_EQ(std::next(result.begin())->first, 101);  // Movie 101 should be second
}

TEST(CombineAndCalculateMoviesRelevanceTest, HandlesEmptyInputs) {
    // Step 1: Empty inputs
    std::vector<User> allUsers;  // No users
    std::vector<Movie> allMovies;  // No movies
    User givenUser(1);  // User ID 1
    Movie givenMovie(102);  // Movie ID 102

    // Step 2: Call the function
    std::map<int, int> result = combineAndCalculateMoviesRelevance(allUsers, allMovies, givenUser, givenMovie);

    // Step 3: Perform assertions
    ASSERT_TRUE(result.empty());  // The result should be empty since no users or movies exist
}

TEST(CombineAndCalculateMoviesRelevanceTest, HandlesNoCommonMovies) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2

    // Step 3: Assign watched movies to users
    user1.addMovieWatched(movie1);
    user2.addMovieWatched(movie2);

    // Step 4: Create the list of all users and all movies
    std::vector<User> allUsers = {user1, user2};
    std::vector<Movie> allMovies = {movie1, movie2};

    // Step 5: Create the given user and given movie for relevance calculation
    User givenUser(1);  // User ID 1
    Movie givenMovie(102);  // Movie ID 102

    // Step 6: Call the function
    std::map<int, int> result = combineAndCalculateMoviesRelevance(allUsers, allMovies, givenUser, givenMovie);

    // Step 7: Perform assertions
    ASSERT_TRUE(result.empty());  // No common movies to calculate relevance for
}

TEST(CombineAndCalculateMoviesRelevanceTest, HandlesDuplicateMoviesInUsers) {
    // Step 1: Create movies
    Movie movie1(101);  // Movie ID 101
    Movie movie2(102);  // Movie ID 102

    // Step 2: Create users
    User user1(1);  // User ID 1
    User user2(2);  // User ID 2

    // Step 3: Assign duplicate watched movies to users
    user1.addMovieWatched(movie1);
    user1.addMovieWatched(movie1);  // Duplicate movie
    user2.addMovieWatched(movie2);

    // Step 4: Create the list of all users and all movies
    std::vector<User> allUsers = {user1, user2};
    std::vector<Movie> allMovies = {movie1, movie2};

    // Step 5: Create the given user and given movie for relevance calculation
    User givenUser(1);  // User ID 1
    Movie givenMovie(102);  // Movie ID 102

    // Step 6: Call the function
    std::map<int, int> result = combineAndCalculateMoviesRelevance(allUsers, allMovies, givenUser, givenMovie);

    // Step 7: Perform assertions
    ASSERT_EQ(result.size(), 1);  // Only one movie should be returned
    ASSERT_EQ(result.begin()->first, 101);  // Movie 101 should be returned
}
