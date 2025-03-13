import React, { useState } from 'react';
import './movieBox.css';
import MovieDetailsModal from './movieDetailsModal'; // Import the modal component

function MovieBox({ movie, width }) {
  const [isModalOpen, setModalOpen] = useState(false); // State to handle modal visibility

  const handleInfoClick = () => {
    setModalOpen(true); // Open modal when "Info" button is clicked
  };

  const closeModal = () => {
    setModalOpen(false); // Close modal
  };

  return (
    <div className="movie-box" style={{ width }}>
       <img
    src={"http://localhost:4000/" + movie.picture} // Correctly referencing the movie's picture URL
    alt={movie.name}    // Providing a valid alt description
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
      {/* Include the MovieDetailsModal */}
      <MovieDetailsModal movie={movie} isOpen={isModalOpen} onClose={closeModal} />
    </div>
  );
}

export default MovieBox;
