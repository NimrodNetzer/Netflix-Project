import React, { useEffect, useState } from 'react';
import VideoPlayer from '../Utils/VideoPlayer';
import './movieDetailsModal.css';

function MovieDetailsModal({ movie, isOpen, onClose, updateMovie }) { // ✅ Accept updateMovie function
  const [relatedMovies, setRelatedMovies] = useState([]);

  useEffect(() => {
    const fetchRelatedMovies = async () => {
      if (!isOpen || !movie?._id) return;

      try {
        const response = await fetch(`http://localhost:4000/api/movies/${movie._id}/recommend`, {
          method: 'GET',
          headers: {
            'Content-Type': 'application/json',
            authorization: 'Bearer ' + localStorage.getItem('jwt'),
          },
        });

        if (!response.ok) {
          throw new Error(`Network response was not ok (status: ${response.status})`);
        }

        const data = await response.json();

        const moviesDetails = await Promise.all(
          data.recommendedMovies.map(async (id) => {
            const movieResponse = await fetch(`http://localhost:4000/api/movies/${id}`, {
              method: 'GET',
              headers: {
                'Content-Type': 'application/json',
                authorization: 'Bearer ' + localStorage.getItem('jwt'),
              },
            });

            if (!movieResponse.ok) {
              throw new Error(`Failed to fetch movie with ID: ${id}`);
            }

            return movieResponse.json();
          })
        );

        setRelatedMovies(moviesDetails);
      } catch (error) {
        console.error('Error fetching related movies:', error);
      }
    };

    fetchRelatedMovies();
  }, [isOpen, movie]);

  // ✅ Instead of navigating, update the modal with the clicked movie
  const handleMovieClick = (newMovie) => {
    updateMovie(newMovie); // Updates the modal with the clicked movie's details
  };

  if (!isOpen || !movie) return null;

  return (
    <div className="modal-overlay" onClick={onClose}>
      <div className="modal-content" onClick={(e) => e.stopPropagation()}>
        <button className="close-button" onClick={onClose}>✕</button>
        <div className="movie-banner" style={{ height: '420px' }}>
          <img 
            src={`http://localhost:4000/${movie.picture}`} 
            alt={movie.name} 
            className="movie-banner-image"
            style={{ height: '100%', objectFit: 'cover' }}
          />
        </div>

        <div className="movie-details-container">
          <div className="movie-details-header">
            <h1 className="movie-title" style={{ fontFamily: 'Netflix Sans, Arial, sans-serif', fontWeight: 'bold', letterSpacing: '1px' }}>
              {movie.name}
            </h1>
            <div className="action-buttons">
              <button className="play-button">
                <span className="play-icon">▶</span> Play
              </button>
            </div>
          </div>

          <p className="movie-description" style={{ fontFamily: 'Netflix Sans, Arial, sans-serif' }}>
            {movie.description}
          </p>
          <div className="movie-meta" style={{ fontFamily: 'Netflix Sans, Arial, sans-serif' }}>
            <span><strong>Year:</strong> {movie.year}</span>
            <span><strong>Duration:</strong> {movie.time} minutes</span>
            <span><strong>Age Rating:</strong> {movie.age}+</span>
            <span><strong>Language:</strong> {movie.language}</span>
          </div>

          <div className="related-movies">
            <h2 style={{ fontFamily: 'Netflix Sans, Arial, sans-serif', fontWeight: 'bold', letterSpacing: '1px' }}>More Like This</h2>
            <div className="related-movie-list">
              {relatedMovies.length > 0 ? (
                relatedMovies.map((relatedMovie) => (
                  <div 
                    key={relatedMovie._id} 
                    className="related-movie-item" 
                    onClick={() => handleMovieClick(relatedMovie)} // ✅ Update modal with clicked movie
                    style={{ cursor: 'pointer' }} 
                  >
                    <img
                      src={`http://localhost:4000/${relatedMovie.picture}`}
                      alt={relatedMovie.name}
                      className="related-movie-poster"
                    />
                    <p className="related-movie-title" style={{ fontFamily: 'Netflix Sans, Arial, sans-serif', fontWeight: 'bold' }}>
                      {relatedMovie.name}
                    </p>
                  </div>
                ))
              ) : (
                <p className="no-related-movies">No related movies found.</p>
              )}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}

export default MovieDetailsModal;
