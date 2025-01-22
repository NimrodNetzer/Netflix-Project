import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import Login from './components/Login';
import Home from './components/Home'; // New Home screen
import Signup from './components/Signup';
import Hero from './components/Hero';


const PrivateRoute = ({ element: Element }) => {
  const isAuthenticated = localStorage.getItem('jwt'); // Check for JWT
  return isAuthenticated ? <Element /> : <Navigate to="/" />;
};

const App = () => {
  return (
    <Router>
      <Routes>
        <Route path="/login" element={<Login />} />
        <Route path="/signup" element={<Signup />} />
        <Route path="/home" element={<PrivateRoute element={Home} />} />
        <Route path='/' element={
          <div className='App'>
          <Hero />
          </div>
      } />
      </Routes>
    </Router>
  );
};

export default App;