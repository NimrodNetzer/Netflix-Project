#ifndef USER_H
#define USER_H
#include <vector>

#include "Movie.h"


class User {
    private:
        const int userID;
        std::vector<Movie> moviesWatched;
    public:
        User(const int id) : userID(id) {}
        int getUserID() const;
        // add a movie the user watched to the moviesWatched vector
        void addMovieWatched(Movie movie);
        std::vector<Movie> getMoviesWatched() const;
};



#endif //USER_H
