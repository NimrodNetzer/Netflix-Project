const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const movieRoutes = require('./routs/movie'); // Movie routes
const searchRoutes = require('./routs/search'); // Search routes

// Connect to MongoDB with proper error handling
mongoose.connect("mongodb://127.0.0.1:27017/test", { // Using the 'movies' database
    useNewUrlParser: true,
    useUnifiedTopology: true,
})
  .then(() => console.log('MongoDB connected successfully.'))
  .catch((err) => console.error('MongoDB connection error:', err));

// Create the Express app
const app = express();

// Middleware
app.use(cors()); // Enable CORS for cross-origin requests
app.use(bodyParser.urlencoded({ extended: true })); // Parse URL-encoded data
app.use(express.json()); // Parse JSON data

// Routes
app.use('/api/movies', movieRoutes); // Movie-related routes
app.use('/api/movies/search', searchRoutes); // Search routes

// Error handling middleware (for better debugging and response)
app.use((err, req, res, next) => {
    console.error(err.stack); // Log the error
    res.status(500).json({ error: 'An internal server error occurred.' }); // Send a generic error response
});

// Start the server
const PORT = process.env.PORT || 4000; // Use environment variable or default to 4000
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});