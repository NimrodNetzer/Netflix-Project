const { createMovie, getMovieById, deleteMovieById, replaceMovieById } = require('../services/movie');
const socketClient = require('../utils/socketClient'); // Import socket client for communication with Recommendation System
const User = require('../models/user');
const mongoose = require('mongoose'); 
// Configuration for Recommendation System server
const RECOMMENDATION_SYSTEM_HOST = '127.0.0.1'; // Localhost
const RECOMMENDATION_SYSTEM_PORT = 8080;        // Port where RecommendationSystem.exe is running

//const socketClient = new SocketClient(RECOMMENDATION_SYSTEM_HOST, RECOMMENDATION_SYSTEM_PORT);

// Create a new movie
const createMovieController = async (req, res) => {
    try {
        const movieData = req.body;
        const newMovie = await createMovie(movieData);
        res.status(201).json({ newMovie });
    } catch (error) {
        res.status(400).json({
            message: error.message || 'An error occurred while creating the movie',
        });
    }
};

// Get a movie by ID
const getMovie = async (req, res) => {
    try {
        const id = req.params.id;
        const movie = await getMovieById(id);

        if (!movie) {
            return res.status(404).json({ message: 'Movie not found' });
        }

        res.status(200).json({ movie });
    } catch (error) {
        res.status(500).json({
            message: error.message || 'An error occurred while fetching the movie',
        });
    }
};

// Delete a movie by ID
const deleteMovie = async (req, res) => {
    try {
        const id = req.params.id;
        const movie = await deleteMovieById(id);

        if (!movie) {
            return res.status(404).json({ message: 'Movie not found' });
        }

        res.status(200).json({ message: 'Movie deleted successfully', movie });
    } catch (error) {
        res.status(500).json({
            message: error.message || 'An error occurred while deleting the movie',
        });
    }
};

// Update a movie by ID
const updateMovie = async (req, res) => {
    try {
        const { id } = req.params;
        const movieUpdates = req.body;
        const updatedMovie = await replaceMovieById(id, movieUpdates);

        if (!updatedMovie) {
            return res.status(404).json({ message: 'Movie not found' });
        }

        res.status(200).json({ updatedMovie });
    } catch (error) {
        res.status(400).json({
            message: error.message || 'An error occurred while updating the movie',
        });
    }
};

// Fetch recommended movies
const getRecommendations = async (req, res) => {
    console.log('Loading recommendations');
    const { id } = req.params;
    const userId = req.headers['user-id']; // Assume User ID is passed in headers

    if (!userId) {
        return res.status(400).json({ error: 'User ID is required' });
    }

    try {
        const request = `GET ${userId} ${id}\n`;
        console.log(`Sending request to Recommendation System: ${request}`);
        const response = await socketClient.send(request);

        console.log(`Received response from Recommendation System: ${response}`);

        if (response.startsWith('404')) {
            return res.status(404).json({ error: 'User or Movie not found' });
        }

        const recommendedMovies = response.split(',').map((movieId) => parseInt(movieId.trim(), 10));
        res.json({ recommendedMovies });
    } catch (error) {
        console.error('Error communicating with Recommendation System:', error);
        res.status(500).json({
            error: 'Failed to fetch recommendations',
            details: error.message,
        });
    }
};

const addRecommendation = async (req, res) => {
  console.log("Sending request to Recommendation System");
  const { id } = req.params; // Movie ID
  const userId = req.headers['user-id']; // User ID passed in headers

  if (!userId) {
      return res.status(400).json({ error: 'User ID is required' });
  }

  try {
      // Construct the initial POST request
      const postRequest = `POST ${userId} ${id}\n`;
      console.log(`Sending POST request to Recommendation System: ${postRequest}`);
      const response = await socketClient.send(postRequest);

      console.log(`Response from Recommendation System: ${response}`);

      if (response.startsWith('404')) {
          console.log(`Server error encountered, attempting to PATCH the movie for user ${userId}`);

          // Construct a PATCH request
          const patchRequest = `PATCH ${userId} ${id}\n`;
          console.log(`Sending PATCH request to Recommendation System: ${patchRequest}`);
          const patchResponse = await socketClient.send(patchRequest);

          console.log(`Response from Recommendation System (PATCH): ${patchResponse}`);

          if (patchResponse.startsWith('204')) {
              // Update MongoDB with the movie recommendation
              await updateMongoDBMoviesList(userId, id);

              return res.status(204).json({ message: 'Recommendation created successfully via PATCH' });
          } else {
              return res.status(500).json({ error: 'Failed to add movie via PATCH', details: patchResponse });
          }
      } else if (response.startsWith('201')) {
          // Update MongoDB with the movie recommendation
          await updateMongoDBMoviesList(userId, id);

          res.status(201).json({ message: 'Recommendation added successfully' });
      } else {
          res.status(500).json({ error: 'Unexpected response from server', details: response });
      }
  } catch (error) {
      console.error('Error communicating with Recommendation System:', error);
      res.status(500).json({
          error: 'Failed to communicate with Recommendation System',
          details: error.message,
      });
  }
};

const updateMongoDBMoviesList = async (userId, movieId) => {
  console.log(movieId);
  try {
      // Use the provided `movieId` directly, assuming it's a valid ObjectId string
     
      const result = await User.findByIdAndUpdate(
          userId,
          {
              $addToSet: {
                  moviesList: { movieId }
              }
          },
          { new: true, upsert: false } // Return the updated document
      );

      if (!result) {
          throw new Error(`User with ID ${userId} not found`);
      }

      console.log(`Movie ${movieId} successfully added to user ${userId}'s moviesList.`);
      return result; // Return the updated user for further use if needed
  } catch (error) {
      console.error(`Error adding movie to user ${userId}:`, error.message);
      throw error; // Optionally rethrow the error to handle it higher up
  }
};




module.exports = {
    createMovieController,
    getMovie,
    deleteMovie,
    updateMovie,
    getRecommendations,
    addRecommendation,
};
