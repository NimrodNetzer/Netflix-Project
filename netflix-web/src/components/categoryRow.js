import React, { useRef, useState, useEffect } from 'react';
import MovieBox from './movieBox';
import './categoryRow.css';

function CategoryRow({ category, movies }) {
  const rowRef = useRef(null);
  const [currentIndex, setCurrentIndex] = useState(0);

  const moviesPerView = 6; // Number of movies visible at a time
  const scrollStep = 3; // Number of movies to scroll per step

  // Extend the movies array for infinite scrolling
  const circularMovies =
    movies.length > moviesPerView
      ? [
          ...movies.slice(-moviesPerView), // Add last movies at the beginning
          ...movies,
          ...movies.slice(0, moviesPerView), // Add first movies at the end
        ]
      : movies; // If fewer movies, no duplicates needed

  const totalSegments = Math.ceil(movies.length / scrollStep); // Total scrollable steps

  useEffect(() => {
    if (movies.length > moviesPerView) {
      // On initial load, center the scroll position to the actual movie list
      const initialScrollPosition = moviesPerView * (rowRef.current.offsetWidth / moviesPerView);
      rowRef.current.scrollTo({ left: initialScrollPosition, behavior: 'auto' });
    }
  }, [movies]);

  const handleScroll = (direction) => {
    if (movies.length <= moviesPerView) return; // Disable scrolling for small lists

    const scrollAmount = (rowRef.current.offsetWidth / moviesPerView) * scrollStep; // Width of 3 movies
    let newIndex = currentIndex + direction;

    // Infinite scroll behavior
    if (newIndex < 0) {
      // Jump to the end of the list
      newIndex = totalSegments - 1;
      rowRef.current.style.animation = 'scroll-left 0.6s ease-in-out';
      rowRef.current.scrollTo({
        left: scrollAmount * (totalSegments + 1),
        behavior: 'auto',
      });
    } else if (newIndex >= totalSegments) {
      // Jump to the beginning of the list
      newIndex = 0;
      rowRef.current.style.animation = 'scroll-right 0.6s ease-in-out';
      rowRef.current.scrollTo({
        left: scrollAmount * moviesPerView,
        behavior: 'auto',
      });
    } else {
      // Normal scroll movement
      rowRef.current.style.animation =
        direction === 1 ? 'scroll-right 0.6s ease-in-out' : 'scroll-left 0.6s ease-in-out';
    }

    setTimeout(() => {
      // Reset animation after scroll
      rowRef.current.style.animation = '';
    }, 600); // Match the duration of the animation

    setCurrentIndex(newIndex);

    // Smoothly scroll to the new position
    rowRef.current.scrollTo({
      left: scrollAmount * (newIndex + (movies.length > moviesPerView ? moviesPerView / scrollStep : 0)),
      behavior: 'smooth',
    });
  };

  // Slice the displayed movies dynamically based on the current index
  const displayedMovies = circularMovies.slice(
    currentIndex + (movies.length > moviesPerView ? moviesPerView : 0),
    currentIndex + (movies.length > moviesPerView ? moviesPerView : 0) + moviesPerView
  );

  return (
    <div className="category-row">
      <h2 className="category-title">{category}</h2>
      {movies.length > moviesPerView && (
        <div className="scrollbar-container">
          {Array.from({ length: totalSegments }).map((_, index) => (
            <div
              key={index}
              className={`scrollbar-segment ${index === currentIndex ? 'active' : ''}`}
            ></div>
          ))}
        </div>
      )}
      <div className="row-container">
        {movies.length > moviesPerView && (
          <button className="scroll-button left" onClick={() => handleScroll(-1)}>
            &#9664;
          </button>
        )}
        <div
          className="movie-list"
          ref={rowRef}
          style={{ display: 'flex', overflowX: 'hidden' }}
        >
          {displayedMovies.map((movie) => (
            <MovieBox key={movie._id} movie={movie} />
          ))}
        </div>
        {movies.length > moviesPerView && (
          <button className="scroll-button right" onClick={() => handleScroll(1)}>
            &#9654;
          </button>
        )}
      </div>
    </div>
  );
}

export default CategoryRow;
