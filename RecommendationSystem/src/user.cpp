

#include "user.h"

int User::getUserID() const {
    return userID;
}

void User::addMovieWatched(Movie movie) {
    moviesWatched.push_back(movie);
}

std::vector<Movie> User::getMoviesWatched() const {
    return moviesWatched;
}


