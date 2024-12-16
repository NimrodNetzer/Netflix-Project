#ifndef MOVIE_H
#define MOVIE_H
#include <string>

// Movie class representing a movie entity with a unique movie ID
class Movie {
private:
    const int movieID; // Movie ID (unique identifier for the movie)

public:
    // Default constructor, initializes movieID to -1 (indicating no valid ID)
    Movie() : movieID(-1) {}

    // Constructor with a parameter to initialize movieID with a provided value
    Movie(const int id) : movieID(id) {}

    // Copy constructor, ensures that the movieID of the copied object is properly initialized
    Movie(const Movie& other) : movieID(other.movieID) {}

    // Getter method to retrieve the movieID (unique identifier)
    int getMovieID() const;
};

#endif //MOVIE_H
