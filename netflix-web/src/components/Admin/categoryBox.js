import React, { useState } from 'react';
import './categoryBox.css';

function CategoryBox({ category, onDelete, onEdit }) {
  const [isEditing, setIsEditing] = useState(false);
  const [editCategoryName, setEditCategoryName] = useState(category.name);
  const [editCategoryPromoted, setEditCategoryPromoted] = useState(category.promoted);

  const handleSaveEdit = () => {
    onEdit(category._id, editCategoryName, editCategoryPromoted);
    setIsEditing(false);
  };

  return (
    <div className="category-box">
      {/* Category Name */}
      {!isEditing ? (
        <div className="category-content">
          <h3 className="category-title">{category.name}</h3>
          <p className="category-promoted">
            {category.promoted ? '🌟 Promoted' : '📁 Regular'}
          </p>
        </div>
      ) : (
        <div className="category-edit-form">
          <input 
            type="text" 
            value={editCategoryName} 
            onChange={(e) => setEditCategoryName(e.target.value)} 
          />
          <label>
            <input 
              type="checkbox" 
              checked={editCategoryPromoted} 
              onChange={() => setEditCategoryPromoted(!editCategoryPromoted)} 
            />
            Promoted
          </label>
          <button className="save-button" onClick={handleSaveEdit}>Save</button>
          <button className="cancel-button" onClick={() => setIsEditing(false)}>Cancel</button>
        </div>
      )}

      {/* Action Buttons */}
      {!isEditing && (
        <div className="category-actions">
          {/* Delete Button */}
          <button className="action-button delete" onClick={() => onDelete(category._id)}>
            🗑️
          </button>
          {/* Edit Button */}
          <button className="action-button edit" onClick={() => setIsEditing(true)}>
            ✏️
          </button>
        </div>
      )}
    </div>
  );
}

export default CategoryBox;
