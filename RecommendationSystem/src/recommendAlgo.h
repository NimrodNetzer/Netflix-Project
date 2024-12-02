//
// Created by nimro on 01/12/2024.
//

#ifndef RECOMMENDATIONSYSTEM_RECOMMENDALGO_H
#define RECOMMENDATIONSYSTEM_RECOMMENDALGO_H

#include <unordered_map>
#include <vector>
#include "user.h"
#include "movie.h"

// Function declarations
std::vector<User> watchedDesiredMovie(
        const std::vector<User> &allUsers,
        const Movie &givenMovie);

std::unordered_map<int, int> countCommonMoviesWithGivenUser(
        const std::vector<User> &usersWatchedTargetMovieList,
        const User &givenUser);


std::unordered_map<int, int>
sumMoviesRelevance(const std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList,
                   const std::vector<User> &allUsers, const User &givenUser);

std::map<int, int> combineAndCalculateMoviesRelevance(
        const std::vector<User> &allUsers, const std::vector<Movie> &allMovies,
        const User &givenUser, const Movie &givenMovie);

#endif // RECOMMENDATIONSYSTEM_RECOMMENDALGO_H