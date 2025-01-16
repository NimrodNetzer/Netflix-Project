// Import Express to define routes
const express = require('express');
const router = express.Router();
const userController = require('../controllers/user'); // Import user controller
const isAuthenticated = require('./auth'); // Import the authentication middleware

/**
 * Routes for user operations
 * - GET: Retrieve all users
 * - POST: Create a new user
 */
router.route('/')
    .post(userController.createUser); // Create a new user

/**
 * Routes for specific user operations
 * - GET: Retrieve a user by ID
 * - DELETE: Delete a user by ID
 * - PATCH: Update a user's details by ID
 */
router.route('/:id')
    .get(isAuthenticated,userController.getUser) // Retrieve user by ID
    
// Export the router
module.exports = router;