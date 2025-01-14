const express = require('express');
const categoryController = require('../controllers/category');
const {validateUserIdHeader} = require('./authenticate')
const router = express.Router();

router.use(validateUserIdHeader);

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
