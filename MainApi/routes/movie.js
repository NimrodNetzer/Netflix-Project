const express = require('express');
const { 
    createMovieController, 
    getMovie, 
    deleteMovie, 
    updateMovie, 
    getRecommendations, 
    addRecommendation 
} = require('../controllers/movie');

const router = express.Router();

// Movie Routes
router
    .route('/')
    .post(createMovieController);

router
    .route('/:id')
    .get(getMovie)
    .delete(deleteMovie)
    .put(updateMovie);

// Recommendation Routes
router
    .route('/:id/recommend')
    .get(getRecommendations) // Fetch recommended movies
    .post(addRecommendation); // Add watched movie for recommendation

module.exports = router;
