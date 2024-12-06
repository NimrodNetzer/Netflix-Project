

#ifndef MOVIE_H
#define MOVIE_H
#include <string>


class Movie {
    private:
        const int movieID;
    public:
        Movie() : movieID(-1) {}
        Movie(const int id) : movieID(id) {}
        Movie(const Movie& other) : movieID(other.movieID) {}
        int getMovieID() const;

};



#endif //MOVIE_H
