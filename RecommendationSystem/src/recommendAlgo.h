//
// Created by nimro on 01/12/2024.
//

#ifndef RECOMMENDATIONSYSTEM_RECOMMENDALGO_H
#define RECOMMENDATIONSYSTEM_RECOMMENDALGO_H

#include "map"
#include <unordered_map>
#include <vector>
#include "User.h"
#include "Movie.h"

// Function declarations
std::unordered_map<int, int> countCommonMoviesWithGivenUser(
        const Movie &givenMovie,  // List of users to compare against the given user
        const User &givenUser);

std::unordered_map<int, int>
sumMoviesRelevance(
        // Map of users and their common movie count with the given user
        std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList,
        const User &givenUser);

std::vector<int> sortKeysByValues(const std::unordered_map<int, int> &movieRelevance);


std::vector<int> combineAndCalculateMoviesRelevance(const User &givenUser, const Movie &givenMovie);


#endif // RECOMMENDATIONSYSTEM_RECOMMENDALGO_H