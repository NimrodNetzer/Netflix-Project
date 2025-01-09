// recommendationService.js
const socketClient = require('../utils/socketClient'); // Import socket client for communication with Recommendation System
const User = require('../models/user');
const mongoose = require('mongoose'); 
// Configuration for Recommendation System server
const RECOMMENDATION_SYSTEM_HOST = '127.0.0.1'; // Localhost
const RECOMMENDATION_SYSTEM_PORT = 8080;        // Port where RecommendationSystem.exe is running

const fetchRecommendations = async (userId, movieId) => {
    const request = `GET ${userId} ${movieId}\n`;
    console.log(`Sending request to Recommendation System: ${request}`);
    const response = await socketClient.send(request);

    console.log(`Received response from Recommendation System: ${response}`);

    if (response.startsWith('404')) {
        const error = new Error('User or Movie not found');
        error.status = 404;
        throw error;
    }

    return response.split(',').map((movieId) => parseInt(movieId.trim(), 10));
};

const addRecommendation = async (userId, movieId) => {
    try {
      await updateMongoDBMoviesList(userId, movieId);
   
      const postResponse = await socketClient.send(`POST ${userId} ${movieId}\n`);
      
      if (postResponse.startsWith('201')) {
        return 'Recommendation added successfully';
      }
      
      if (postResponse.startsWith('404')) {
        const patchResponse = await socketClient.send(`PATCH ${userId} ${movieId}\n`);
        if (patchResponse.startsWith('204')) {
          return 'Recommendation created successfully via PATCH';
        }
        throw new Error(`PATCH failed: ${patchResponse}`);
      }
      
      throw new Error(`Unexpected response: ${postResponse}`); 
    } catch (error) {
      console.error('Recommendation System error:', error);
      error.status = 500;
      throw error;
    }
};

const updateMongoDBMoviesList = async (userId, movieId) => {
    try {
        const result = await User.findByIdAndUpdate(
            userId,
            { $addToSet: { moviesList: { movieId } } },
            { new: true, upsert: false }
        );

        if (!result) {
            throw new Error(`User with ID ${userId} not found`);
        }

        console.log(`Movie ${movieId} successfully added to user ${userId}'s moviesList.`);
        return result;
    } catch (error) {
        console.error(`Error adding movie to user ${userId}:`, error.message);
        throw error;
    }
};


const deleteWatchedMovie = async (movieId) => {
    try {
      await User.updateMany({}, { $pull: { moviesList: { movieId } } });
      const users = await User.find({});
      
      for (const user of users) {
        await socketClient.send(`DELETE ${user._id} ${movieId}\n`);
      }
      
      return `Movie ${movieId} deleted from ${users.length} users`;
    } catch (error) {
      console.error('Delete recommendation error:', error);
      error.status = 500;
      throw error;
    }
};
   

module.exports = {
    fetchRecommendations,
    addRecommendation,
    deleteWatchedMovie
};
