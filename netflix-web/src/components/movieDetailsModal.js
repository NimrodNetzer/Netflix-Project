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
        setRelatedMovies(data.movies);
      } catch (error) {
        console.error('Error fetching related movies:', error);
      }
    };

    fetchRelatedMovies();
  }, [isOpen, movie]);

  if (!isOpen || !movie) return null;

  return (
    <div className="modal-overlay">
      <div className="modal-content">
        <button className="close-button" onClick={onClose}>
          ✕
        </button>
        <div className="movie-details">
          <img src={movie.image} alt={movie.name} className="movie-poster" />
          <div className="movie-info">
            <h1>{movie.name}</h1>
            <p>{movie.description}</p>
            <p>
              <strong>Year:</strong> {movie.year}
            </p>
            <p>
              <strong>Duration:</strong> {movie.time} minutes
            </p>
            <p>
              <strong>Age Rating:</strong> {movie.age}+
            </p>
            <p>
              <strong>Language:</strong> {movie.language}
            </p>
          </div>
        </div>
        <div className="related-movies">
          <h2>Related Movies</h2>
          <div className="related-movie-list">
            {relatedMovies.length > 0 ? (
              relatedMovies.map((relatedMovie) => (
                <div key={relatedMovie._id} className="related-movie-item">
                  <img
                    src={relatedMovie.image}
                    alt={relatedMovie.name}
                    className="related-movie-poster"
                  />
                  <p>{relatedMovie.name}</p>
                </div>
              ))
            ) : (
              <p>No related movies found.</p>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}

export default MovieDetailsModal;
