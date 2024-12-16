#include "recommend.h"
#include <sstream>
#include <stdexcept>
#include "Data/DataManager.h"
#include "recommendAlgo.h"

recommend::recommend(IMenu& menu) : m_menu(menu) {}

#include <sstream>
#include <stdexcept>
#include <string>
#include <cctype>  // For isdigit

void recommend::validateString(std::string s) {
    // Trim leading and trailing whitespace
    s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
    s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check if the string is empty after trimming
    if (s.empty()) {
        throw std::invalid_argument("");
    }

    std::istringstream iss(s);
    int userID, movieID;

    // Validate the first part (userID)
    if (!(iss >> userID)) {
        throw std::invalid_argument("");
    }
    if (userID < 0) {
        throw std::invalid_argument("");
    }

    // Validate the second part (movieID)
    if (!(iss >> movieID)) {
        throw std::invalid_argument("");
    }
    if (movieID < 0) {
        throw std::invalid_argument("");
    }

    // Check if there is any extra input after the movie ID
    std::string extra;
    if (iss >> extra) {
        throw std::invalid_argument("" + extra);
    }

    // Optionally, you can check if all characters are digits in the string
    // but this approach works well for IDs that should be numeric
    for (char c : s) {
        if (!std::isdigit(c) && !std::isspace(c)) {
            throw std::invalid_argument("");
        }
    }
}

void recommend::execute(std::string s) {
    try {
        // Validate the input string, ensuring it has the correct format
        validateString(s);
    } catch (const std::invalid_argument& e) {
        // If validation fails, display an error message and exit the function
        m_menu.displayError(e.what());
        return;
    }

    // Get the singleton instance of DataManager to manage data
    DataManager& data_manager = DataManager::getInstance();

    // Initialize an input stream from the string to extract the userID and movieID
    std::istringstream iss(s);
    int userID, movieID;
    iss >> userID >> movieID;

    // Check if the user with the specified userID exists in the data manager
    if (!data_manager.hasUser(userID)) {
        // If user does not exist, display an error and exit
        m_menu.displayError("User not found.");
        return;
    }

    // Check if the movie with the specified movieID exists in the data manager
    if (!data_manager.hasMovie(movieID)) {
        // If movie does not exist, display an error and exit
        m_menu.displayError("Movie not found.");
        return;
    }

    // Combine and calculate movie relevance based on user data and movie data
    std::vector<int> sortedMovies = combineAndCalculateMoviesRelevance(
            data_manager.getUser(userID), data_manager.getMovie(movieID));

    // Display the list of relevant movies to the user
    m_menu.displayMovieList(sortedMovies);
}

