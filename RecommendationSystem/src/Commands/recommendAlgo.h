//
// Created by nimro on 01/12/2024.
//

#ifndef RECOMMENDATIONSYSTEM_RECOMMENDALGO_H
#define RECOMMENDATIONSYSTEM_RECOMMENDALGO_H

#include "map"
#include <unordered_map>
#include <vector>
#include "../objects/User.h"
#include "../objects/Movie.h"

// Function to count the common movies between a given user and a specific movie
// It compares the list of users who watched the given movie and counts common movies with the given user
std::unordered_map<int, int> countCommonMoviesWithGivenUser(
        const Movie &givenMovie,  // Movie to compare users against
        const User &givenUser);   // User to compare movie lists with

// Function to calculate the sum of movie relevance based on common movies
// It uses the common movie count for each user and sums the relevance of movies watched by them
std::unordered_map<int, int>
sumMoviesRelevance(
        std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList,  // Users and their common movie count
        const User &givenUser);  // The user whose movie relevance is being calculated

// Function to sort keys (user IDs) based on their associated values (relevance score)
// Returns the list of user IDs sorted by their movie relevance
std::vector<int> sortKeysByValues(const std::unordered_map<int, int> &movieRelevance);

// Function to combine the common movies and calculate movie relevance for a given user
// This function combines the logic of counting common movies and calculating relevance
std::vector<int> combineAndCalculateMoviesRelevance(const User &givenUser, const Movie &givenMovie);

#endif // RECOMMENDATIONSYSTEM_RECOMMENDALGO_H
