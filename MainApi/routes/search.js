const express = require('express');
const router = express.Router();
const searchController = require('../controllers/search');

// Define the POST route for search
router.post('/', searchController.searchMovies);

module.exports = router;
