const express = require('express');
const { createMovieController, getMovie, deleteMovie} = require('../controllers/movie');

const router = express.Router();

// POST route to create a new movie
router.route('/')
    .post(createMovieController);
router.route('/:id')
    .get(getMovie)
    .delete(deleteMovie)

module.exports = router;
