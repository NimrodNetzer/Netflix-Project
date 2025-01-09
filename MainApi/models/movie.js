const mongoose = require('mongoose');
const counter = require('./counter');

const movieSchema = new mongoose.Schema({
  _id: { type: Number },
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
 // categoryId: {
 //   type: mongoose.Schema.Types.ObjectId,
 //   ref: 'Category',
  //  required: true,
 // },
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

movieSchema.pre('save', async function (next) {
  if (!this.movieId) {
      this._id = await counter.getNextSequence('movieId');
  }
  console.log(this._id);
  next();
});

const Movie = mongoose.model('Movie', movieSchema);

module.exports = Movie;
