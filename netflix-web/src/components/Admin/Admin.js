import React, { useState } from "react";
import MoviesAdminPage from "./moviesAdminPage";
import CategoriesAdminPage from "./categoriesAdminPage";
import CreateCategoryForm from "./CreateCategoryForm";
import CreateMovieForm from "./CreateMovieForm"; // ✅ Import the movie form
import "./Admin.css";


function Admin() {
  const [isMoviesView, setIsMoviesView] = useState(true);
  const [isCategoryModalOpen, setCategoryModalOpen] = useState(false);
  const handleToggle = () => {
    setIsMoviesView(!isMoviesView); // ✅ Toggle between Movies & Categories
  };
  const [isMovieModalOpen, setMovieModalOpen] = useState(false); // ✅ State for Movie Modal


  // Functions to open/close category modal
  const handleAddCategoryClick = () => setCategoryModalOpen(true);
  const closeCategoryModal = () => setCategoryModalOpen(false);

  // Functions to open/close movie modal
  const handleAddMovieClick = () => setMovieModalOpen(true);
  const closeMovieModal = () => setMovieModalOpen(false);

  return (
    <div className="admin-container">
      {/* Toggle Switch for Movies & Categories */}
      <div className="toggle-switch-container">
        <span className="toggle-label">Movies</span>
        <label className="toggle-switch">
          <input type="checkbox" checked={!isMoviesView} onChange={handleToggle} />
          <span className="toggle-slider"></span>
        </label>
        <span className="toggle-label">Categories</span>
      </div>

      {/* Action Buttons */}
      <div className="admin-actions">
        <button className="add-button" onClick={handleAddMovieClick}>
          Add Movie
        </button>
        <button className="add-button" onClick={handleAddCategoryClick}>
          Add Category
        </button>
      </div>

      {/* Display Movies or Categories based on toggle selection */}
      <div className="admin-content">
        {isMoviesView ? <MoviesAdminPage /> : <CategoriesAdminPage />}
      </div>
      {/* Show Category Modal when needed */}
      {/* ✅ Category Modal */}

      {isCategoryModalOpen && (
        <div className="modal-overlay" onClick={closeCategoryModal}>
          <div className="modal-content" onClick={(e) => e.stopPropagation()}>
            <button className="close-button" onClick={closeCategoryModal}>✕</button>
            <CreateCategoryForm onSubmit={closeCategoryModal} onCancel={closeCategoryModal} />
          </div>
        </div>
      )}

      {/* ✅ Movie Modal */}
      {isMovieModalOpen && (
        <div className="modal-overlay" onClick={closeMovieModal}>
          <div className="modal-content" onClick={(e) => e.stopPropagation()}>
            <button className="close-button" onClick={closeMovieModal}>
              ✕
            </button>
            <CreateMovieForm onSubmit={closeMovieModal} onCancel={closeMovieModal} />
          </div>
        </div>
      )}
    </div>
  );
}

export default Admin;
