import './Login.css'; // Import the CSS file for styling
import React, { useState } from 'react';

const Login = () => {
  const [email, setEmail] = useState(''); // State for username
  const [password, setPassword] = useState(''); // State for password
  const [errorMessage, setErrorMessage] = useState(''); // State for error messages
  const [isLoading, setIsLoading] = useState(false); // State for loading indicator

  const handleLogin = async (event) => {
    event.preventDefault(); // Prevent page refresh
    setIsLoading(true); // Start loading

    // Client-side validation
    if (!email) {
      setErrorMessage('Email is required');
      setIsLoading(false); // Stop loading
      return;
    }
    if (password.length < 8) {
      setErrorMessage('Password must be at least 8 characters long');
      setIsLoading(false); // Stop loading
      return;
    }

    try {
      const response = await fetch('http://localhost:3000/api/tokens', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ email, password }),
      });

      const data = await response.json();

      if (response.ok) {
        localStorage.setItem('jwt', data.token); // Save JWT token locally
        alert('Login successful!');
        // Redirect to the main page
      } else {
        setErrorMessage('Invalid username or password');
      }
    } catch (error) {
      setErrorMessage('An error occurred. Please try again.');
    } finally {
      setIsLoading(false); // Stop loading
    }
  };

  return (
    <div className="login-container">
      <h2>Login</h2>
      <form onSubmit={handleLogin}>
        {/* Username field */}
        <div className="form-group">
          <label htmlFor="email">Email:</label>
          <input
            type="text"
            id="email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            placeholder="Enter your email"
            required
          />
        </div>

        {/* Password field */}
        <div className="form-group">
          <label htmlFor="password">Password:</label>
          <input
            type="password"
            id="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            placeholder="Enter your password"
            required
          />
        </div>

        {/* Error message */}
        {errorMessage && <p className="error-message">{errorMessage}</p>}

        {/* Login button */}
        <button type="submit" disabled={isLoading}>
          {isLoading ? 'Loading...' : 'Login'}
        </button>
      </form>
    </div>
  );
};

export default Login;