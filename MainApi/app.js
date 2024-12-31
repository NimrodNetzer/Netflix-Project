const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const movieRoutes = require('./routes/movie');

//require('custom-env').env(process.env.NODE_ENV,'./config');
mongoose.connect("mongodb://127.0.0.1:27017")

var app = express();
app.use(cors());
app.use(bodyParser.urlencoded({extended : true}));
app.use(express.json());
app.use('/api/movies', movieRoutes);

app.listen(4000);