import React, { useState } from 'react';
import './movieBox.css';
import MovieDetailsModal from './movieDetailsModal'; // Import the modal component

function MovieBox({ movie, width, isAdmin = false }) {
  const [isModalOpen, setModalOpen] = useState(false);
  const [selectedMovie, setSelectedMovie] = useState(movie);
  const [autoPlay, setAutoPlay] = useState(false); // ✅ Track if video should auto-play

  const handleInfoClick = () => {
    setSelectedMovie(movie);
    setAutoPlay(false); // ❌ No auto-play when clicking "Info"
    setModalOpen(true);
  };

  const handlePlayClick = () => {
    setSelectedMovie(movie);
    setAutoPlay(true); // ✅ Set auto-play when clicking "Play"
    setModalOpen(true);
  };

  const handleDeleteClick = async () => {
    const confirmDelete = window.confirm("Are you sure you want to delete this movie?");
    if (!confirmDelete) return;

    try {
      const response = await fetch(`http://localhost:4000/api/movies/${movie._id}`, {
        method: 'DELETE',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': 'Bearer ' + localStorage.getItem('jwt'),
        },
      });

      if (!response.ok) {
        throw new Error(`Failed to delete movie (status: ${response.status})`);
      }

      alert("Movie deleted successfully");
      window.location.reload(); // Refresh page after deletion
    } catch (error) {
      console.error("Error deleting movie:", error);
      alert("Failed to delete movie");
    }
  };

  const updateMovie = (newMovie) => {
    setSelectedMovie(newMovie);
    setAutoPlay(false); // ❌ Reset auto-play when switching movies
  };

  const closeModal = () => {
    setModalOpen(false);
    setAutoPlay(false); // ❌ Stop auto-play when closing modal
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
            {!isAdmin && (
              <button className="play-button" onClick={handlePlayClick}>▶ Play</button>
            )}
            <button className="info-button" onClick={handleInfoClick}>Info</button>
            {isAdmin && (
              <>
                <button className="edit-button">✏ Edit</button>
                <button className="delete-button" onClick={handleDeleteClick}>🗑 Delete</button>
              </>
            )}
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
      {/* ✅ Pass autoPlay state to modal */}
      <MovieDetailsModal 
        movie={selectedMovie} 
        isOpen={isModalOpen} 
        onClose={closeModal} 
        updateMovie={updateMovie} 
        autoPlay={autoPlay} // ✅ Auto-start video when clicking "Play"
      />
    </div>
  );
}

export default MovieBox;