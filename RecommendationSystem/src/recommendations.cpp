#include <iostream>
#include <unordered_map>
#include "unordered_set"
#include <vector>
#include <algorithm>
#include "user.h"
#include "movie.h"
#include "recommendations.h"

// Function to count how many users have common movies with the given user
std::unordered_map<int, int> countCommonMovies(const User &user, const std::vector<User> &users) {
    std::unordered_map<int, int> commonMoviesCount;

    std::unordered_set<int> userMoviesSet;
    for (const Movie &movie: user.getMoviesWatched()) {
        userMoviesSet.insert(movie.getMovieID());
    }

    for (const User &u: users) {
        if (u.getUserID() != user.getUserID()) {
            int commonCount = 0;
            for (const Movie &movie: u.getMoviesWatched()) {
                if (userMoviesSet.find(movie.getMovieID()) != userMoviesSet.end()) {
                    ++commonCount;
                }
            }

            if (commonCount > 0) {
                commonMoviesCount[u.getUserID()] = commonCount;
            }
        }
    }

    return commonMoviesCount;
}


// A function to create list of users that watched the given movie
// The function checks only users with at least one common movie with the original user
std::unordered_map<int, int> watchedDesiredMovie(
        const std::unordered_map<int, int> &commonMoviesCount,
        const std::vector<User> &allUsers,
        const Movie &movie) {
    std::unordered_map<int, int> usersWatchedDesiredMovie;

    // Iterate through the users in the map
    for (const auto &[userID, commonCount]: commonMoviesCount) {
        // Find the user object with the given userID
        for (const User &user: allUsers) {
            if (user.getUserID() == userID) {
                // Check if the user has watched the desired movie
                for (const Movie &watchedMovie: user.getMoviesWatched()) {
                    if (watchedMovie.getMovieID() == movie.getMovieID()) {
                        // Add user to the result, maintaining their common movie count
                        usersWatchedDesiredMovie[userID] = commonCount;
                        break; // No need to check further movies for this user
                    }
                }
                break; // Exit the loop once the user is found
            }
        }
    }

    return usersWatchedDesiredMovie;
}


// Sum the movie relevance based on common movie count
std::unordered_map<int, int> sumMoviesRelevance(
        const std::unordered_map<int, int> &commonMoviesCount,
        const std::vector<User> &allUsers) {
    std::unordered_map<int, int> movieRelevance;

    // Iterate through the users in the commonMoviesCount map
    for (const auto &[userID, commonCount]: commonMoviesCount) {
        // Find the user object with the given userID
        for (const User &user: allUsers) {
            if (user.getUserID() == userID) {
                // Iterate through the movies the user has watched
                for (const Movie &watchedMovie: user.getMoviesWatched()) {
                    // Add the commonCount (number of common movies) to the relevance of the watched movie
                    movieRelevance[watchedMovie.getMovieID()] += commonCount;
                }
                break; // Exit the loop once the user is found
            }
        }
    }

    return movieRelevance; // Return the map of movieID to relevance
}


// Function to sort and print movies by relevance
void printMoviesByRelevance(const std::unordered_map<int, int> &movieRelevance) {
    // Create a vector of pairs (movieID, relevance) from the map
    std::vector<std::pair<int, int>> sortedMovies(movieRelevance.begin(), movieRelevance.end());

    // Sort the vector by relevance in descending order
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const auto &a, const auto &b) {
        return a.second > b.second; // Sort by relevance (second) in descending order
    });

    // Print the movies with non-zero relevance
    std::cout << "Recommended Movies: ";
    for (const auto &[movieID, relevance]: sortedMovies) {
        if (relevance > 0) {
            std::cout << movieID << " "; // Print the movie ID
        }
    }
    std::cout << std::endl; // Newline after printing all movies
}


void getAndPrintMoviesByRelevance(User &user, const std::vector<User> &users, Movie &movie) {
    // Step 1: Count the number of common movies watched between user and other users
    std::unordered_map<int, int> movieRelevance;  // Movie ID -> relevance count

    // Collect movie IDs watched by the user
    std::unordered_set<int> userMovieIds;
    for (const auto &watchedMovie: user.getMoviesWatched()) {
        userMovieIds.insert(watchedMovie.getMovieID());  // Extract movie ID
    }

    // Step 2: Iterate through all users and calculate relevance
    for (const auto &otherUser: users) {
        if (otherUser.getUserID() == user.getUserID()) continue; // Skip the user itself

        // Find common movies between user and other user
        const std::vector<Movie> &otherUserMovies = otherUser.getMoviesWatched();
        for (const Movie &otherMovie: otherUserMovies) {
            int otherMovieId = otherMovie.getMovieID(); // Extract movie ID
            if (userMovieIds.count(otherMovieId) == 0) {  // Exclude movies already watched by the user
                movieRelevance[otherMovieId]++;
            }
        }
    }

    // Step 3: Sort the movies by relevance
    printMoviesByRelevance(movieRelevance); // Print sorted movies
}