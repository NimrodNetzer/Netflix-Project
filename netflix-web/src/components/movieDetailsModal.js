import React, { useEffect, useState } from 'react';
import './movieDetailsModal.css';

function MovieDetailsModal({ movie, isOpen, onClose }) {
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

        // Fetch details for each movie ID in recommendedMovies
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

  if (!isOpen || !movie) return null;

  return (
    <div className="modal-overlay" onClick={onClose}>
      <div
        className="modal-content"
        onClick={(e) => e.stopPropagation()} /* Prevent click on content from closing */
      >
        <button className="close-button" onClick={onClose}>✕</button>
        {/* Movie Banner Section */}
        <div className="movie-banner">
          <img 
            src={`http://localhost:4000/${movie.picture}`} 
            alt={movie.name} 
            className="movie-banner-image"
          />
        </div>

        <div className="movie-details-container">
          <div className="movie-details-header">
            <h1 className="movie-title">{movie.name}</h1>
            <div className="action-buttons">
              <button className="play-button">
                <span className="play-icon">▶</span> הפעל
              </button>
              <button className="circle-button">
                <span className="icon">👍</span>
              </button>
              <button className="circle-button">+</button>
            </div>
          </div>

          <p className="movie-description">{movie.description}</p>
          <div className="movie-meta">
            <span><strong>Year:</strong> {movie.year}</span>
            <span><strong>Duration:</strong> {movie.time} minutes</span>
            <span><strong>Age Rating:</strong> {movie.age}+</span>
            <span><strong>Language:</strong> {movie.language}</span>
          </div>

          <div className="related-movies">
            <h2>More Like This</h2>
            <div className="related-movie-list">
              {relatedMovies.length > 0 ? (
                relatedMovies.map((relatedMovie) => (
                  <div key={relatedMovie._id} className="related-movie-item">
                    <img
                      src={`http://localhost:4000/${relatedMovie.picture}`}
                      alt={relatedMovie.name}
                      className="related-movie-poster"
                    />
                    <p className="related-movie-title">{relatedMovie.name}</p>
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
