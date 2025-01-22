import React from 'react';
import './Hero.css';

function Hero() {
    return (
        <div className="hero">
            <div className="hero-content">
                <h1 className="hero-title">
                    Unlimited movies, <br /> TV shows, and more.
                </h1>
                <h2>Watch anywhere. Cancel anytime.</h2>
                <p>Ready to watch? Enter your email to create or restart your membership.</p>
                <div className="input-container">
                    <input type="email" placeholder="Email address" />
                    <button>Get Started &gt;</button>
                </div>
            </div>
        </div>
    );
}

export default Hero;
