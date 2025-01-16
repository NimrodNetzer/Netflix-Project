const express = require('express');
const isAuthenticated = require('./auth'); // Import the authentication middleware
const router = express.Router();
router.use(isAuthenticated);
const searchController = require('../controllers/search');

// Define the GET route with a path parameter for search
router.get('/:query', searchController.searchMovies);

module.exports = router;
