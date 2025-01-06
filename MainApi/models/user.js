// Import mongoose to define the schema and interact with the database
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

/**
 * User Schema
 * Defines the structure for storing user data in the database.
 */
const UserSchema = new Schema({
    _id: {
        type: String, // Allow custom IDs as strings
        required: true // Make the `_id` field mandatory
    },
    email: {
        type: String, // User's email
        required: true, // Email is mandatory
        unique: true // Each email must be unique
    },
    password: {
        type: String, // User's hashed password
        required: true // Password is mandatory
    },
    nickname: {
        type: String, // User's nickname
        required: true // Nickname is mandatory
    },
    picture: {
        type: String, // URL for the user's profile picture
        required: false // Picture is optional
    },
    createdAt: {
        type: Date, // Timestamp for when the user was created
        default: Date.now // Automatically set the current date and time
    }, 
    moviesList:
        [{
            movieId: { type: String}, // ID of the movie
            watchedAt: { type: Date, default: Date.now } // Timestamp for when the movie was added/watched
}]
    });

// Export the User model based on the schema
module.exports = mongoose.model('User', UserSchema);
