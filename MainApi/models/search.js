// Import mongoose to define the schema and interact with the database
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

/**
 * Movie Schema
 * Defines the structure for storing movie data in the database.
 */
const MovieSchema = new Schema({
    name: {
        type: String, // Name of the movie
        required: true, // Movie name is mandatory
        trim: true // Removes whitespace from both ends of the string
    },
    description: {
        type: String, // Description of the movie
        required: false, // Description is optional
        trim: true // Removes whitespace
    },
    author: {
        type: String, // Author or creator of the movie
        required: false, // Author is optional
        trim: true // Removes whitespace
    },
    cast: [
        {
            name: {
                type: String, // Name of the cast member
                required: false, // Cast member name is optional
                trim: true // Removes whitespace
            },
            role: {
                type: String, // Role played by the cast member
                required: false, // Role is optional
                trim: true // Removes whitespace
            }
        }
    ],
    properties: [
        {
            key: {
                type: String, // Property key (e.g., genre, language)
                required: false, // Key is optional
                trim: true // Removes whitespace
            },
            value: {
                type: String, // Value for the property (e.g., Action, English)
                required: false, // Value is optional
                trim: true // Removes whitespace
            }
        }
    ],
    createdAt: {
        type: Date, // Timestamp for when the movie was added to the database
        default: Date.now // Automatically set the current date and time
    },
    releaseDate: {
        type: Date, // Optional field for movie release date
        required: false // Not mandatory
    },
    quality: {
        type: String, // Optional field for movie quality (e.g., HD, 4K)
        required: false, // Not mandatory
        trim: true // Removes whitespace
    }
});

// Export the Movie model based on the schema
module.exports = mongoose.model('Movie', MovieSchema);
