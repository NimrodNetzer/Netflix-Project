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
        const postRequest = `POST ${userId} ${movieId}\n`;
        console.log(`Sending POST request to Recommendation System: ${postRequest}`);
        const response = await socketClient.send(postRequest);

        console.log(`Response from Recommendation System: ${response}`);

        if (response.startsWith('404')) {
            const patchRequest = `PATCH ${userId} ${movieId}\n`;
            console.log(`Sending PATCH request to Recommendation System: ${patchRequest}`);
            const patchResponse = await socketClient.send(patchRequest);

            console.log(`Response from Recommendation System (PATCH): ${patchResponse}`);

            if (patchResponse.startsWith('204')) {
                await updateMongoDBMoviesList(userId, movieId);
                return 'Recommendation created successfully via PATCH';
            } else {
                throw new Error(`Failed to add movie via PATCH: ${patchResponse}`);
            }
        } else if (response.startsWith('201')) {
            await updateMongoDBMoviesList(userId, movieId);
            return 'Recommendation added successfully';
        } else {
            throw new Error(`Unexpected response from server: ${response}`);
        }
    } catch (error) {
        console.error('Error communicating with Recommendation System:', error);
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

module.exports = {
    fetchRecommendations,
    addRecommendation,
};
