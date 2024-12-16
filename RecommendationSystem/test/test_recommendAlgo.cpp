#include "gtest/gtest.h"
#include "DataManage/DataManager.h"
#include "objects/User.h"
#include "objects/Movie.h"
#include "Commands/recommendAlgo.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

class RecommendationAlgoTest : public ::testing::Test {
protected:
    void SetUp() override {
        DataManager &dataManager = DataManager::getInstance();
        dataManager.reset();
        // Add users
        dataManager.addUser(User(1));  // user1
        dataManager.addUser(User(2));  // user2
        dataManager.addUser(User(3));  // user3
        dataManager.addUser(User(4));  // user4

        // Add movies
        dataManager.addMovie(Movie(0)); // movie0
        dataManager.addMovie(Movie(1)); // movie1
        dataManager.addMovie(Movie(2)); // movie2
        dataManager.addMovie(Movie(3)); // movie3

        // Assign watched movies to users
        dataManager.addUserWatchedMovie(1, 0); // user1 watches movie0
        dataManager.addUserWatchedMovie(1, 1); // user1 watches movie1
        dataManager.addUserWatchedMovie(2, 1); // user2 watches movie1
        dataManager.addUserWatchedMovie(2, 3); // user2 watches movie3
        dataManager.addUserWatchedMovie(3, 2); // user3 watches movie2
        dataManager.addUserWatchedMovie(4, 0); // user4 watches movie0
        dataManager.addUserWatchedMovie(4, 3); // user4 watches movie3
    }
};

// Test for countCommonMoviesWithGivenUser
TEST_F(RecommendationAlgoTest, TestCountCommonMoviesWithGivenUser) {
    DataManager &dataManager = DataManager::getInstance();
    Movie targetMovie = dataManager.getMovie(1); // movie1
    User targetUser = dataManager.getUser(1);    // user1

    std::unordered_map<int, int> result = countCommonMoviesWithGivenUser(targetMovie, targetUser);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[2], 1); // user2 shares movie1 with user1
}

// Test for sumMoviesRelevance
TEST_F(RecommendationAlgoTest, TestSumMoviesRelevance) {
    DataManager &dataManager = DataManager::getInstance();
    Movie targetMovie = dataManager.getMovie(1); // movie1
    User targetUser = dataManager.getUser(1);    // user1

    std::unordered_map<int, int> commonMoviesCount = countCommonMoviesWithGivenUser(targetMovie, targetUser);

    std::unordered_map<int, int> result = sumMoviesRelevance(commonMoviesCount, targetUser);

    ASSERT_EQ(result.size(), 2); // Two movies are relevant: movie2, movie3
    EXPECT_EQ(result[2], 0);     // movie2 is not watched by user1, no relevance from common users
    EXPECT_EQ(result[3], 1);     // movie3 has relevance score of 1 from user2
}


// Test for combineAndCalculateMoviesRelevance
TEST_F(RecommendationAlgoTest, TestCombineAndCalculateMoviesRelevance) {
    DataManager &dataManager = DataManager::getInstance();
    Movie targetMovie = dataManager.getMovie(0); // movie0
    User targetUser = dataManager.getUser(1);    // user1

    std::vector<int> recommendations = combineAndCalculateMoviesRelevance(targetUser, targetMovie);

    ASSERT_EQ(recommendations.size(), 2); // Two recommendations: movie2, movie3
    EXPECT_EQ(recommendations[0], 3);    // movie3 should be the top recommendation
    EXPECT_EQ(recommendations[1], 2);    // movie2 should follow
}
