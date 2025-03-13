import React, { useState, useEffect } from 'react';
import CategoryRow from './categoryRow';
import './Home.css';
import TopMenu from '../Utils/TopMenu';
import FeaturedVideo from './FeaturedVideo'; // Import the new component

function Home() {
  const [categories, setCategories] = useState([]);
  const [featuredMovie, setFeaturedMovie] = useState(null);

  useEffect(() => {
    const fetchMovies = async () => {
      try {
        const response = await fetch('http://localhost:4000/api/movies', {
          method: 'GET',
          headers: {
            'Content-Type': 'application/json',
            'authorization': 'Bearer ' + localStorage.getItem('jwt')
          },
        });

        if (!response.ok) {
          throw new Error(`Network response was not ok (status: ${response.status})`);
        }

        const data = await response.json();
        setCategories(data.movies);

        // Set a featured movie (e.g., first movie from the first category)
        if (data.movies.length > 0 && data.movies[0].movies.length > 0) {
          setFeaturedMovie(data.movies[0].movies[0]);
        }
      } catch (error) {
        console.error('Error fetching movies:', error);
      }
    };

    fetchMovies();
  }, []);

  return (
    <div className="home">
      <TopMenu />

      {/* Featured Video Component */}
      {featuredMovie && <FeaturedVideo movie={featuredMovie} />}

      {/* Category Rows */}
      {categories.map((category) => (
        <CategoryRow
          key={category.category_id}
          category={category.category}
          movies={category.movies}
        />
      ))}
    </div>
  );
}

export default Home;
