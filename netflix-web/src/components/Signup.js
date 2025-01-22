import './Signup.css'; // Import the CSS file for styling
import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';


const Signup = () => {
  const [email, setEmail] = useState(''); // State for email
  const [password, setPassword] = useState(''); // State for password
  const [nickname, setNickname] = useState(''); // State for nickname
  const [picture, setPicture] = useState(null); // State for profile picture
  const [errorMessage, setErrorMessage] = useState(''); // State for error messages
  const [isLoading, setIsLoading] = useState(false); // State for loading indicator

  const navigate = useNavigate(); // Initialize useNavigate


  const handleSignup = async (event) => {
    event.preventDefault(); // Prevent page refresh
    setIsLoading(true); // Start loading

    // Client-side validation
    if (!email) {
      setErrorMessage('Email is required.');
      setIsLoading(false);
      return;
    }
    if (!password) {
      setErrorMessage('Password is required.');
      setIsLoading(false);
      return;
    }
    if (!nickname) {
      setErrorMessage('Nickname is required.');
      setIsLoading(false);
      return;
    }

    /*const emailRegex = /^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$/;
    if (!emailRegex.test(email)) {
      setErrorMessage('Invalid email format.');
      setIsLoading(false);
      return;
    }
*/
    const passwordRegex = /^[\\x20-\\x7E]{8,}$/;
    if (!passwordRegex.test(password)) {
      setErrorMessage(
        'Password must be at least 8 characters long and contain only English letters, numbers, or special characters.'
      );
      setIsLoading(false);
      return;
    }

    try {
      const formData = new FormData();
      formData.append('email', email);
      formData.append('password', password);
      formData.append('nickname', nickname);
      if (picture) {
        formData.append('picture', picture);
      }

      const response = await fetch('http://localhost:4000/api/users', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
          },
        body: JSON.stringify({ email, password, nickname, picture }),
      });

      if (response.ok) {
        alert('Signup successful! You can now log in.');
        // Redirect to the login page or another appropriate action
      } else {
        const data = await response.json();
        setErrorMessage(data.errors || 'Signup failed.' + data);
      }
    } catch (error) {
      setErrorMessage('An error occurred during signup.');
    } finally {
      setIsLoading(false); // Stop loading
    }
  };

  return (
    <div className="signup-container">
      <h2>Sign Up</h2>
      <form onSubmit={handleSignup}>
        {/* Email field */}
        <div className="form-group">
          <label htmlFor="email">Email:</label>
          <input
            type="email"
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

        {/* Nickname field */}
        <div className="form-group">
          <label htmlFor="nickname">Nickname:</label>
          <input
            type="text"
            id="nickname"
            value={nickname}
            onChange={(e) => setNickname(e.target.value)}
            placeholder="Enter your nickname"
            required
          />
        </div>

        {/* Picture field */}
        <div className="form-group">
          <label htmlFor="picture">Profile Picture:</label>
          <input
            type="file"
            id="picture"
            onChange={(e) => setPicture(e.target.files[0])}
          />
        </div>

        {/* Error message */}
        {errorMessage && <p className="error-message">{errorMessage}</p>}

        {/* Signup button */}
        <button type="submit" disabled={isLoading}>
          {isLoading ? 'Signing up...' : 'Signup'}
        </button>

        <div className="additional-options">
        <a onClick={() => navigate('/')}>Already have an account? Sign in</a>
        </div>
      </form>
    </div>

    
  );
};

export default Signup;
