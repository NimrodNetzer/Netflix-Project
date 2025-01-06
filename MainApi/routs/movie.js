const express = require('express');
const { createMovieController, getMovie, deleteMovie, updateMovie, getMovies} = require('../controllers/movie');

const router = express.Router();

// POST route to create a new movie
router.route('/')
    .get(getMovies)
    .post(createMovieController);
router.route('/:id')
    .get(getMovie)
    .delete(deleteMovie)
    .put(updateMovie)
module.exports = router;
