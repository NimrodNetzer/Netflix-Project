const { createMovie, getMovieById, deleteMovieById, replaceMovieById } = require('../services/movie');
const recommendationService = require('../services/recommendation');

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
        const message = await recommendationService.deleteWatchedMovie(id);
        console.log(message);
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
};
