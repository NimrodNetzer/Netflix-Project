const Movie = require('../models/movie'); // Path to your Movie model
const Category = require('../models/category'); // Path to your Movie model
const User = require('../models/user'); // Path to your User model

const createMovie = async (movieData) => {
  try {
    // Required field validation
    const requiredFields = ['name', 'description', 'picture', 'age', 'time', 'releaseDate', 'quality', 'categoryId', 'author'];
    for (const field of requiredFields) {
      if (!movieData[field]) {
        throw new Error(`Missing required field: ${field}`);
      }
    }

    // Specific field validations
    if (typeof movieData.name !== 'string' || movieData.name.trim() === '') {
      throw new Error('Invalid name: must be a non-empty string');
    }
    if (typeof movieData.description !== 'string' || movieData.description.length < 20) {
      throw new Error('Invalid description: must be at least 20 characters long');
    }
    if (!/^https?:\/\/\S+\.\S+$/.test(movieData.picture)) {
      throw new Error('Invalid picture URL');
    }
    if (!Number.isInteger(movieData.age) || movieData.age < 0 || movieData.age > 18) {
      throw new Error('Invalid age: must be an integer between 0 and 18');
    }
    if (!/^\d+h \d+m$/.test(movieData.time)) {
      throw new Error('Invalid time format: must be in the format "Xh Ym"');
    }
    if (isNaN(new Date(movieData.releaseDate).getTime())) {
      throw new Error('Invalid releaseDate: must be a valid date');
    }
    if (!['HD', 'SD', '4K'].includes(movieData.quality)) {
      throw new Error('Invalid quality: must be one of "HD", "SD", or "4K"');
    }
    if (!movieData.categoryId.match(/^[a-fA-F0-9]{24}$/)) {
      throw new Error('Invalid categoryId: must be a valid ObjectId');
    }

    // Optional validations
    if (movieData.cast) {
      if (!Array.isArray(movieData.cast)) {
        throw new Error('Invalid cast: must be an array');
      }
      movieData.cast.forEach((member, index) => {
        if (!member.name) {
          throw new Error(`Invalid cast member at index ${index}: missing name`);
        }
      });
    }

    // Check for duplicates
    const existingMovie = await Movie.findOne({ name: movieData.name, releaseDate: movieData.releaseDate });
    if (existingMovie) {
      throw new Error('A movie with the same name and release date already exists');
    }

    // Create and save the movie
    const newMovie = new Movie({ ...movieData });
    const savedMovie = await newMovie.save();

    return savedMovie;
  } catch (error) {
    console.error('Error creating movie:', error);
    throw new Error(error.message || 'Failed to create movie');
  }
};

const getMovieById = async (movieId) => {
    try {
      // Populate category and any other referenced fields if needed
      const movie = await Movie.findById(movieId);
      if (!movie) {
        return null;
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
  
  const getMoviesByPromotedCategories = async (userId) => {
    // Fetch the user's watched movies
    const user = await User.findById(userId).exec();
    if (!user) {
        throw new Error('User not found.');
    }

    // Get the last 20 movies the user watched (sorted by `watchedAt` in descending order)
    const watchedMovies = user.moviesList
        .sort((a, b) => new Date(b.watchedAt) - new Date(a.watchedAt)) // Sort by watchedAt descending
        .slice(0, 20) // Take the last 20 watched movies
        .map((movie) => movie.movieId); // Extract movie IDs

    // Fetch promoted categories
    const promotedCategories = await Category.find({ promoted: true });

    if (promotedCategories.length === 0) {
        throw new Error('No promoted categories found.');
    }

    // Map promoted category IDs
    const promotedCategoryIds = promotedCategories.map((category) => category._id);

    // Fetch movies in promoted categories that the user hasn't watched yet
    const movies = await Movie.find({
        categoryId: { $in: promotedCategoryIds },
        _id: { $nin: watchedMovies } // Exclude movies the user has watched
    })
        .populate('categoryId', 'name promoted') // Include category details
        .exec();

    // Group movies by category and select up to 20 random movies per category
    const promotedMovies = promotedCategories.map((category) => {
        const categoryMovies = movies
            .filter((movie) => movie.categoryId._id.toString() === category._id.toString())
            .sort(() => 0.5 - Math.random()) // Shuffle the movies
            .slice(0, 20); // Take up to 20 movies

        return {
            category: category.name,
            category_id: category._id,
            promoted: category.promoted,
            movies: categoryMovies
        };
    });

    // Select up to 20 random watched movies

    const randomWatchedMovies = watchedMovies
        .sort(() => 0.5 - Math.random()) // Shuffle the movies
        .slice(0, 20); // Limit to 20 movies
    
    // Step 3: Fetch movie details from the database
    const finalMovies = await Movie.find({ _id: { $in: randomWatchedMovies } })
    .lean() // Return plain JavaScript objects instead of Mongoose documents
    .exec();


    // Add a special category for watched movies
    const specialCategory = {
        category: 'Watched Movies',
        category_id: null, // No specific ID for this category
        promoted: false,
        movies: finalMovies
    };

    // Combine promoted movies and the special watched category
    return [...promotedMovies, specialCategory];
};

  

module.exports = {
  createMovie, getMovieById, deleteMovieById, replaceMovieById, getMoviesByPromotedCategories
};
