import React, { useState } from 'react';
import './FeaturedVideo.css';
import MovieDetailsModal from './movieDetailsModal'; // Import the modal component

function FeaturedVideo({ movie }) {
  const [isModalOpen, setModalOpen] = useState(false); // Modal state

  if (!movie) return null; // Prevent rendering if no movie is available

  return (
    <div className="featured-video">
      <video
        src={`http://localhost:4000/${movie.video}`}
        type="video/mp4"
        autoPlay
        muted
        loop
        className="featured-video-player"
        onClick={() => setModalOpen(true)} // Ensure this updates state properly
      />
      <div className="video-overlay" onClick={() => setModalOpen(true)}>
        <h1 className="featured-title">{movie.title}</h1>
        <p className="featured-description">{movie.description}</p>
      </div>

      {/* Ensure the modal gets the correct state */}
      {isModalOpen && (
        <MovieDetailsModal
          movie={movie}
          isOpen={isModalOpen}
          onClose={() => setModalOpen(false)} // Ensure modal closes
        />
      )}
    </div>
  );
}

export default FeaturedVideo;
