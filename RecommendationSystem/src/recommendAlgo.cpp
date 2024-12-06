#include "iostream"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "User.h"
#include "Movie.h"

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

// Function to count the number of common movies between the given user and other users in the provided list
std::unordered_map<int, int> countCommonMoviesWithGivenUser(
        const std::vector<User> &usersWatchedTargetMovieList,  // List of users to compare against the given user
        const User &givenUser) {  // The target user whose common movies we are counting

    // Map to store the count of common movies for each user, where the key is the user's ID
    std::unordered_map<int, int> commonMoviesWithGivenUserCounterList;

    // Loop through each user in the list of users who watched the target movie
    for (const User &currentUser: usersWatchedTargetMovieList) {

        // Loop through each movie the given user has watched
        for (Movie givenUserCurrentMovie: givenUser.getMoviesWatched()) {

            // Loop through each movie the current user has watched
            for (Movie currentUserMovie: currentUser.getMoviesWatched()) {

                // Skip if the current user is the same as the given user (we don't want to compare the same user)
                if (givenUser.getUserID() == currentUser.getUserID()) continue;

                // If the given user's movie matches the current user's movie
                if (givenUserCurrentMovie.getMovieID() == currentUserMovie.getMovieID()) {

                    // Check if this current user has been encountered before in the map
                    if (commonMoviesWithGivenUserCounterList.count(currentUser.getUserID()) == 0) {
                        // If not, initialize their count with 1 (indicating one common movie found)
                        commonMoviesWithGivenUserCounterList[currentUser.getUserID()] = 1;
                    } else {
                        // If the user is already in the map, increment their count of common movies
                        commonMoviesWithGivenUserCounterList[currentUser.getUserID()] += 1;
                    }
                }
            }
        }
    }
    // Return the map, where the key is the user's ID and the value is the count of common movies with the given user
    return commonMoviesWithGivenUserCounterList;
}


// Function to calculate the relevance of movies for each user based on the number of common movies with the target user
std::unordered_map<int, int>
sumMoviesRelevance(
        std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList, // Map of users and their common movie count with the given user
        const std::vector<User> &allUsers, // List of all users
        const User &givenUser) { // The target user whose common movies are being counted

    // Map to store the final movie relevance count, where the key is the movie ID and the value is its relevance score
    std::unordered_map<int, int> finalMovieCounterList;

    // Loop through all users to create a list of movies watched by users that are not watched by the given user
    for (const User &user: allUsers) {
        // Loop through each movie the user has watched
        for (Movie movie: user.getMoviesWatched()) {
            bool watched = false;  // Flag to track if the movie was watched by the given user

            // Check if the given user has already watched the current movie
            for (const Movie &givenUserWatchedMovie: givenUser.getMoviesWatched()) {
                if (givenUserWatchedMovie.getMovieID() == movie.getMovieID()) {
                    watched = true; // Movie is watched by the given user, set the flag
                    break;
                }
            }

            // Skip this movie if it was already watched by the given user
            if (watched) continue;

            // If the movie was not watched by the given user, add it to the final movie counter list with initial count of 0
            if (finalMovieCounterList.count(movie.getMovieID()) == 0) {
                finalMovieCounterList[movie.getMovieID()] = 0;
            }
        }
    }

    // Now the final movie counter list contains all movies that were not watched by the given user
    // Loop through each movie in the final movie counter list to calculate its relevance score
    for (const auto &pairs: finalMovieCounterList) {
        int currentAllUsersMovieKey = pairs.first; // Movie ID
        int valueZero = pairs.second; // Relevance score (initialized to 0)

        // Loop through each user in the commonMoviesWithGivenUserCounterList to get their common movie count with the given user
        for (const auto &pair: commonMoviesWithGivenUserCounterList) {
            int keyUserID = pair.first; // User ID
            int numberOfCommonMoviesWithTargetUser = pair.second; // Number of common movies with the given user

            // Find the user in the original list by their user ID
            for (const User &currentUser: allUsers) {
                const User &originalKeyUser = currentUser;
                // Skip if the current user ID doesn't match the key user ID
                if (currentUser.getUserID() != keyUserID) {
                    continue;
                }

                // Now we can use the original user object
                // Loop through each movie the original user has watched
                for (const Movie &currentOriginalKeyMovie: originalKeyUser.getMoviesWatched()) {
                    // If the movie is the same as the current movie in the final list, update the relevance score
                    if (currentOriginalKeyMovie.getMovieID() == currentAllUsersMovieKey) {
                        finalMovieCounterList[currentAllUsersMovieKey] +=
                                commonMoviesWithGivenUserCounterList[originalKeyUser.getUserID()]; // Increase score
                        break;
                    }
                }
            }
        }
    }
    // Return the final map, where the key is the movie ID and the value is its relevance score
    return finalMovieCounterList;
}


std::vector<int> sortKeysByValues(const std::unordered_map<int, int> &movieRelevance) {
    // Create a vector of pairs from the map
    std::vector<std::pair<int, int>> elements(movieRelevance.begin(), movieRelevance.end());

    // Sort the vector with a stable tie-breaking mechanism
    std::sort(elements.begin(), elements.end(), [](const auto &a, const auto &b) {
        if (a.second == b.second) {
            return a.first < b.first; // Sort by key in ascending order if values are equal
        }
        return a.second > b.second; // Otherwise, sort by value in descending order
    });

    // Extract the keys into a vector
    std::vector<int> sortedKeys;
    for (const auto &pair: elements) {
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