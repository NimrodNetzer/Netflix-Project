import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import Login from './components/Login/Login';
import Home from './components/Home/Home'; // New Home screen
import Signup from './components/Login/Signup';
import Hero from './components/FirstPage/Hero';
import SearchPage from './components/Utils/SearchPage'; 
import TopMenu from './components/Utils/TopMenu'; 

const PrivateRoute = ({ element: Element }) => {
  const isAuthenticated = localStorage.getItem('jwt'); // Check for JWT
  return isAuthenticated ? <Element /> : <Navigate to="/" />;
};

const App = () => {
  return (
    <Router>
            <TopMenu /> {/* ✅ TopMenu is only here once */}
      <Routes>
        <Route path="/login" element={<Login />} />
        <Route path="/signup" element={<Signup />} />
        <Route path="/home" element={<Home/>} />
        <Route path="/search/:query" element={<SearchPage />} />

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