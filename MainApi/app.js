const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
require('custom-env').env(process.env.NODE_ENV,'./config');

// Import category routes
const categoryRoutes = require('./routes/category');

mongoose.connect(process.env.CONNECTION_STRING)

var app = express();
app.use(cors());
app.use(bodyParser.urlencoded({extended : true}));
app.use(express.json());
// app.listen(process.env.PORT);

// Mount Routes
app.use('/api/categories', categoryRoutes);

app.listen(4000);