import React, { useState } from 'react';
import MoviesAdminPage from './moviesAdminPage'; // Ensure default export
import CategoriesAdminPage from './categoriesAdminPage'; // Ensure default export
import './Admin.css';

function Admin() {
  const [isMoviesView, setIsMoviesView] = useState(true);

  return (
    <div className="admin-container">
      <div className="admin-toggle">
        <button 
          className={`toggle-button ${isMoviesView ? 'active' : ''}`} 
          onClick={() => setIsMoviesView(true)}
        >
          Movies
        </button>
        <button 
          className={`toggle-button ${!isMoviesView ? 'active' : ''}`} 
          onClick={() => setIsMoviesView(false)}
        >
          Categories
        </button>
      </div>
      <div className="admin-actions">
        <button className="add-button">Add Movie</button>
        <button className="add-button">Add Category</button>
      </div>
      <div className="admin-content">
        {isMoviesView ? <MoviesAdminPage /> : <CategoriesAdminPage />}
      </div>
    </div>
  );
}

export default Admin;