import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import Login from './components/Login';
import Home from './components/Home'; // New Home screen
import Signup from './components/Signup';


const PrivateRoute = ({ element: Element }) => {
  const isAuthenticated = localStorage.getItem('jwt'); // Check for JWT
  return isAuthenticated ? <Element /> : <Navigate to="/" />;
};

const App = () => {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Login />} />
        <Route path="/signup" element={<Signup />} />
        <Route path="/home" element={<PrivateRoute element={Home} />} />
      </Routes>
    </Router>
  );
};

export default App;