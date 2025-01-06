
// Import required modules
const express = require('express'); // Framework for building web applications
const bodyParser = require('body-parser'); // Middleware for parsing request bodies
const cors = require('cors'); // Middleware for enabling Cross-Origin Resource Sharing
const mongoose = require('mongoose'); // Library for interacting with MongoDB
const movieRoutes = require('./routes/movie');
const categoryRoutes = require('./routes/category');
const searchRoutes = require('./routes/search');

// Import route files
const users = require('./routes/user'); // Routes for user-related operations
const tokens = require('./routes/token'); // Routes for token-related operations

// Load environment variables based on the current environment
require('custom-env').env(process.env.NODE_ENV, './config');

// Connect to MongoDB using the connection string from environment variables
mongoose.connect(process.env.CONNECTION_STRING, {
}).then(() => console.log('Connected to MongoDB')).catch(err => console.error('MongoDB connection error:', err));

// Initialize the Express application
const app = express();

// Enable CORS to allow requests from other origins

app.use(cors());

// Use body-parser to parse URL-encoded bodies and JSON
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.json());

// Define routes for the application
app.use('/api/users', users); // Routes for user operations (e.g., create, update, delete users)
app.use('/api/tokens', tokens); // Routes for token operations (e.g., validate, create tokens)
app.use('/api/movies', movieRoutes);
app.use('/api/categories', categoryRoutes);
app.use('/api/movies/search', searchRoutes)
// Start the server and listen on the port specified in environment variables
const PORT = process.env.PORT || 3000; // Default to port 3000 if not specified
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
