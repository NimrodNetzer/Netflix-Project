import React, { useState } from 'react';
import CategoriesList from './CategoriesList';
import './categoriesAdminPage.css';
const API_URL = process.env.REACT_APP_API_URL;

function CategoriesAdminPage() {
  const [editCategory, setEditCategory] = useState(null);
  const [editCategoryName, setEditCategoryName] = useState('');
  const [editCategoryPromoted, setEditCategoryPromoted] = useState(false);

  const handleEditCategory = (category) => {
    setEditCategory(category);
    setEditCategoryName(category.name);
    setEditCategoryPromoted(category.promoted);
  };

  const handleUpdateCategory = async () => {
    if (!editCategoryName.trim()) return;

    try {
      await fetch(`${API_URL}/api/categories/${editCategory._id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
          authorization: 'Bearer ' + localStorage.getItem('jwt'),
        },
        body: JSON.stringify({
          name: editCategoryName,
          promoted: editCategoryPromoted,
        }),
      });

      setEditCategory(null);
    } catch (error) {
      console.error('Error updating category:', error);
    }
  };

  return (
    <div className="admin-page">
      <h1>Categories Management</h1>
      <CategoriesList onEditCategory={handleEditCategory} />

      {editCategory && (
        <div className="edit-category-form">
          <h2>Edit Category</h2>
          <input type="text" value={editCategoryName} onChange={(e) => setEditCategoryName(e.target.value)} />
          <button onClick={handleUpdateCategory}>Update</button>
        </div>
      )}
    </div>
  );
}

export default CategoriesAdminPage;
