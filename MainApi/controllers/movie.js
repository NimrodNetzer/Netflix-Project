const { createMovie, getMovieById, deleteMovieById, replaceMovieById } = require('../services/movie');

const createMovieController = async (req, res) => {
  try {
    const movieData = req.body;
    const newMovie = await createMovie(movieData);
    res.status(201).json({
      message: 'Movie created successfully',
      data: newMovie,
    });
  } catch (error) {
    res.status(500).json({
      message: error.message || 'An error occurred while creating the movie',
    });
  }
};


const getMovie = async (req, res) => {
    console.log('get movie');
    try {
      const id = req.params.id; // Get the movie ID from the route parameters
      const movie = await getMovieById(id);
  
      res.status(200).json({
        message: 'Movie fetched successfully',
        data: movie,
      });
    } catch (error) {
      res.status(404).json({
        message: error.message || 'Movie not found',
      });
    }
};

const deleteMovie = async (req, res) => {
    const movie = await deleteMovieById(req.params.id);
    if(!movie){
        return res.status(404).json({errors : ['Movie not found']});
    }
    res.json(movie);
}

const updateMovie = async (req, res) => {
  try {
    const { id } = req.params;
    const movieUpdates = req.body;
    const updatedMovie = await replaceMovieById(id, movieUpdates);

    res.status(200).json({
      message: 'Movie updated successfully',
      data: updatedMovie,
    });
  } catch (error) {
    res.status(500).json({
      message: error.message || 'An error occurred while updating the movie',
    });
  }
};



module.exports = {
  createMovieController, getMovie, deleteMovie, updateMovie
};
