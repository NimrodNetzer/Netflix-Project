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
    const category = await Category.findById(movieData.categoryId);
    if (!category) {
      throw new Error(`Category with id: ${movieData.categoryId} does not exists.`)
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
    // 1. Fetch the user and their watched movies
    const user = await User.findById(userId)
      .populate('moviesList.movieId')
      .exec();
    
    if (!user) {
      throw new Error('User not found.');
    }
  
    // 2. Get the last 20 watched movies (sorted by `watchedAt` descending)
    const recentlyWatchedMovies = user.moviesList
      .sort((a, b) => new Date(b.watchedAt) - new Date(a.watchedAt))
      .slice(0, 20);
  
    // 3. Fetch all promoted categories
    const promotedCategories = await Category.find({ promoted: true });
    if (promotedCategories.length === 0) {
      throw new Error('No promoted categories found.');
    }
  
    // 4. Collect IDs of the watched movies
    const watchedMovieIds = recentlyWatchedMovies.map(
      (movieRecord) => movieRecord.movieId._id
    );
  
    // 5. Fetch movies from promoted categories that are not in the watched list
    const unWatchedPromotedMovies = await Movie.find({
      categoryId: { $in: promotedCategories.map((cat) => cat._id) },
      _id: { $nin: watchedMovieIds },
    })
      .populate('categoryId', 'name promoted')
      .exec();
  
    // 6. Group promoted movies by category, picking up to 20 random for each
    const promotedMoviesGrouped = promotedCategories.map((category) => {
      const moviesInCategory = unWatchedPromotedMovies
        .filter((movie) => movie.categoryId._id.toString() === category._id.toString())
        .sort(() => 0.5 - Math.random()) // Randomize
        .slice(0, 20);                   // Take up to 20
  
      return {
        category: category.name,
        category_id: category._id,
        promoted: category.promoted,
        movies: moviesInCategory,
      };
    });
  
    // 7. Randomize the watched movies array
    const shuffledWatchedMovies = recentlyWatchedMovies
      .sort(() => 0.5 - Math.random());
  
    // 8. Create a special category for watched movies
    const watchedCategory = {
      category: 'Watched Movies',
      category_id: null,  // or any placeholder
      promoted: false,
      movies: shuffledWatchedMovies.map((entry) => entry.movieId), 
      // If you want the full array with `watchedAt` and other details, remove `.map(...)`
    };
  
    // 9. Combine results and return
    return [...promotedMoviesGrouped, watchedCategory];
  };
  

  

module.exports = {
  createMovie, getMovieById, deleteMovieById, replaceMovieById, getMoviesByPromotedCategories
};
