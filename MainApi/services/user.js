// Import mongoose to validate ObjectId and the User model
const mongoose = require('mongoose');
const User = require('../models/user');
const user = require('../models/user');

/**
 * Create a new user
 * @param {String} email - User's email address
 * @param {String} password - User's password
 * @param {String} nickname - User's nickname
 * @param {String} picture - URL of the user's picture
 * @returns {Object} The created user
 */
const createUser = async (email, password, nickname, picture) => {

    try {
        const user = new User({ email, password, nickname, picture });
        return await user.save(); // Save the user to the database
    } catch (error) {
        throw new Error(`Error creating user: ${error.message}`);
    }
};

/**
 * Get a user by ID
 * @param {String} id - User's ID
 * @returns {Object|null} The user object if found, otherwise null
 */
const getUserById = async (id) => {
    if (!mongoose.Types.ObjectId.isValid(id)) {
        throw new Error('Invalid ObjectId format');
    }

    try {
        const user = await User.findById(id);
        if (!user) {
            throw new Error('User not found');
        }
        return user;
    } catch (error) {
        throw new Error(`Error fetching user by ID: ${error.message}`);
    }
};

/**
 * Get all users
 * @returns {Array} List of all users
 */
const getUsers = async () => {
    try {
        return await User.find({}); // Retrieve all users from the database
    } catch (error) {
        throw new Error(`Error fetching users: ${error.message}`);
    }
};
const getUserByEmail = async (email) => {
    return await User.findOne({ email }); // Query the database for a user with the given email
};

module.exports = { createUser, getUserById, getUsers, getUserByEmail };