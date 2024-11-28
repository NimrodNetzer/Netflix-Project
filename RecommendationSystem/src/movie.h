

#ifndef MOVIE_H
#define MOVIE_H
#include <string>


class Movie {
    private:
        const int movieID;
    public:
        Movie() : movieID(-1) {}
        Movie(const int id) : movieID(id) {}
        int getMovieID() const;
};



#endif //MOVIE_H
