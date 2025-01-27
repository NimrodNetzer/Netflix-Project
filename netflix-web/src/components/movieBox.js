import React from 'react';
import './movieBox.css';

function MovieBox({ movie, width }) {
  return (
    <div className="movie-box" style={{ width }}>
      <img
        src="https://i0.wp.com/picjumbo.com/wp-content/uploads/silhouette-of-young-blonde-with-short-hair-on-orange-background-free-image.jpeg?h=800&quality=80"
        alt={movie.name}
        className="default-image"
      />
      <div className="movie-hover-overlay">
        <div className="movie-hover-content">
          {/* Movie Title */}
          <div className="movie-title">{movie.name}</div>
          <div className="movie-buttons">
            <button className="play-button">▶ Play</button>
            <button className="info-button">info</button>
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
          <div className="movie-categories">
            {movie.categories.map((category, index) => (
              <div key={index} className="movie-detail-box">
                <span className="movie-category">{category.name}</span>
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
}

export default MovieBox;
