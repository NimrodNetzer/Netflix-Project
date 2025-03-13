import React, { useState } from 'react';
import './categoryBox.css';

function CategoryBox({ category, onDelete, onEdit }) {
  const [isEditing, setIsEditing] = useState(false);
  const [editedName, setEditedName] = useState(category.name);
  const [editedPromoted, setEditedPromoted] = useState(category.promoted);
  const [loading, setLoading] = useState(false);
  const [successMessage, setSuccessMessage] = useState('');

  const handleSaveEdit = async () => {
    setLoading(true);
    setSuccessMessage('');

    try {
      await onEdit(category._id, editedName, editedPromoted);
      setSuccessMessage('Category updated successfully!');
      setTimeout(() => {
        setIsEditing(false);
        setSuccessMessage('');
      }, 2000);
    } catch (error) {
      console.error('Error updating category:', error);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="category-box">
      {isEditing ? (
        <div className="edit-mode">
          <h3>Edit Category</h3>

          {/* Category Name Input */}
          <input
            type="text"
            className="form-input"
            value={editedName}
            onChange={(e) => setEditedName(e.target.value)}
            required
          />

          {/* Promoted Toggle */}
          <div className="toggle-section">
            <label className="form-label">Promoted:</label>
            <div className="toggle-switch">
              <input
                type="checkbox"
                id={`promoted-toggle-${category._id}`}
                checked={editedPromoted}
                onChange={() => setEditedPromoted(!editedPromoted)}
              />
              <label htmlFor={`promoted-toggle-${category._id}`} className="toggle-slider"></label>
            </div>
          </div>

          {/* Success Message */}
          {successMessage && <div className="success-message">{successMessage}</div>}

          {/* Save & Cancel Buttons */}
          <div className="edit-actions">
            <button type="button" className="save-button" onClick={handleSaveEdit} disabled={loading}>
              {loading ? 'Saving...' : 'Save'}
            </button>
            <button className="cancel-button" onClick={() => setIsEditing(false)}>Cancel</button>
          </div>
        </div>
      ) : (
        <>
          {/* Display category details */}
          <h3 className="category-title">{category.name}</h3>
          <p className="category-promoted">{category.promoted ? '🌟 Promoted' : '📁 Regular'}</p>

          {/* Edit & Delete Buttons */}
          <div className="category-actions">
            <button className="edit-button" onClick={() => setIsEditing(true)}>✏ Edit</button>
            <button className="delete-button" onClick={() => onDelete(category._id)}>🗑 Delete</button>
          </div>
        </>
      )}
    </div>
  );
}

export default CategoryBox;
