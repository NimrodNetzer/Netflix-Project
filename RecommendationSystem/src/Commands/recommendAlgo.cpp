#include "iostream"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../objects/User.h"
#include "../objects/Movie.h"
#include "../Data/DataManager.h"

// Function to count the number of common movies between the given user and other users in the provided list
std::unordered_map<int, int> countCommonMoviesWithGivenUser(
        const Movie &givenMovie,  // List of users to compare against the given user
        const User &givenUser) {  // The target user whose common movies we are counting

    DataManager &dataManager = DataManager::getInstance();
    // Map to store the count of common movies for each user, where the key is the user's ID
    std::unordered_map<int, int> commonMoviesWithGivenUserCounterList;

    std::vector<int> usersWatchedTargetMovieList =
            dataManager.getUsersWhoWatchedMovie(givenMovie.getMovieID());

    // Loop through each user in the list of users who watched the target movie
    for (int &currentUser: usersWatchedTargetMovieList) {

        // Loop through each movie the given user has watched
        for (int givenUserCurrentMovie: dataManager.getMoviesWatchedByUser(givenUser.getUserID())) {

            // Loop through each movie the current user has watched
            for (int currentUserMovie: dataManager.getMoviesWatchedByUser(currentUser)) {

                // Skip if the current user is the same as the given user (we don't want to compare the same user)
                if (givenUser.getUserID() == currentUser) continue;

                // If the given user's movie matches the current user's movie
                if (givenUserCurrentMovie == currentUserMovie) {

                    // Check if this current user has been encountered before in the map
                    if (commonMoviesWithGivenUserCounterList.count(currentUser) == 0) {
                        // If not, initialize their count with 1 (indicating one common movie found)
                        commonMoviesWithGivenUserCounterList[currentUser] = 1;
                    } else {
                        // If the user is already in the map, increment their count of common movies
                        commonMoviesWithGivenUserCounterList[currentUser] += 1;
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
        // Map of users and their common movie count with the given user
        std::unordered_map<int, int> &commonMoviesWithGivenUserCounterList,
        const User &givenUser) { // The target user whose common movies are being counted

    // Map to store the final movie relevance count, where the key is the movie ID and the value is its relevance score
    std::unordered_map<int, int> finalMovieCounterList;

    DataManager &dataManager = DataManager::getInstance();

    // Loop through all users to create a list of movies watched by users that are not watched by the given user
    for (int user: dataManager.getUserIds()) {
        // Loop through each movie the user has watched
        for (Movie movie: dataManager.getMoviesWatchedByUser(user)) {
            bool watched = dataManager.userWatchedMovie(givenUser.getUserID() , movie.getMovieID());  // Flag to track if the movie was watched by the given user
            // Skip this movie if it was already watched by the given user
            if (watched) continue;

            // If the movie was not watched by the given user, add it to the final movie counter list with initial count of 0
            if (finalMovieCounterList.count(movie.getMovieID()) == 0) {
                finalMovieCounterList[movie.getMovieID()] = 0;
            }
        }
    }


    for (const auto &pairs: finalMovieCounterList) {
        int currentAllUsersMovieKey = pairs.first; // Movie ID
        int valueZero = pairs.second; // Relevance score (initialized to 0)

        for (int userID: dataManager.getUsersWhoWatchedMovie(currentAllUsersMovieKey)) {
            if (commonMoviesWithGivenUserCounterList.find(userID) != commonMoviesWithGivenUserCounterList.end()) {
                finalMovieCounterList[currentAllUsersMovieKey] += commonMoviesWithGivenUserCounterList[userID];
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
}


// Combine the algorithm functions
std::vector<int> combineAndCalculateMoviesRelevance(const User &givenUser, const Movie &givenMovie) {

    // Step 2: Get the count of common movies with the given user
    std::unordered_map<int, int> commonMoviesCount = countCommonMoviesWithGivenUser(givenMovie, givenUser);

    // Step 3: Get the movie relevance based on the number of common movies
    std::unordered_map<int, int> movieRelevance =
            sumMoviesRelevance(commonMoviesCount, givenUser);

    movieRelevance.erase(givenMovie.getMovieID());
    return sortKeysByValues(movieRelevance);
}