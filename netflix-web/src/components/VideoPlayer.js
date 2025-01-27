import React, { useRef, useState , useCallback, useEffect} from "react";
import {
  FaPlay,
  FaPause,
  FaUndo,
  FaRedo,
  FaAngleLeft,
  FaExpand,
  FaCompress,
  FaCog,
  FaVolumeUp,
} from "react-icons/fa";
import "./VideoPlayer.css";

const VideoPlayer = () => {
  const videoRef = useRef(null);
  const containerRef = useRef(null);
  const [showControls, setShowControls] = useState(true);

  // Instead of [timer, setTimer], we use a ref:
  const timerRef = useRef(null);

  // Only depends on setShowControls (which is stable), not on timerRef
  const resetTimer = useCallback(() => {
    setShowControls(true);

    // Clear old timer if any
    if (timerRef.current) {
      clearTimeout(timerRef.current);
    }

    // Create a new timer
    timerRef.current = setTimeout(() => {
      setShowControls(false);
    }, 3000);
  }, [setShowControls]);

  useEffect(() => {
    function handleMouseMove() {
      resetTimer();
    }

    const container = containerRef.current;
    if (container) {
      container.addEventListener("mousemove", handleMouseMove);
      container.addEventListener("touchstart", handleMouseMove);
    }

    // Clear timer on unmount
    return () => {
      if (container) {
        container.removeEventListener("mousemove", handleMouseMove);
        container.removeEventListener("touchstart", handleMouseMove);
      }
      // Clear the timer if still active
      if (timerRef.current) {
        clearTimeout(timerRef.current);
      }
    };
  }, [resetTimer]);

  // Call it once on mount
  useEffect(() => {
    resetTimer();
    // eslint-disable-next-line
  }, []);

  // Playback states
  const [isPlaying, setIsPlaying] = useState(false);
  const [progress, setProgress] = useState(0); // percentage
  const [duration, setDuration] = useState(0);
  const [currentTime, setCurrentTime] = useState(0);

  // Volume
  const [volume, setVolume] = useState(1);

  // Fullscreen
  const [isFullscreen, setIsFullscreen] = useState(false);

  // Play/Pause toggle
  const handlePlayPause = () => {
    if (!videoRef.current) return;
    if (isPlaying) {
      videoRef.current.pause();
    } else {
      videoRef.current.play();
    }
    setIsPlaying(!isPlaying);
  };

  // Skip forward/backward 10s
  const handleSkip = (seconds) => {
    if (!videoRef.current) return;
    videoRef.current.currentTime += seconds;
  };

  // When metadata is loaded, get duration
  const handleLoadedMetadata = () => {
    if (videoRef.current) {
      setDuration(videoRef.current.duration);
    }
  };

  // On time update, calculate current progress
  const handleTimeUpdate = () => {
    if (videoRef.current) {
      const current = videoRef.current.currentTime;
      const dur = videoRef.current.duration;
      setCurrentTime(current);
      setProgress((current / dur) * 100);
    }
  };

  // Seek
  const handleSeek = (e) => {
    if (!videoRef.current) return;
    const manualChange = Number(e.target.value);
    videoRef.current.currentTime = (manualChange / 100) * duration;
    setProgress(manualChange);
  };

  // Volume
  const handleVolumeChange = (e) => {
    if (!videoRef.current) return;
    const newVolume = Number(e.target.value);
    setVolume(newVolume);
    videoRef.current.volume = newVolume;
  };

  // Fullscreen
  const handleFullScreen = () => {
    const playerContainer = containerRef.current;
    if (!document.fullscreenElement) {
      // Enter fullscreen
      if (playerContainer.requestFullscreen) {
        playerContainer.requestFullscreen();
      } else if (playerContainer.msRequestFullscreen) {
        playerContainer.msRequestFullscreen();
      } else if (playerContainer.mozRequestFullScreen) {
        playerContainer.mozRequestFullScreen();
      } else if (playerContainer.webkitRequestFullscreen) {
        playerContainer.webkitRequestFullscreen();
      }
      setIsFullscreen(true);
    } else {
      // Exit fullscreen
      if (document.exitFullscreen) {
        document.exitFullscreen();
      } else if (document.msExitFullscreen) {
        document.msExitFullscreen();
      } else if (document.mozCancelFullScreen) {
        document.mozCancelFullScreen();
      } else if (document.webkitExitFullscreen) {
        document.webkitExitFullscreen();
      }
      setIsFullscreen(false);
    }
  };

  // Format time (e.g. 1:23)
  const formatTime = (timeSec) => {
    if (!timeSec) return "0:00";
    const minutes = Math.floor(timeSec / 60);
    const seconds = Math.floor(timeSec - minutes * 60);
    return `${minutes}:${seconds < 10 ? "0" + seconds : seconds}`;
  };

  return (
    <div
      ref={containerRef}
      className={`player-container ${showControls ? "show" : "hide"}`}
    >
      {/* Video Element */}
      <video
        ref={videoRef}
        className="video"
        src="https://media.w3.org/2010/05/sintel/trailer_hd.mp4"
        onLoadedMetadata={handleLoadedMetadata}
        onTimeUpdate={handleTimeUpdate}
        onClick={handlePlayPause} // Click video to toggle play/pause
      />

      {/* Top Bar */}
      <div className="top-bar">
        <div className="left-actions">
          {/* Back Button */}
          <button className="icon-btn">
            <FaAngleLeft />
          </button>
          {/* Title / Episode Info */}
          <div className="episode-info">
            <p>S1:E2 "Kryptonite"</p>
          </div>
        </div>
        <div className="right-actions">
          <span>
            D: {formatTime(currentTime)} / U: {formatTime(duration)}
          </span>
        </div>
      </div>

      {/* Center Controls (large icons) */}
      <div className="center-controls">
        <button onClick={() => handleSkip(-10)} className="skip-btn">
          <FaUndo /> 10
        </button>
        <button className="play-btn" onClick={handlePlayPause}>
          {isPlaying ? <FaPause /> : <FaPlay />}
        </button>
        <button onClick={() => handleSkip(10)} className="skip-btn">
          10 <FaRedo />
        </button>
      </div>

      {/* Bottom Bar */}
      <div className="bottom-bar">
        {/* Progress Bar */}
        <input
          type="range"
          className="progress"
          min={0}
          max={100}
          step={0.1}
          value={progress}
          onChange={handleSeek}
        />
        {/* Time */}
        <div className="time-display">
          {formatTime(currentTime)} / {formatTime(duration)}
        </div>

        {/* Bottom-left: Volume + Settings */}
        <div className="bottom-left">
          <button className="icon-btn">
            <FaVolumeUp />
          </button>
          <button className="icon-btn">
            <FaCog />
          </button>
        </div>

        {/* Bottom-right: Fullscreen */}
        <div className="bottom-right">
          <button className="icon-btn" onClick={handleFullScreen}>
            {isFullscreen ? <FaCompress /> : <FaExpand />}
          </button>
        </div>
      </div>

      {/* Volume Slider (optional) */}
      <div className="volume-control">
        <input
          type="range"
          min={0}
          max={1}
          step={0.01}
          value={volume}
          onChange={handleVolumeChange}
        />
      </div>
    </div>
  );
};

export default VideoPlayer;
