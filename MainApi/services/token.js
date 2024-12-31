// services/token.js

// Import mongoose and the User model
const mongoose = require('mongoose');
const User = require('../models/user');

/**
 * Authenticate a user by email and password
 * @param {String} email - User's email
 * @param {String} password - User's password
 * @returns {Object|null} The authenticated user object if successful, otherwise null
 */
const authenticateUser = async (email, password) => {
    try {
        // Find a user with the given email and password
        const user = await User.findOne({ email, password });
        if (!user) {
            return null; // User not found or invalid credentials
        }
        return user; // Return the authenticated user
    } catch (error) {
        throw new Error(`Error during authentication: ${error.message}`);
    }
};

module.exports = { authenticateUser };
