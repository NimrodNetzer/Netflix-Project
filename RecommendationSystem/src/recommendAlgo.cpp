#include "iostream"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <map>
#include "user.h"
#include "movie.h"

// A function to create list of users that watched the given movie
std::vector<User> watchedDesiredMovie(
        const std::vector<User> &allUsers,
        const Movie &givenMovie) {
    std::vector<User> usersList;
    int targetMovieID = givenMovie.getMovieID();

    // Iterate over all users
    for (const User &user: allUsers) {
        const std::vector<Movie> &userMovies = user.getMoviesWatched();

        // Check if user watched the given movie
        for (const Movie &movie: userMovies) {
            if (movie.getMovieID() == targetMovieID) {
                usersList.push_back(user);  // Store the user in the list
                break;  // No need to check further movies for this user
            }
        }
    }
    return usersList;
}

std::unordered_map<int, int> countCommonMoviesWithGivenUser(
        const std::vector<User> &usersWatchedTargetMovieList,
        const User &givenUser) {

    std::unordered_map<int, int> commonMoviesWithGivenUserCounterList;

    for (const User &currentUser: usersWatchedTargetMovieList) {
        for (Movie givenUserCurrentMovie: givenUser.getMoviesWatched()) {
            for (Movie currentUserMovie: currentUser.getMoviesWatched()) {
                if (givenUser.getUserID() == currentUser.getUserID()) continue;
                if (givenUserCurrentMovie.getMovieID() == currentUserMovie.getMovieID()) {
                    if (commonMoviesWithGivenUserCounterList.count(currentUser.getUserID()) == 0) {
                        commonMoviesWithGivenUserCounterList[currentUser.getUserID()] = 1;
                    } else {
                        commonMoviesWithGivenUserCounterList[currentUser.getUserID()] += 1;
                    }
                }
            }
        }
    }
    // Return map which the key is th user's ID, and the value is the number of common movies with target user
    return commonMoviesWithGivenUserCounterList;
}


std::unordered_map<int, int>
sumMoviesRelevance(std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList,
                   const std::vector<User> &allUsers, const User &givenUser) {

    std::unordered_map<int, int> finalMovieCounterList;

    for (const User &user: allUsers) {
        for (Movie movie: user.getMoviesWatched()) {
            bool watched = false;
            for (const Movie &givenUserWatchedMovie: givenUser.getMoviesWatched()) {
                if (givenUserWatchedMovie.getMovieID() == movie.getMovieID()) {
                    watched = true;
                    break;
                };
            }
            if (watched) continue;
            if (finalMovieCounterList.count(movie.getMovieID()) == 0) {
                finalMovieCounterList[movie.getMovieID()] = 0;
            }
        }
    }

    // Now the final movie counter list is all movies watched
    for (const auto &pairs: finalMovieCounterList) {
        int currentAllUsersMovieKey = pairs.first;
        int valueZero = pairs.second;


        // Iterating the user ID values in the map, the value is the number of common movies with target user
        for (const auto &pair: commonMoviesWithGivenUserCounterList) {
            int keyUserID = pair.first;
            int numberOfCommonMoviesWithTargetUser = pair.second;

            // Find the user in the original list by ID
            for (const User &currentUser: allUsers) {
                const User &originalKeyUser = currentUser;
                // Keep the loop iteration if the current user is with different ID
                if (currentUser.getUserID() != keyUserID) {
                    continue;
                }
                // We can use the original user now
                for (const Movie &currentOriginalKeyMovie: originalKeyUser.getMoviesWatched()) {
                    if (currentOriginalKeyMovie.getMovieID() == currentAllUsersMovieKey) {
                        finalMovieCounterList[currentAllUsersMovieKey] +=
                                commonMoviesWithGivenUserCounterList[originalKeyUser.getUserID()];
                        break;
                    }
                }
            }
        }
    }
    return finalMovieCounterList;
}


std::vector<int> sortKeysByValues(const std::unordered_map<int, int>& movieRelevance) {
    // Create a vector of pairs from the map
    std::vector<std::pair<int, int>> elements(movieRelevance.begin(), movieRelevance.end());

    // Sort the vector with a stable tie-breaking mechanism
    std::sort(elements.begin(), elements.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first < b.first; // Sort by key in ascending order if values are equal
        }
        return a.second > b.second; // Otherwise, sort by value in descending order
    });

    // Extract the keys into a vector
    std::vector<int> sortedKeys;
    for (const auto& pair : elements) {
        sortedKeys.push_back(pair.first);
    }

    size_t size = std::min(sortedKeys.size(), static_cast<size_t>(10));
    return std::vector<int>(sortedKeys.begin(), sortedKeys.begin() + size);
    return sortedKeys;
}


// Combine the algorithm functions
std::vector<int> combineAndCalculateMoviesRelevance(
        const std::vector<User> &allUsers, const std::vector<Movie> &allMovies,
        const User &givenUser, const Movie &givenMovie) {

    // Step 1: Get users who watched the given movie
    std::vector<User> usersWhoWatchedGivenMovie = watchedDesiredMovie(allUsers, givenMovie);

    // Step 2: Get the count of common movies with the given user
    std::unordered_map<int, int> commonMoviesCount =
            countCommonMoviesWithGivenUser(usersWhoWatchedGivenMovie, givenUser);

    // Step 3: Get the movie relevance based on the number of common movies
    std::unordered_map<int, int> movieRelevance =
            sumMoviesRelevance(commonMoviesCount, allUsers, givenUser);

    movieRelevance.erase(givenMovie.getMovieID());
    return sortKeysByValues(movieRelevance);
}