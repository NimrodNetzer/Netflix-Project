const searchService = require('../services/search');

exports.searchMovies = async (req, res) => {
    try {
        const query = req.body.query; // Extract query from request body
        if (!query) {
            return res.status(400).json({ errors: ['Query parameter is required in the body.'] });
        }
        const movies = await searchService.searchMovies(query); // Call the search service
        res.status(200).json(movies); // Return the search results
    } catch (error) {
        console.error('Error while searching for movies:', error);
        res.status(500).json({ message: error.message });
    }
};
