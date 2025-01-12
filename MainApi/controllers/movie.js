const { createMovie, getMovieById, deleteMovieById, replaceMovieById } = require('../services/movie');
const socketClient = require('../utils/socketClient');
const User = require('../models/user');

// Recommendation System configuration
const RECOMMENDATION_SYSTEM_HOST = '127.0.0.1';
const RECOMMENDATION_SYSTEM_PORT = 8080;

// Create a new movie
const createMovieController = async (req, res) => {
    try {
        const { name, description, releaseDate } = req.body;

        if (!name || !description || !releaseDate) {
            return res.status(400).json({ message: 'Missing required fields: name, description, or releaseDate' });
        }

        const movieData = req.body;
        const newMovie = await createMovie(movieData);
        res.status(201).json({ newMovie });
    } catch (error) {
        res.status(400).json({ message: error.message || 'An error occurred while creating the movie' });
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
        res.status(500).json({ message: error.message || 'An error occurred while fetching the movie' });
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
        res.status(500).json({ message: error.message || 'An error occurred while deleting the movie' });
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
        res.status(400).json({ message: error.message || 'An error occurred while updating the movie' });
    }
};

// Fetch recommended movies
const getRecommendations = async (req, res) => {
    const { id } = req.params;
    const userId = req.headers['user-id'];

    if (!userId) {
        return res.status(400).json({ error: 'User ID is required' });
    }

    try {
        const request = `GET ${userId} ${id}\n`;
        const response = await socketClient.send(request);

        if (response.startsWith('404')) {
            return res.status(404).json({ error: 'User or Movie not found' });
        }

        const recommendedMovies = response.split(',').map((movieId) => parseInt(movieId.trim(), 10));
        res.json({ recommendedMovies });
    } catch (error) {
        res.status(500).json({ error: 'Failed to fetch recommendations', details: error.message });
    }
};

// Add a recommendation
const addRecommendation = async (req, res) => {
    const { id } = req.params;
    const userId = req.headers['user-id'];

    if (!userId) {
        return res.status(400).json({ error: 'User ID is required' });
    }

    try {
        const postRequest = `POST ${userId} ${id}\n`;
        const response = await socketClient.send(postRequest);

        if (response.startsWith('404')) {
            // Attempt a PATCH request if POST fails
            const patchRequest = `PATCH ${userId} ${id}\n`;
            const patchResponse = await socketClient.send(patchRequest);

            if (patchResponse.startsWith('204')) {
                await updateMongoDBMoviesList(userId, id);
                return res.status(204).json({ message: 'Recommendation created successfully via PATCH' });
            } else {
                return res.status(500).json({ error: 'Failed to add movie via PATCH', details: patchResponse });
            }
        } else if (response.startsWith('201')) {
            await updateMongoDBMoviesList(userId, id);
            return res.status(201).json({ message: 'Recommendation added successfully' });
        } else {
            return res.status(500).json({ error: 'Unexpected response from server', details: response });
        }
    } catch (error) {
        res.status(500).json({ error: 'Failed to communicate with Recommendation System', details: error.message });
    }
};

// Update MongoDB movies list
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

        console.log(`Movie ${movieId} successfully added to User ${userId}'s moviesList.`);
        return result;
    } catch (error) {
        console.error(`Error adding movie to User ${userId}:`, error.message);
        throw error;
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
