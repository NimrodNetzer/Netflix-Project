const express = require('express');
const categoryController = require('../controllers/category');
const isAuthenticated = require('./auth'); // Import the authentication middleware


const router = express.Router();
router.use(isAuthenticated);
router
  .route('/')
  .get(categoryController.getCategories)
  .post(categoryController.createCategory);

router
  .route('/:id')
  .get(categoryController.getCategory)
  .patch(categoryController.updateCategory)
  .delete(categoryController.deleteCategory);

module.exports = router;
