import React, { useState, useEffect, useRef } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import { jwtDecode } from "jwt-decode";
import "./TopMenu.css";

function TopMenu() {
  const [isSearchVisible, setIsSearchVisible] = useState(false);
  const [searchQuery, setSearchQuery] = useState("");
  const [isAdmin, setIsAdmin] = useState(false);
  const searchRef = useRef(null);
  const inputRef = useRef(null);
  const navigate = useNavigate();
  const location = useLocation();

  useEffect(() => {
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
    if (value.trim() === "") {
      navigate("/home");
    } else {
      navigate(`/search/${value}`, { replace: true });
    }
  };

  const storedUser = JSON.parse(localStorage.getItem("user"));
  const avatarImage = storedUser ? storedUser.picture : "/assets/default-avatar.png";

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
    navigate("/login");
  };

  // Function to check if the current route matches a given path
  const isActive = (path) => location.pathname === path;

  // Hide menu items on login-related pages
  const isLoginPage = ["/login", "/register", "/"].includes(location.pathname);

  return (
    <div className="top-menu-wrapper">
      <nav className="top-menu">
        <ul>
          <li className="netflix-logo">
            <a href="/">
              <img src="../assets/LOGO.jpg" alt="Netflix Logo" className="logo-img" />
            </a>
          </li>

          {/* Show these links only if not on a login-related page */}
          {!isLoginPage && (
            <>
              <li className={isActive("/home") ? "active" : ""}>
                <a href="#" onClick={(e) => { e.preventDefault(); navigate("/home"); }}>
                  Movies
                </a>
              </li>
              <li>
                <a href="#" onClick={handleSignOut}>Exit Netflix</a>
              </li>
              {isAdmin && (
                <li className={isActive("/admin") ? "active" : ""}>
                  <a href="/admin">Admin</a>
                </li>
              )}
            </>
          )}
        </ul>
        
        {/* Show search only if not on login pages */}
        {!isLoginPage && (
          <div className="right-section">
            <div className="search-container" ref={searchRef}>
              <img
                src="/assets/searchButton.png"
                alt="Search"
                className="search-icon"
                onClick={() => setIsSearchVisible(true)}
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
          </div>
        )}
      </nav>
    </div>
  );
}

export default TopMenu;
