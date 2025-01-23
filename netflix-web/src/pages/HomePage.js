import React from 'react';
import Header from '../components/newHeader'; // Correct relative path to Header.js
import TopMenu from '../components/TopMenu';

function HomePage() {

  
  return (
    <div>
      <Header />
      <TopMenu />
      <h1>Welcome to Netflix Clone</h1>
    </div>
  );
}

export default HomePage;
