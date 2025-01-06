const mongoose = require('mongoose');
const Category = require('../models/category');

// Create a new category
const createCategory = async (name, promoted) => {
  try {
    const category = new Category({ name, promoted });
    return await category.save();
  } catch (error) {
    throw new Error(`Error creating category: ${error.message}`);
  }
};

// Get a category by ID
const getCategoryById = async (id) => {
  if (!mongoose.Types.ObjectId.isValid(id)) {
    throw new Error('Invalid ObjectId format');
  }

  try {
    const category = await Category.findById(id);
    if (!category) {
      throw new Error('Category not found');
    }
    return category;
  } catch (error) {
    throw new Error(`Error fetching category by ID: ${error.message}`);
  }
};

// Get all categories with optional filters
const getCategories = async (filters = {}) => {
  try {
    return await Category.find(filters);
  } catch (error) {
    throw new Error(`Error fetching categories: ${error.message}`);
  }
};

// Update a category by ID
const updateCategory = async (id, name, promoted) => {
  if (!mongoose.Types.ObjectId.isValid(id)) {
    throw new Error('Invalid ObjectId format');
  }

  try {
    const category = await Category.findById(id);
    if (!category) {
      return null;
    }

    // Update fields
    if (name) category.name = name;
    if (typeof promoted !== 'undefined') category.promoted = promoted;

    await category.save();
    return category;
  } catch (error) {
    throw new Error(`Error updating category: ${error.message}`);
  }
};

// Delete a category by ID
const deleteCategory = async (id) => {
  if (!mongoose.Types.ObjectId.isValid(id)) {
    throw new Error('Invalid ObjectId format');
  }

  try {
    const category = await Category.findById(id);
    if (!category) {
      return null;
    }

    await category.deleteOne();
    return category;
  } catch (error) {
    throw new Error(`Error deleting category: ${error.message}`);
  }
};

// Retrieve all categories by ID (if filtering by specific IDs is required)
const getAllCategorieById = async (id) => {
  try {
    return await Category.find({ _id: id });
  } catch (error) {
    throw new Error(`Error fetching categories: ${error.message}`);
  }
};

module.exports = {
  getCategories,
  getCategoryById,
  createCategory,
  updateCategory,
  deleteCategory,
  getAllCategorieById,
};
