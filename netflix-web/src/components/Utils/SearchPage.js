import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom'; // Import navigation hook
import MovieBox from '../Home/movieBox';
import './SearchPage.css';
import { jwtDecode } from 'jwt-decode'; // Import jwtDecode

function SearchPage() {
  const { query } = useParams(); // Extract query from URL
  const navigate = useNavigate(); // Used for redirection
  const [movies, setMovies] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [isAdmin, setIsAdmin] = useState(false);

  // Check if the user is admin from the token
  useEffect(() => {
    const token = localStorage.getItem('jwt');
    if (token) {
      try {
        const decodedToken = jwtDecode(token);
        console.log(decodedToken);
        setIsAdmin(decodedToken.admin === true); // Ensure 'role' matches your token structure
      } catch (error) {
        console.error("Error decoding token:", error);
      }
    }
  }, []);

  // Redirect to home if query is empty or missing
  useEffect(() => {
    if (!query || query.trim() === '') {
      navigate('/home'); // Redirect to home page
      return;
    }
  }, [query, navigate]);

  useEffect(() => {
    const fetchMovies = async () => {
      if (!query || query.trim() === '') return; // Prevent unnecessary API calls

      try {
        setLoading(true);
        const response = await fetch(`http://localhost:4000/api/movies/search/${query}`, {
          headers: { authorization: 'Bearer ' + localStorage.getItem('jwt') },
        });
        if (!response.ok) throw new Error('Failed to fetch search results');
        const data = await response.json();
        setMovies(data);
      } catch (error) {
        setError(error.message);
      } finally {
        setLoading(false);
      }
    };

    fetchMovies();
  }, [query]);

  return (
    <div className="search-page">
      <h1 className="search-title">Search Results for "{query}"</h1>
      {loading && <p className="loading-message">Loading...</p>}
      {error && <p className="error-message">{error}</p>}
      {!loading && !error && movies.length === 0 && <p className="no-results-message">No movies found.</p>}
      <div className="search-results-container">
        {movies.map((movie) => (
          <MovieBox key={movie._id} movie={movie} isAdmin={isAdmin} />
        ))}
      </div>
    </div>
  );
}

export default SearchPage;
