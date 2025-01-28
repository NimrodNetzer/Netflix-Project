import React from 'react';
import VideoPlayer from '../components/VideoPlayer';
import video from '../assets/video.mp4'

const Home = () => {
  const videoUrl =  "https://media.w3.org/2010/05/sintel/trailer_hd.mp4";
  const videoName =  "My Awesome Video";
  const startFullscreen =  false;
  const handleLogout = () => {
    localStorage.removeItem('jwt'); // Remove the token
    window.location.href = '/'; // Redirect to login
  };

  return (
    <div>
      <h1>Welcome to the Home Page!</h1>
      <button onClick={handleLogout}>Logout</button>
      <VideoPlayer
        videoUrl={videoUrl}
        videoName={videoName}
        startFullscreen={startFullscreen}
      />

    </div>
  );
};

export default Home;
