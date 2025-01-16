const express = require('express');
const router = express.Router();
const searchController = require('../controllers/search');

// Define the GET route with a path parameter for search
router.get('/:query', searchController.searchMovies);

module.exports = router;
