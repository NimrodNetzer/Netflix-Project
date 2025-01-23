import React, { useState, useEffect, useRef } from 'react';
import './TopMenu.css';

function TopMenu() {
  const [isSearchVisible, setIsSearchVisible] = useState(false);
  const searchRef = useRef(null);

  const handleSearchClick = () => {
    setIsSearchVisible(!isSearchVisible);
  };

  const handleClickOutside = (event) => {
    if (searchRef.current && !searchRef.current.contains(event.target)) {
      setIsSearchVisible(false);
    }
  };

  useEffect(() => {
    document.addEventListener('mousedown', handleClickOutside);
    return () => {
      document.removeEventListener('mousedown', handleClickOutside);
    };
  }, []);

  return (
    <nav className="top-menu">
      <ul>
        <li className="netflix-logo">
          <a href="/">
            <img src="../assets/LOGO.jpg" alt="Netflix Logo" className="logo-img" />
          </a>
        </li>
        <li><a href="/">Home</a></li>
        <li><a href="/">Movies</a></li>
        <li><a href="/">New & Popular</a></li>
        <li><a href="/">My List</a></li>
      </ul>
      <div className="right-section">
        <div className="search-container" ref={searchRef}>
          <img
            src="/assets/searchButton.png" /* Path to your image */
            alt="Search"
            className="search-icon"
            onClick={handleSearchClick}
          />
          {isSearchVisible && (
            <input
              type="text"
              placeholder="Search"
              className="search-input"
            />
          )}
        </div>
        <button className="profile-button">
          <img src="/assets/p.png" alt="Profile" className="search-icon" />
        </button>
      </div>
    </nav>
  );
}

export default TopMenu;
