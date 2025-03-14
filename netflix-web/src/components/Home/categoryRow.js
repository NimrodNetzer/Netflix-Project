import React, { useRef, useState, useEffect } from 'react';
import MovieBox from './movieBox';
import './categoryRow.css';

function CategoryRow({ category, movies, isAdmin = false }) {
  const rowRef = useRef(null);
  const [currentIndex, setCurrentIndex] = useState(0);
  const [moviesPerView, setMoviesPerView] = useState(6);
  const scrollStep = 3; // Number of movies to scroll per step

  useEffect(() => {
    const updateMoviesPerView = () => {
      if (rowRef.current) {
        const containerWidth = rowRef.current.offsetWidth;
        const movieBoxWidth = 300;
        const calculatedMoviesPerView = Math.max(1, Math.floor(containerWidth / movieBoxWidth));
        setMoviesPerView(calculatedMoviesPerView);
      }
    };

    updateMoviesPerView();
    window.addEventListener('resize', updateMoviesPerView);
    return () => window.removeEventListener('resize', updateMoviesPerView);
  }, []);

  // 🔹 Ensure movies are available before rendering
  if (!movies || movies.length === 0) {
    return <h2 className="category-title">No movies available in {category}</h2>;
  }

  // 🔹 Fix Infinite Scroll Issues
  const extendedMovies =
    movies.length > moviesPerView
      ? [...movies, ...movies.slice(0, Math.min(moviesPerView, movies.length))]
      : movies;

  const handleScroll = (direction) => {
    if (movies.length <= moviesPerView) return;

    const scrollAmount = (rowRef.current.offsetWidth / moviesPerView) * scrollStep;
    let newIndex = currentIndex + direction;

    if (newIndex < 0) {
      newIndex = Math.ceil(movies.length / scrollStep) - 1;
      rowRef.current.scrollTo({ left: scrollAmount * (movies.length - moviesPerView), behavior: 'auto' });
    } else if (newIndex * scrollStep >= movies.length) {
      newIndex = 0;
      rowRef.current.scrollTo({ left: 0, behavior: 'auto' });
    } else {
      rowRef.current.scrollTo({ left: scrollAmount * newIndex, behavior: 'smooth' });
    }

    setCurrentIndex(newIndex);
  };

  return (
    <div className="category-row">
      <h2 className="category-title">{category}</h2>
      <div className="row-container">
        {movies.length > moviesPerView && (
          <button className="scroll-button left" onClick={() => handleScroll(-1)}>
            &#9664;
          </button>
        )}
        <div className="movie-list" ref={rowRef}>
          {extendedMovies.map((movie, index) => (
            <MovieBox key={index} movie={movie} isAdmin={isAdmin} />
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
