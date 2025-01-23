import React from 'react';
import Header from '../components/newHeader'; // Correct relative path to Header.js
import VideoPlayer from '../components/VideoPlayer';
function HomePage() {
  return (
    <div>
      <Header />
      <h1>Welcome to Netflix Clone</h1>
      <VideoPlayer videoSrc="../assets/video.mp4"/> 
    </div>
  );
}

export default HomePage;
