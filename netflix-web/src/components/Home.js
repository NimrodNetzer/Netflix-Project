// Home.jsx
import React, { useState } from 'react';
import VideoPlayer from '../components/VideoPlayer';

const Home = () => {
  const videoUrl = "https://media.w3.org/2010/05/sintel/trailer_hd.mp4";
  const videoName = "My Awesome Video";
  const [isVideoOpen, setIsVideoOpen] = useState(false); // State to control VideoPlayer visibility

  const handleLogout = () => {
    localStorage.removeItem('jwt'); // Remove the token
    window.location.href = '/'; // Redirect to login
  };

  const handleOpenVideo = () => {
    setIsVideoOpen(true);
  };

  const handleCloseVideo = () => {
    setIsVideoOpen(false);
  };

  return (
    <div>
      <h1>Welcome to the Home Page!</h1>
      <button onClick={handleLogout}>Logout</button>
      <button onClick={handleOpenVideo}>Play Fullscreen</button> {/* Button to open VideoPlayer */}
      
      {isVideoOpen && (
        <VideoPlayer
          videoUrl={videoUrl}
          videoName={videoName}
          play={true}
          startFullscreen={true}
          onClose={handleCloseVideo} // Pass a prop to handle closing
        />
      )}
    </div>
  );
}
export default Home;