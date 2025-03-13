import React, { useState } from 'react';
import './Hero.css';
import logo from '../../assets/LOGO.jpg'; // Assuming the logo is in the assets folder
import { useNavigate } from 'react-router-dom';

function Hero() {
    const navigate = useNavigate();
    const [email, setEmail] = useState(''); // State to store the email input

    const handleGetStarted = (e) => {
        e.preventDefault(); // Prevent page refresh if validation passes
        navigate('/signup', { state: { email } }); // Pass email to Signup page
    };

    return (
        <div className="hero">
            {/* Add the logo */}
            <img src={logo} alt="Logo" className="logo" />

            {/* Add Sign In button */}
            <button onClick={() => navigate('/login')} className="sign-in-button">
                Sign In
            </button>

            <div className="hero-content">
                <h1 className="hero-title">
                    Unlimited movies, <br /> TV shows, and more
                </h1>
                <h2>Watch anywhere. Cancel anytime.</h2>
                <p>Ready to watch? Enter your email to create or restart your membership.</p>
                <form onSubmit={handleGetStarted} className="input-container">
                    <input
                        type="email"
                        id="email"
                        placeholder="Email address"
                        value={email}
                        onChange={(e) => setEmail(e.target.value)}
                        required // Make the field required
                        pattern="^[^\s@]+@[^\s@]+\.[^\s@]+$" // Ensure valid email format
                        
                    />
                    <button type="submit">
                        Get Started &gt;
                    </button>
                </form>
            </div>
        </div>
    );
}

export default Hero;
