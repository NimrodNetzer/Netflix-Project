import React, { useRef, useState, useEffect } from 'react';
import MovieBox from './movieBox';
import './categoryRow.css';

function CategoryRow({ category, movies, isAdmin = false }) {
  const rowRef = useRef(null);
  const [currentIndex, setCurrentIndex] = useState(0);
  const [moviesPerView, setMoviesPerView] = useState(6); // Default value

  const scrollStep = 3; // Number of movies to scroll per step

  useEffect(() => {
    const updateMoviesPerView = () => {
      if (rowRef.current) {
        const containerWidth = rowRef.current.offsetWidth; // Get the container's width
        const movieBoxWidth = 300; // Width of each movie box in pixels
        const calculatedMoviesPerView = Math.floor(containerWidth / movieBoxWidth); // Calculate how many fit
        setMoviesPerView(calculatedMoviesPerView > 0 ? calculatedMoviesPerView : 1); // Minimum 1
      }
    };

    // Initial calculation and on window resize
    updateMoviesPerView();
    window.addEventListener('resize', updateMoviesPerView);

    return () => window.removeEventListener('resize', updateMoviesPerView);
  }, []);

  // Extend the movies array for infinite scrolling
  const circularMovies =
    movies.length > moviesPerView
      ? [
          ...movies.slice(-moviesPerView), // Add last movies at the beginning
          ...movies,
          ...movies.slice(0, moviesPerView), // Add first movies at the end
        ]
      : movies;

  const totalSegments = Math.ceil(movies.length / scrollStep); // Total scrollable steps

  const handleScroll = (direction) => {
    if (movies.length <= moviesPerView) return;

    const scrollAmount = (rowRef.current.offsetWidth / moviesPerView) * scrollStep; // Width of scrollable step
    let newIndex = currentIndex + direction;

    // Infinite scroll behavior
    if (newIndex < 0) {
      newIndex = totalSegments - 1;
      rowRef.current.style.animation = 'scroll-left 0.6s ease-in-out';
      rowRef.current.scrollTo({
        left: scrollAmount * (totalSegments + 1),
        behavior: 'auto',
      });
    } else if (newIndex >= totalSegments) {
      newIndex = 0;
      rowRef.current.style.animation = 'scroll-right 0.6s ease-in-out';
      rowRef.current.scrollTo({
        left: scrollAmount * moviesPerView,
        behavior: 'auto',
      });
    } else {
      rowRef.current.style.animation =
        direction === 1 ? 'scroll-right 0.6s ease-in-out' : 'scroll-left 0.6s ease-in-out';
    }

    setTimeout(() => {
      rowRef.current.style.animation = ''; // Reset animation after scroll
    }, 600); // Match the duration of the animation

    setCurrentIndex(newIndex);
    rowRef.current.scrollTo({
      left: scrollAmount * (newIndex + (movies.length > moviesPerView ? moviesPerView / scrollStep : 0)),
      behavior: 'smooth',
    });
  };

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
          style={{
            display: 'flex',
            overflowX: 'hidden',
          }}
        >
          {displayedMovies.map((movie) => (
            <MovieBox key={movie._id} movie={movie} isAdmin={isAdmin} />
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
