import React, { useState, useEffect, useRef } from 'react';
import './TopMenu.css';
import HelperTopMenu from './HelperTopMenu';

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
            src="/assets/searchButton.png"
            alt="Search"
            className="search-icon"
            onClick={handleSearchClick}
          />
          <input
            type="text"
            placeholder="Search"
            className={`search-input ${isSearchVisible ? 'visible' : ''}`}
          />
        </div>
        <HelperTopMenu />
      </div>
    </nav>
  );
}

export default TopMenu;
