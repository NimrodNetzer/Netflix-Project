import React, { useState, useEffect } from 'react';
import CategoryRow from './categoryRow'; // Ensure this import is correct
import './Home.css';
import React from 'react';
import TopMenu from './TopMenu';

function Home() {
  const [categories, setCategories] = useState([]);

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
        setCategories(data.movies); // Update state with fetched categories
      } catch (error) {
        console.error('Error fetching movies:', error);
        // Handle errors here (e.g., display an error message to the user)
      }
    };

    fetchMovies(); // Call the fetch function inside useEffect
  }, []); // Empty dependency array: fetch movies only on mount

  return (
    <div className="home">
          <TopMenu />

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