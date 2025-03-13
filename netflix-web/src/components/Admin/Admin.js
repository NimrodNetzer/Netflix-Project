import React, { useState } from "react";
import MoviesAdminPage from "./moviesAdminPage";
import CategoriesAdminPage from "./categoriesAdminPage";
import CreateCategoryForm from "./CreateCategoryForm"; // ✅ Import modal component
import "./Admin.css";


function Admin() {
  const [isMoviesView, setIsMoviesView] = useState(true);
  const [isCategoryModalOpen, setCategoryModalOpen] = useState(false);

  const handleToggle = () => {
    setIsMoviesView(!isMoviesView); // ✅ Toggle between Movies & Categories
  };

  const handleAddCategoryClick = () => {
    setCategoryModalOpen(true); // ✅ Open modal
  };

  const closeCategoryModal = () => {
    setCategoryModalOpen(false); // ✅ Close modal
  };

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
        <button className="add-button">Add Movie</button>
        <button className="add-button" onClick={handleAddCategoryClick}>
          Add Category
        </button>
      </div>

      {/* Display Movies or Categories based on toggle selection */}
      <div className="admin-content">
        {isMoviesView ? <MoviesAdminPage /> : <CategoriesAdminPage />}
      </div>

      {/* Show Category Modal when needed */}
      {isCategoryModalOpen && (
        <div className="modal-overlay" onClick={closeCategoryModal}>
          <div className="modal-content" onClick={(e) => e.stopPropagation()}>
            <button className="close-button" onClick={closeCategoryModal}>✕</button>
            <CreateCategoryForm onSubmit={closeCategoryModal} onCancel={closeCategoryModal} />
          </div>
        </div>
      )}
    </div>
  );
}

export default Admin;
