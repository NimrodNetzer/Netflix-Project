const Movie = require('../models/movie'); // Path to your Movie model

const createMovie = async (movieData) => {
  try {
    // Create a new movie instance
    const newMovie = new Movie({
      _id: 5, // Use the custom ID
      ...movieData // Spread the rest of the movie data
  });

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

  const replaceMovieById = async (id, movieUpdates) => {
    try {
      // Validate the incoming data first
      const tempMovie = new Movie(movieUpdates);
      await tempMovie.validate(); // This ensures the data conforms to the schema
  
      // Find and delete the original document
      const existingMovie = await Movie.findById(id);
      if (!existingMovie) {
        throw new Error('Movie not found');
      }
      await existingMovie.deleteOne(); // Delete the original document
  
      // Create and save the new movie with the same ID
      tempMovie._id = id; // Preserve the original ID
      const newMovie = await tempMovie.save(); // Save the validated new document
  
      return newMovie;
    } catch (error) {
      throw new Error(error.message || 'Failed to replace movie');
    }
  };
  
  

module.exports = {
  createMovie, getMovieById, deleteMovieById, replaceMovieById
};
