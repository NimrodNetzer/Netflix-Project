import React, { useState, useEffect, useRef } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import { jwtDecode } from "jwt-decode";
import "./TopMenu.css";

// Import default avatar
import defaultAvatar from "../../assets/default-avatar.png";

function TopMenu() {
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
    setTimeout(() => inputRef.current?.focus(), 100); // Ensure input gains focus
  };

  // Closes search bar when clicking outside
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

  // Function to check if the current route matches a given path
  const isActive = (path) => location.pathname === path;
  const isLoginPage = ["/login", "/register", "/"].includes(location.pathname);
  const isLoggedIn = !!localStorage.getItem("jwt"); // Check if user is logged in
  const avatarImage = user?.picture || defaultAvatar;

  // Function to navigate only if logged in
  const handleNavigateToHome = (e) => {
    e.preventDefault();
    if (isLoggedIn) {
      navigate("/home");
    } else {
      alert("You must be logged in to access Movies.");
      navigate("/login");
    }
  };

  return (
    <div className="top-menu-wrapper">
      <nav className="top-menu">
        <ul>
          {/* Netflix Logo Clickable - Redirects to Home if logged in */}
          <li className="netflix-logo">
            <a href="#" onClick={handleNavigateToHome}>
              <img src="../assets/LOGO.jpg" alt="Netflix Logo" className="logo-img" />
            </a>
          </li>

          {!isLoginPage && (
            <>
              <li className={isActive("/home") ? "active" : ""}>
                <a href="#" onClick={handleNavigateToHome}>Movies</a>
              </li>
              <li><a href="#" onClick={handleSignOut}>Exit Netflix</a></li>
              {isAdmin && <li className={isActive("/admin") ? "active" : ""}><a href="/admin">Admin</a></li>}
            </>
          )}
        </ul>

        {/* Right Section: Search & Avatar */}
        {!isLoginPage && (
          <div className="right-section">
            {/* Search Box */}
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

            {/* User Avatar */}
            <div className="user-avatar-container">
              <img src={avatarImage} alt="User Avatar" className="user-avatar" />
            </div>
          </div>
        )}
      </nav>
    </div>
  );
}

export default TopMenu;
