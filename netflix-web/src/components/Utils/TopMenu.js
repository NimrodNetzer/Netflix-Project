import React, { useState, useEffect, useRef } from 'react';
import { useNavigate, useLocation } from 'react-router-dom';
import './TopMenu.css';
import HelperTopMenu from './HelperTopMenu';

function TopMenu() {
  const [isSearchVisible, setIsSearchVisible] = useState(false);
  const [searchQuery, setSearchQuery] = useState('');
  const searchRef = useRef(null);
  const inputRef = useRef(null);
  const navigate = useNavigate();
  const location = useLocation();

  // Show search input and keep focus
  const handleSearchClick = () => {
    setIsSearchVisible(true);
    setTimeout(() => {
      inputRef.current?.focus();
    }, 100);
  };

  // Handle search input change and navigate
  const handleSearchChange = (event) => {
    const value = event.target.value;

    if (value !== searchQuery) {
      setSearchQuery(value);
    }

    if (value.trim() === '') {
      navigate('/home'); // Stay in Home when search is empty
    } else {
      navigate(`/search/${value}`, { replace: true });
    }
  };

  // Close search input only when clicking outside
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

  // ✅ Keep search open when switching pages (even when coming back from Home)
  useEffect(() => {
    if (location.pathname.startsWith('/search')) {
      setIsSearchVisible(true);
      setSearchQuery(decodeURIComponent(location.pathname.replace('/search/', '')));
    } else if (location.pathname === '/home') {
      setTimeout(() => setIsSearchVisible(true), 100); // Ensures search box stays open after navigating home
    }
  }, [location.pathname]);

  return (
    <nav className="top-menu">
      <ul>
        <li className="netflix-logo">
          <a href="/">
            <img src="../assets/LOGO.jpg" alt="Netflix Logo" className="logo-img" />
          </a>
        </li>
        <li><a href="/home">Home</a></li>
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
          {isSearchVisible && (
            <input
              type="text"
              placeholder="Search"
              className="search-input visible"
              value={searchQuery}
              onChange={handleSearchChange}
              ref={inputRef}
              autoFocus
            />
          )}
        </div>
        <HelperTopMenu />
      </div>
    </nav>
  );
}

export default TopMenu;