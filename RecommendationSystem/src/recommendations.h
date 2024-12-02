#ifndef NETFLIX_BIU_RECOMMENDATIONS_H
#define NETFLIX_BIU_RECOMMENDATIONS_H

#include <unordered_map>
#include <vector>
#include "user.h"
#include "movie.h"

// Function declarations
std::unordered_map<int, int> countCommonMovies(const User &user, const std::vector<User> &users);

std::unordered_map<int, int> sumMoviesRelevance(
        const std::unordered_map<int, int> &commonMoviesCount,
        const std::vector<User> &allUsers);

// Declare the watchedDesiredMovie function
std::unordered_map<int, int> watchedDesiredMovie(
        const std::unordered_map<int, int> &commonMoviesCount,
        const std::vector<User> &allUsers,
        const Movie &movie);

// Declare the getAndPrintMoviesByRelevance function
void getAndPrintMoviesByRelevance(User &user, const std::vector<User> &users, Movie &movie);

#endif // NETFLIX_BIU_RECOMMENDATIONS_H
