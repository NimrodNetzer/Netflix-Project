const mongoose = require('mongoose');

const movieSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
    trim: true,
  },
  picture: {
    type: String,
    required: true,
  },
  description: {
    type: String,
    required: true,
  },
  age: {
    type: Number,
    required: true,
  },
  time: {
    type: String, // e.g., "2h 15m"
    required: true,
  },
  releaseDate: {
    type: Date,
    required: true,
  },
  quality: {
    type: String, // e.g., "HD", "SD", "4K"
    required: true,
  },
  categoryId: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Category',
    required: true,
  },
  cast: [
    {
      name: { type: String, required: true },
      role: { type: String },
    },
  ],
  properties: {
    type: Map,
    of: String, // You can use other types depending on your requirements
  },
  movieData: {
    type: Object,
  },
  author: {
    type: String,
    required: true,
  },
}, {
  timestamps: true, // Adds createdAt and updatedAt fields
});

const Movie = mongoose.model('Movie', movieSchema);

module.exports = Movie;
