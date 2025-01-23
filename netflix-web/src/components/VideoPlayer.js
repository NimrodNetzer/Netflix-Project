import React, { useRef, useState, useEffect } from 'react';
import './VideoPlayer.css';
import myVideo from '../assets/video.mp4';
import ClickableLogo from './ClickableLogo';

const VideoPlayer = ({ width = '100%', height = 'auto' }) => {
  const videoRef = useRef(null);
  const containerRef = useRef(null);
  const [isPlaying, setIsPlaying] = useState(false);
  const [showControls, setShowControls] = useState(false);
  const [progress, setProgress] = useState(0);

  const handlePlayPause = () => {
    if (videoRef.current) {
      if (isPlaying) {
        videoRef.current.pause();
      } else {
        videoRef.current.play();
      }
      setIsPlaying(!isPlaying);
    }
  };

  const handleTimeUpdate = () => {
    if (videoRef.current) {
      const progressPercent = 
        (videoRef.current.currentTime / videoRef.current.duration) * 100;
      setProgress(progressPercent);
    }
  };

  useEffect(() => {
    const videoElement = videoRef.current;
    videoElement.addEventListener('timeupdate', handleTimeUpdate);

    return () => {
      videoElement.removeEventListener('timeupdate', handleTimeUpdate);
    };
  }, []);

  useEffect(() => {
    const handleKeyDown = (event) => {
      if (event.key === ' ' || event.key === 'Spacebar') {
        handlePlayPause();
      }
    };

    window.addEventListener('keydown', handleKeyDown);

    return () => {
      window.removeEventListener('keydown', handleKeyDown);
    };
  }, []);

  return (
    <div 
      ref={containerRef}
      className="video-player-container"
      onMouseEnter={() => setShowControls(true)}
      onMouseLeave={() => setShowControls(false)}
    >
      <video 
        ref={videoRef} 
        src={myVideo} 
        className="video-player" 
        style={{ width, height }} 
        onEnded={() => setIsPlaying(false)}
      />
      {showControls && (
        <>
          <div className="video-overlay"></div>
          <button 
            className="play-pause-button" 
            onClick={handlePlayPause}
          >
            {isPlaying ? (
              <svg width="50" height="50" viewBox="0 0 24 24" fill="white">
                <rect x="6" y="4" width="4" height="16" />
                <rect x="14" y="4" width="4" height="16" />
              </svg>
            ) : (
              <svg width="50" height="50" viewBox="0 0 24 24" fill="white">
                <path d="M8 5v14l11-7z" />
              </svg>
            )}
          </button>
          <div className="progress-bar">
            <div 
              className="progress" 
              style={{width: `${progress}%`}}
            ></div>
          </div>
        </>
      )}
    </div>
  );
};

export default VideoPlayer;