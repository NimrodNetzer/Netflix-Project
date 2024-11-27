#ifndef USER_H
#define USER_H
#include <vector>

#include "movie.h"


class User {
    private:
        const int userID;
        std::vector<Movie> moviesWatched;
    public:
        User(const int id) : userID(id) {}
        int getUserID() const;
        void addMovieWatched(Movie movie);
        std::vector<Movie> getMoviesWatched() const;
};



#endif //USER_H
