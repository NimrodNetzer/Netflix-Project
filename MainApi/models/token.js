// models/token.js

// Import mongoose to define the schema and interact with the database
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

/**
 * Token Schema
 * Defines the structure for storing token-related data for authentication checks.
 */
const TokenSchema = new Schema({
    email: {
        type: String, // The user's email address
        required: true // Email is mandatory
    },
    password: {
        type: String, // The user's password
        required: true // Password is mandatory
    },
    createdAt: {
        type: Date, // Timestamp for when the token entry was created
        default: Date.now // Automatically set the current date and time
    }
});

// Export the Token model based on the schema
module.exports = mongoose.model('Token', TokenSchema);
