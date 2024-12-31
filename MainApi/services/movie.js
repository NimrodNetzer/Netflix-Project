const Movie = require('../models/movie'); // Path to your Movie model

const createMovie = async (movieData) => {
  try {
    // Create a new movie instance
    const newMovie = new Movie(movieData);

    // Save the movie to the database
    const savedMovie = await newMovie.save();

    return savedMovie;
  } catch (error) {
    // Handle and log errors
    console.error('Error creating movie:', error);
    throw new Error('Failed to create movie');
  }
};

const getMovieById = async (movieId) => {
    try {
      // Populate category and any other referenced fields if needed
      const movie = await Movie.findById(movieId);
      if (!movie) {
        throw new Error('Movie not found');
      }
      return movie;
    } catch (error) {
      console.error('Error in getMovieById service:', error);
      throw new Error(error.message || 'Failed to fetch movie');
    }
  };

  const deleteMovieById = async (id) => {
    try {
      const movie = await Movie.findById(id);
      if (!movie) {
        return null;
      }
  
      await movie.deleteOne();
      return movie;
    } catch (error) {
      throw new Error(`Error deleting movie: ${error.message}`);
    }
  };

module.exports = {
  createMovie, getMovieById, deleteMovieById
};
