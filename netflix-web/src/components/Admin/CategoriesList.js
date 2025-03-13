import React, { useEffect, useState } from 'react';
import CategoryBox from './categoryBox';
import './categoriesList.css';

function CategoriesList() {
  const [categories, setCategories] = useState([]);
  const [errorMessage, setErrorMessage] = useState('');
  const [successMessage, setSuccessMessage] = useState('');

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

      if (response.status === 204 || response.ok) {
        // ✅ Show success message
        setSuccessMessage('Category deleted successfully!');
        setErrorMessage('');

        // ✅ Refresh the category list
        fetchCategories();

        // ✅ Hide success message after 3 seconds
        setTimeout(() => setSuccessMessage(''), 3000);
      } else {
        const data = await response.json();
        throw new Error(data.error || 'Failed to delete category');
      }
    } catch (error) {
      console.error('Error deleting category:', error);
      setErrorMessage(error.message);
      setSuccessMessage('');
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

      if (response.status === 204 || response.ok) {
        // ✅ Show success message
        setSuccessMessage('Category updated successfully!');
        setErrorMessage('');

        // ✅ Refresh the category list
        fetchCategories();

        // ✅ Hide success message after 3 seconds
        setTimeout(() => setSuccessMessage(''), 3000);
      } else {
        const data = await response.json();
        throw new Error(data.error || 'Failed to update category');
      }
    } catch (error) {
      console.error('Error updating category:', error);
      setErrorMessage(error.message);
      setSuccessMessage('');
    }
  };

  return (
    <div className="categories-container">
      {/* ✅ Show success message when action is successful */}
      {successMessage && <p className="success-message">{successMessage}</p>}
      {/* ✅ Show error message when an error occurs */}
      {errorMessage && <p className="error-message">{errorMessage}</p>}

      <div className="categories-list">
        {categories.map((category) => (
          <CategoryBox 
            key={category._id} 
            category={category} 
            onDelete={handleDeleteCategory} 
            onEdit={handleEditCategory} 
          />
        ))}
      </div>
    </div>
  );
}

export default CategoriesList;
