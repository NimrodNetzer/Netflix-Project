import React from 'react';
import VideoPlayer from '../components/VideoPlayer';
import video from '../assets/video.mp4'

const Home = () => {
  const handleLogout = () => {
    localStorage.removeItem('jwt'); // Remove the token
    window.location.href = '/'; // Redirect to login
  };

  return (
    <div>
      <h1>Welcome to the Home Page!</h1>
      <button onClick={handleLogout}>Logout</button>
      <VideoPlayer videoSrc="video"/> 

    </div>
  );
};

export default Home;
