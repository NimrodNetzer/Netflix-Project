import React from 'react';
import TopMenu from './TopMenu';

const Home = () => {
  const handleLogout = () => {
    localStorage.removeItem('jwt'); // Remove the token
    window.location.href = '/'; // Redirect to login
  };

  return (
    <div>
      <TopMenu />
      <h1>Welcome to the Home Page!</h1>
      <button onClick={handleLogout}>Logout</button>
    </div>
  );
};

export default Home;
