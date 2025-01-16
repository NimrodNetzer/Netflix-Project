const { request } = require('express');
const { createMovie, getMovieById, deleteMovieById, replaceMovieById, getMoviesByPromotedCategories } = require('../services/movie');
const recommendationService = require('../services/recommendation')
// Create a new movie
const createMovieController = async (req, res) => {
    try {
        const { name, description, releaseDate } = req.body;

        if (!name || !description || !releaseDate) {
            return res.status(400).json({ message: 'Missing required fields: name, description, or releaseDate' });
        }

        const movieData = req.body;
        const newMovie = await createMovie(movieData);
        res.status(201).location(`/api/movies/${newMovie._id}`).send();
    } catch (error) {
        res.status(400).json({ message: error.message || 'An error occurred while creating the movie' });
    }
};

const getMovies = async (req, res) => {
    try {
        const movies = await getMoviesByPromotedCategories(req.headers['user-id']);
        res.status(200).json({ movies });
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

        res.status(200).json( movie );
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

        const message = await recommendationService.deleteWatchedMovie(id);
        console.log(message);

        res.status(204).send();
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

        res.status(204).location(`/api/movies/${updatedMovie._id}`).send();
    } catch (error) {
        res.status(400).json({ message: error.message || 'An error occurred while updating the movie' });
    }
};

// Fetch recommended movies
const getRecommendations = async (req, res) => {
    console.log('Loading recommendations');
    const { id } = req.params;
    const userId = req.headers['user-id'];

    if (!userId) {
        return res.status(400).json({ error: 'User ID is required' });
    }

    try {
        const recommendedMovies = await recommendationService.fetchRecommendations(userId, id);
        res.json({ recommendedMovies });
    } catch (error) {
        console.error('Error fetching recommendations:', error);
        res.status(error.status || 500).json({
            error: error.message || 'Failed to fetch recommendations',
            details: error.details || null,
        });
    }
};

// Add a recommendation

const addRecommendation = async (req, res) => {
    console.log('Adding recommendation');
    const { id } = req.params;
    const userId = req.headers['user-id'];

    if (!userId) {
        return res.status(400).json({ error: 'User ID is required' });
    }

    try {
        const message = await recommendationService.addRecommendation(userId, id);
        res.status(201).json({ message });
    } catch (error) {
        console.error('Error adding recommendation:', error);
        res.status(error.status || 500).json({
            error: error.message || 'Failed to add recommendation',
            details: error.details || null,
        });
    }
};



module.exports = {
    createMovieController,
    getMovie,
    deleteMovie,
    updateMovie,
    getRecommendations,
    addRecommendation,
    getMovies
};
