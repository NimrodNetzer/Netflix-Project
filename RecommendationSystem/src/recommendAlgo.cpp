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
                if (givenUserCurrentMovie.getMovieID() == currentUserMovie.getMovieID()) {
                    if (commonMoviesWithGivenUserCounterList[currentUser.getUserID()] == 0) {
                        commonMoviesWithGivenUserCounterList[currentUser.getUserID()] = currentUserMovie.getMovieID();
                    } else {
                        commonMoviesWithGivenUserCounterList[currentUser.getUserID()] += currentUserMovie.getMovieID();
                    }
                }
            }
        }
    }
    // Return map which the key is th user's ID, and the value is the number of common movies with target user
    return commonMoviesWithGivenUserCounterList;
}


std::unordered_map<int, int>
sumMoviesRelevance(const std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList,
                   const std::vector<User> &allUsers, const User &givenUser) {

    std::unordered_map<int, int> finalMovieCounterList;

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
            // We will iterate the given user movies list
            for (Movie givenUserMovie: givenUser.getMoviesWatched()) {
                // Iterating the key original user movies list in order to sum the value, movies weight
                for (const Movie &valueUserMovie: originalKeyUser.getMoviesWatched()) {
                    if (valueUserMovie.getMovieID() == givenUserMovie.getMovieID()) {
                        if (finalMovieCounterList[valueUserMovie.getMovieID()] == 0) {
                            finalMovieCounterList[valueUserMovie.getMovieID()] = numberOfCommonMoviesWithTargetUser;
                        } else {
                            finalMovieCounterList[valueUserMovie.getMovieID()] += numberOfCommonMoviesWithTargetUser;
                        }
                    }
                }
            }
        }
    }
    return finalMovieCounterList;
}


// Sorting the map by its values, from high to small
std::map<int, int> sortKeysByValue(const std::unordered_map<int, int> &inputMap) {
    // Step 1: Create a vector of pairs (key, value) from the input unordered_map
    std::vector<std::pair<int, int>> keyValuePairs(inputMap.begin(), inputMap.end());

    // Step 2: Sort the vector by value in descending order
    std::sort(keyValuePairs.begin(), keyValuePairs.end(),
              [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
                  return a.second > b.second;  // Sorting by value (descending)
              });

    // Step 3: Create a map (which automatically sorts by key)
    std::map<int, int> sortedMap;
    for (const auto &pair: keyValuePairs) {
        sortedMap[pair.first] = pair.second;
    }

    return sortedMap;
}


// Combine the algorithm functions
std::map<int, int> combineAndCalculateMoviesRelevance(
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

    return sortKeysByValue(movieRelevance);
}



