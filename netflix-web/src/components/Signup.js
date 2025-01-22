import './Signup.css'; // Import the CSS file for styling
import React, { useState, useEffect } from 'react';
import { useNavigate, useLocation } from 'react-router-dom';
import profile1 from '../assets/profile1.webp'; // Import predefined images
import profile2 from '../assets/profile2.webp';
import profile3 from '../assets/profile3.webp';

const Signup = () => {
    const location = useLocation();
    const navigate = useNavigate();
    const [selectedPicture, setSelectedPicture] = useState(null); // State for selected profile picture

    const [email, setEmail] = useState(location.state?.email || ''); // Initialize email with passed state or empty string
    const [password, setPassword] = useState('');
    const [nickname, setNickname] = useState('');
    const [picture, setPicture] = useState(null);
    const [errorMessage, setErrorMessage] = useState('');
    const [isLoading, setIsLoading] = useState(false);

    const handleSignup = async (event) => {
        event.preventDefault();
        setIsLoading(true);

        
        try {
            const response = await fetch('http://localhost:4000/api/users', {
                method: 'POST',
                headers: {
                  'Content-Type': 'application/json',
                },
                body: JSON.stringify({ email, password, nickname , picture }),
              });

            if (response.ok) {
                alert('Signup successful! You can now log in.');
                navigate('/Login');
            } else {
                const data = await response.json();
                setErrorMessage(data.errors || 'Signup failed.');
            }
        } catch (error) {
            setErrorMessage('An error occurred during signup.');
        } finally {
            setIsLoading(false);
        }
    };

    return (
      <div className="signup-container">
          <h2>Sign Up</h2>
          <form onSubmit={handleSignup}>
              {/* Email Field */}
              <div className="form-group">
                  <label htmlFor="email">Email:</label>
                  <input
                      type="email"
                      id="email"
                      value={email}
                      onChange={(e) => setEmail(e.target.value)}
                      placeholder="Enter your email"
                      required
                      pattern="^[^\s@]+@[^\s@]+\.[^\s@]+$"
                      title="Please enter a valid email address in the format: example@domain.com"
                  />
              </div>

              {/* Password Field */}
              <div className="form-group">
                  <label htmlFor="password">Password:</label>
                  <input
                      type="password"
                      id="password"
                      value={password}
                      onChange={(e) => setPassword(e.target.value)}
                      placeholder="Enter your password"
                      required
                      pattern="^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$"
                      title="Password must be at least 8 characters long, contain at least one letter and one number, and use only English letters and numbers."
                  />
              </div>

              {/* Nickname Field */}
              <div className="form-group">
                  <label htmlFor="nickname">Nickname:</label>
                  <input
                      type="text"
                      id="nickname"
                      value={nickname}
                      onChange={(e) => setNickname(e.target.value)}
                      placeholder="Enter your nickname"
                      required
                      pattern="^[A-Za-z\d_]{3,}$"
                      title="Nickname must be at least 3 characters long and can include letters, numbers, and underscores only."
                  />
              </div>

              {/* Profile Picture Selection */}
              <div className="form-group">
                    <label>Choose a Profile Picture:</label>
                    <div className="profile-picture-options">
                        {/* Option 1 */}
                        <img
                            src={profile1}
                            alt="Profile 1"
                            className={`profile-thumbnail ${selectedPicture === 'profile1' ? 'selected' : ''}`}
                            onClick={() => setSelectedPicture('profile1')}
                        />

                        {/* Option 2 */}
                        <img
                            src={profile2}
                            alt="Profile 2"
                            className={`profile-thumbnail ${selectedPicture === 'profile2' ? 'selected' : ''}`}
                            onClick={() => setSelectedPicture('profile2')}
                        />

                        {/* Option 3 */}
                        <img
                            src={profile3}
                            alt="Profile 3"
                            className={`profile-thumbnail ${selectedPicture === 'profile3' ? 'selected' : ''}`}
                            onClick={() => setSelectedPicture('profile3')}
                        />
                    </div>
                </div>

              {/* Error Message */}
              {errorMessage && <p className="error-message">{errorMessage}</p>}

              {/* Signup Button */}
              <button type="submit" disabled={isLoading}>
                  {isLoading ? 'Signing up...' : 'Signup'}
              </button>

              {/* Additional Options */}
              <div className="additional-options">
                  <a onClick={() => navigate('/login')}>Already have an account? Sign in</a>
              </div>
          </form>
      </div>
  );
};

export default Signup;