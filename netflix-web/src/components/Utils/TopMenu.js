import React, { useState, useEffect, useRef } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import { jwtDecode } from "jwt-decode";
import "./TopMenu.css";
import defaultAvatar from "../../assets/profile2.webp";

function TopMenu({ darkMode, setDarkMode }) {
  const [isSearchVisible, setIsSearchVisible] = useState(false);
  const [searchQuery, setSearchQuery] = useState("");
  const [isAdmin, setIsAdmin] = useState(false);
  const [user, setUser] = useState(null);
  const searchRef = useRef(null);
  const inputRef = useRef(null);
  const navigate = useNavigate();
  const location = useLocation();

  useEffect(() => {
    const storedUser = JSON.parse(localStorage.getItem("user"));
    if (storedUser) {
      setUser(storedUser);
    }

    const token = localStorage.getItem("jwt");
    if (token) {
      try {
        const decodedToken = jwtDecode(token);
        setIsAdmin(decodedToken.admin === true);
      } catch (error) {
        console.error("Invalid token:", error);
      }
    }
  }, []);

  const handleSearchChange = (event) => {
    const value = event.target.value;
    setSearchQuery(value);
    navigate(value.trim() ? `/search/${value}` : "/home");
  };

  const handleSearchClick = () => {
    setIsSearchVisible(true);
    setTimeout(() => inputRef.current?.focus(), 100);
  };

  useEffect(() => {
    const handleClickOutside = (event) => {
      if (searchRef.current && !searchRef.current.contains(event.target)) {
        setIsSearchVisible(false);
      }
    };
    document.addEventListener("mousedown", handleClickOutside);
    return () => document.removeEventListener("mousedown", handleClickOutside);
  }, []);

  const handleSignOut = (e) => {
    e.preventDefault();
    localStorage.removeItem("jwt");
    localStorage.removeItem("user");
    navigate("/login");
  };

  const handleToggleDarkMode = (event) => {
    event.stopPropagation();
    setDarkMode((prevMode) => {
      const newMode = !prevMode;
      localStorage.setItem("theme", newMode ? "dark" : "light");
      return newMode;
    });
  };

  const isActive = (path) => location.pathname === path;
  const isLoginPage = ["/login", "/register", "/"].includes(location.pathname);
  const isLoggedIn = !!localStorage.getItem("jwt");
  const avatarImage = user?.picture || defaultAvatar;

  return (
    <div className="top-menu-wrapper">
      <nav className="top-menu">
        <ul>
          <li className="netflix-logo">
            <a href="#" onClick={(e) => { e.preventDefault(); isLoggedIn ? navigate("/home") : navigate("/login"); }}>
              <img src="../assets/LOGO.jpg" alt="Netflix Logo" className="logo-img" />
            </a>
          </li>

          {!isLoginPage && (
            <>
              <li className={isActive("/home") ? "active" : ""}>
                <a href="#" onClick={(e) => { e.preventDefault(); navigate("/home"); }}>Movies</a>
              </li>
              <li><a href="#" onClick={handleSignOut}>Exit Netflix</a></li>
              {isAdmin && <li className={isActive("/admin") ? "active" : ""}><a href="/admin">Admin</a></li>}
            </>
          )}
        </ul>

        <div className="right-section">
          {isLoggedIn && (
            <div className="search-container" ref={searchRef}>
              <img src="/assets/searchButton.png" alt="Search" className="search-icon" onClick={handleSearchClick} />
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
          )}

          <div className="dark-mode-toggle">
            <span className="toggle-label">☀</span>
            <label className="switch">
              <input type="checkbox" checked={darkMode} onChange={handleToggleDarkMode} />
              <span className="slider"></span>
            </label>
            <span className="toggle-label">🌙</span>
          </div>

          {isLoggedIn && (
            <div className="user-avatar-container">
              <img src={avatarImage} alt="User Avatar" className="user-avatar" />
            </div>
          )}
        </div>
      </nav>
    </div>
  );
}

export default TopMenu;