#include "test_user.h"
#include <gtest/gtest.h>
#include "../src/User.h"
TEST(User, Contructor) {
    User user(50);
    EXPECT_EQ(user.getUserID(), 50);
}

TEST(User, AddMovies) {
    User user(50);
    Movie movie(25);
    Movie movie2(30);

    user.addMovieWatched(movie);
    EXPECT_EQ(user.getMoviesWatched().size(), 1);
    EXPECT_EQ(user.getMoviesWatched()[0].getMovieID(), 25);
    user.addMovieWatched(movie2);
    EXPECT_EQ(user.getMoviesWatched().size(), 2);
    EXPECT_EQ(user.getMoviesWatched()[1].getMovieID(), 30);
}