#include "test_movie.h"
#include <gtest/gtest.h>
#include "../src/Movie.h"
TEST(Movie, Constructor) {
    Movie movie(100);
    EXPECT_EQ(movie.getMovieID(), 100);
    Movie movie2(50);
    EXPECT_EQ(movie2.getMovieID(), 50);
}