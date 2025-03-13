import React, { useEffect, useState } from 'react';
import CategoryBox from './categoryBox';
import './categoriesList.css';

function CategoriesList() {
  const [categories, setCategories] = useState([]);
  const [errorMessage, setErrorMessage] = useState('');

  useEffect(() => {
    fetchCategories();
  }, []);

  const fetchCategories = async () => {
    try {
      const response = await fetch('http://localhost:4000/api/categories', {
        headers: { authorization: 'Bearer ' + localStorage.getItem('jwt') },
      });

      if (!response.ok) throw new Error('Failed to fetch categories');
      const data = await response.json();
      setCategories(data);
    } catch (error) {
      console.error('Error fetching categories:', error);
      setErrorMessage('Failed to load categories.');
    }
  };

  const handleDeleteCategory = async (id) => {
    if (!window.confirm('Are you sure you want to delete this category?')) return;

    try {
      const response = await fetch(`http://localhost:4000/api/categories/${id}`, {
        method: 'DELETE',
        headers: { authorization: 'Bearer ' + localStorage.getItem('jwt') },
      });

      const data = await response.json(); // Get response body

      if (!response.ok) {
        throw new Error(data.error || 'Failed to delete category');
      }

      // ✅ Remove deleted category from state
      setCategories((prevCategories) => prevCategories.filter((cat) => cat._id !== id));
    } catch (error) {
      console.error('Error deleting category:', error);
      setErrorMessage(error.message); // Display error message
    }
  };

  const handleEditCategory = async (id, name, promoted) => {
    try {
      const response = await fetch(`http://localhost:4000/api/categories/${id}`, {
        method: 'PATCH',
        headers: {
          'Content-Type': 'application/json',
          authorization: 'Bearer ' + localStorage.getItem('jwt'),
        },
        body: JSON.stringify({ name, promoted }),
      });

      const data = await response.json();

      if (!response.ok) {
        throw new Error(data.error || 'Failed to update category');
      }

      // ✅ Update category in state
      setCategories((prevCategories) =>
        prevCategories.map((cat) =>
          cat._id === id ? { ...cat, name, promoted } : cat
        )
      );
    } catch (error) {
      console.error('Error updating category:', error);
      setErrorMessage(error.message); // Display error message
    }
  };

  return (
    <div className="categories-list">
      {/* ✅ Show error message if an error occurs */}
      {errorMessage && <p className="error-message">{errorMessage}</p>}

      {categories.map((category) => (
        <CategoryBox 
          key={category._id} 
          category={category} 
          onDelete={handleDeleteCategory} 
          onEdit={handleEditCategory} 
        />
      ))}
    </div>
  );
}

export default CategoriesList;
