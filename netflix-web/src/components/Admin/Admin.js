import React, { useState } from "react";
import MoviesAdminPage from "./moviesAdminPage";
import CategoriesAdminPage from "./categoriesAdminPage";
import CreateCategoryForm from "./CreateCategoryForm"; // ✅ Import modal component
import "./Admin.css";

function Admin() {
  const [isMoviesView, setIsMoviesView] = useState(true);
  const [isCategoryModalOpen, setCategoryModalOpen] = useState(false); // ✅ State for modal visibility

  const handleAddCategoryClick = () => {
    setCategoryModalOpen(true); // ✅ Open modal
  };

  const closeCategoryModal = () => {
    setCategoryModalOpen(false); // ✅ Close modal
  };

  return (
    <div className="admin-container">
      {/* Toggle between Movies & Categories */}
      <div className="admin-toggle">
        <button 
          className={`toggle-button ${isMoviesView ? "active" : ""}`} 
          onClick={() => setIsMoviesView(true)}
        >
          Movies
        </button>
        <button 
          className={`toggle-button ${!isMoviesView ? "active" : ""}`} 
          onClick={() => setIsMoviesView(false)}
        >
          Categories
        </button>
      </div>

      {/* Action Buttons */}
      <div className="admin-actions">
        <button className="add-button">Add Movie</button>
        <button className="add-button" onClick={handleAddCategoryClick}>
          Add Category
        </button>
      </div>

      {/* Movies or Categories Page */}
      <div className="admin-content">
        {isMoviesView ? <MoviesAdminPage /> : <CategoriesAdminPage />}
      </div>

      {/* ✅ Show Category Modal when needed */}
      {isCategoryModalOpen && (
        <div className="modal-overlay" onClick={closeCategoryModal}>
          <div className="modal-content" onClick={(e) => e.stopPropagation()}>
            <button className="close-button" onClick={closeCategoryModal}>
              ✕
            </button>
            <CreateCategoryForm onSubmit={closeCategoryModal} onCancel={closeCategoryModal} />
          </div>
        </div>
      )}
    </div>
  );
}

export default Admin;
