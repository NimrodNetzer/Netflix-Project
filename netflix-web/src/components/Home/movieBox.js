import React, { useState } from 'react';
import './movieBox.css';
import MovieDetailsModal from './movieDetailsModal'; // Import the modal component

function MovieBox({ movie, width }) {
  const [isModalOpen, setModalOpen] = useState(false); // ✅ Controls if the modal is open
  const [selectedMovie, setSelectedMovie] = useState(movie); // ✅ Tracks the currently selected movie

  const handleInfoClick = () => {
    setSelectedMovie(movie); // ✅ Set the clicked movie as the selected one
    setModalOpen(true);
  };

  // ✅ Updates the movie inside the modal when clicking a related movie
  const updateMovie = (newMovie) => {
    setSelectedMovie(newMovie);
  };

  const closeModal = () => {
    setModalOpen(false);
  };

  return (
    <div className="movie-box" style={{ width }}>
      <img
        src={`http://localhost:4000/${movie.picture}`}
        alt={movie.name}
        className="default-image"
      />
      <div className="movie-hover-overlay">
        <div className="movie-hover-content">
          {/* Movie Title */}
          <div className="movie-title2">{movie.name}</div>
          <div className="movie-buttons">
            <button className="play-button">▶ Play</button>
            <button className="info-button" onClick={handleInfoClick}>
              Info
            </button>
          </div>
          <div className="movie-info">
            <div className="movie-detail-box">
              <span className="movie-age">{movie.age}+</span>
            </div>
            <div className="movie-detail-box">
              <span className="movie-quality">{movie.quality}</span>
            </div>
            <div className="movie-detail-box">
              <span className="movie-time">{movie.time}</span>
            </div>
          </div>
        </div>
      </div>
      {/* ✅ Pass the updateMovie function to allow changing the movie inside the modal */}
      <MovieDetailsModal 
        movie={selectedMovie} 
        isOpen={isModalOpen} 
        onClose={closeModal} 
        updateMovie={updateMovie} 
      />
    </div>
  );
}

export default MovieBox;
