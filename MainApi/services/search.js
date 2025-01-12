const Movie = require('../models/movie'); // Import the Movie model

exports.searchMovies = async (query) => {
    try {
        const regex = new RegExp(query, 'i'); // Case-insensitive regex for matching
        return await Movie.find({
            $or: [
                { name: regex },
                { description: regex },
                { author: regex },
                { 'cast.name': regex },
                { 'cast.role': regex },
                { 'properties.value': regex },
            ],
        });
    } catch (error) {
        throw new Error(`Error during movie search: ${error.message}`);
    }
};
