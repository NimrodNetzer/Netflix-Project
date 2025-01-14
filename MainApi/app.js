
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const movieRoutes = require('./routes/movie');
const categoryRoutes = require('./routes/category');
const searchRoutes = require('./routes/search');
const users = require('./routes/user');
const tokens = require('./routes/token');

// Load environment variables based on the current environment
//require('custom-env').env(process.env.NODE_ENV, './config');

mongoose.connect("mongodb://127.0.0.1:27017")
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('MongoDB connection error:', err));

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
