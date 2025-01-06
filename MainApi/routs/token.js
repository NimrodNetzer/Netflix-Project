// routes/token.js

// Import Express to define routes
const express = require('express');
const router = express.Router();
const tokenController = require('../controllers/token'); // Import token controller

/**
 * POST /api/tokens
 * Authenticate a user by email and password
 */
router.post('/', tokenController.authenticateUser); // Authenticate user

// Export the router
module.exports = router;
