import React, { useState, useEffect } from 'react';
import './CreateMovieForm.css';

const CreateMovieForm = ({ onSubmit, onCancel }) => {
  // Basic movie fields
  const [name, setName] = useState('');
  const [description, setDescription] = useState('');
  const [age, setAge] = useState('');
  const [hours, setHours] = useState('');
  const [minutes, setMinutes] = useState('');
  const [releaseDate, setReleaseDate] = useState('');
  const [quality, setQuality] = useState('');
  // Additional properties fields
  const [genre, setGenre] = useState('');
  const [language, setLanguage] = useState('');
  const [selectedCategories, setSelectedCategories] = useState([]);
  const [categories, setCategories] = useState([]);
  const [cast, setCast] = useState([{ name: '', role: '' }]);
  const [picture, setPicture] = useState(null);
  const [video, setVideo] = useState(null);
  const [author, setAuthor] = useState('');
  const [loading, setLoading] = useState(false);
  const [successMessage, setSuccessMessage] = useState('');

  // Prevent scrolling when modal is open
  useEffect(() => {
    document.body.style.overflow = 'hidden';
    return () => {
      document.body.style.overflow = 'auto';
    };
  }, []);

  // Fetch categories for selection from backend
  useEffect(() => {
    const fetchCategories = async () => {
      try {
        const token = localStorage.getItem('jwt');
        const response = await fetch('http://localhost:4000/api/categories', {
          method: 'GET',
          headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${token}`
          },
        });

        if (!response.ok) {
          throw new Error(`Failed to fetch categories (status: ${response.status})`);
        }

        const data = await response.json();
        setCategories(data);
      } catch (error) {
        console.error('Error fetching categories:', error);
      }
    };

    fetchCategories();
  }, []);

  // Handle time input (allow only numbers & restrict max values)
  const handleHoursChange = (e) => {
    const value = e.target.value.replace(/\D/, '');
    setHours(value ? Math.min(parseInt(value, 10), 3) : '');
  };

  const handleMinutesChange = (e) => {
    const value = e.target.value.replace(/\D/, '');
    setMinutes(value ? Math.min(parseInt(value, 10), 59) : '');
  };

  // Handle cast input changes
  const handleCastChange = (index, field, value) => {
    const updatedCast = [...cast];
    updatedCast[index][field] = value;
    setCast(updatedCast);
  };

  const addCastMember = () => {
    setCast([...cast, { name: '', role: '' }]);
  };

  const removeCastMember = (index) => {
    setCast(cast.filter((_, i) => i !== index));
  };

  // Handle category checkbox selection
  const handleCategorySelection = (id) => {
    if (selectedCategories.includes(id)) {
      setSelectedCategories(selectedCategories.filter(catId => catId !== id));
    } else {
      setSelectedCategories([...selectedCategories, id]);
    }
  };

  const handleSubmit = async (e) => {
    e.preventDefault();

    // Validate age between 0 and 18
    const ageValue = parseInt(age, 10);
    if (isNaN(ageValue) || ageValue < 0 || ageValue > 18) {
      alert("Invalid age! Age must be between 0 and 18.");
      return;
    }

    // Format time as "Xh Ym"
    const formattedTime = `${hours || 0}h ${minutes || 0}m`;

    // Validate cast (at least one member, and each has a name)
    if (!Array.isArray(cast) || cast.length === 0) {
      alert("Invalid cast! At least one cast member is required.");
      return;
    }

    for (let i = 0; i < cast.length; i++) {
      if (!cast[i].name.trim()) {
        alert(`Invalid cast member at index ${i}: Name is required.`);
        return;
      }
    }

    // Build movie object
    const movieData = {
      name,
      description,
      age: ageValue,
      time: formattedTime,
      releaseDate,
      quality,
      categories: selectedCategories,
      cast, // Array of cast objects
      properties: {
        genre,
        language
      },
      author: "my author"
    };

    const formData = new FormData();
    formData.append("data", JSON.stringify(movieData));
    if (picture) formData.append("image", picture);
    if (video) formData.append("video", video);

    setLoading(true);
    setSuccessMessage("");

    try {
      const token = localStorage.getItem("jwt");
      const response = await fetch("http://localhost:4000/api/movies", {
        method: "POST",
        headers: {
          "Authorization": `Bearer ${token}`,
        },
        body: formData,
      });

      if (response.status === 201) {
        setSuccessMessage("Movie Added Successfully!");
        setTimeout(() => {
          onSubmit();
        }, 2000);
      } else {
        const errorResponse = await response.json();
        console.error("Error:", errorResponse);
        alert(`Failed to create movie: ${errorResponse.message}`);
      }
    } catch (error) {
      console.error("Error creating movie:", error);
      alert("Failed to create movie. Please try again.");
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="modal-overlay">
      <div className="modal-content">
        <button className="close-button" onClick={onCancel}>✕</button>
        <h2>Create Movie</h2>
        <form onSubmit={handleSubmit} className="movie-form">
          {/* Row 1: Movie Name (30%) & Description (70%) */}
          <div className="form-row movie-info-row">
            <div className="form-group movie-name">
              <label className="form-label">Movie Name:</label>
              <input
                type="text"
                className="form-input"
                value={name}
                onChange={(e) => setName(e.target.value)}
                required
              />
            </div>
            <div className="form-group movie-description">
              <label className="form-label">Description:</label>
              <textarea
                className="form-input"
                value={description}
                onChange={(e) => setDescription(e.target.value)}
                required
              />
            </div>
          </div>

          {/* Row 2: Age Rating & Duration */}
          <div className="form-row two-column-row">
            <div className="form-group">
              <label className="form-label">Age Rating:</label>
              <input
                type="number"
                className="form-input"
                value={age}
                onChange={(e) => setAge(e.target.value)}
                required
              />
            </div>
            <div className="form-group">
              <label className="form-label">Duration:</label>
              <div className="time-input-container">
                <input
                  type="text"
                  className="time-input"
                  placeholder="Hours"
                  value={hours}
                  onChange={handleHoursChange}
                  maxLength="1"
                />
                <span>h</span>
                <input
                  type="text"
                  className="time-input"
                  placeholder="Minutes"
                  value={minutes}
                  onChange={handleMinutesChange}
                  maxLength="2"
                />
                <span>m</span>
              </div>
            </div>
          </div>

          {/* Row 3: Release Date & Quality */}
          <div className="form-row two-column-row">
            <div className="form-group">
              <label className="form-label">Release Date:</label>
              <input
                type="date"
                className="form-input"
                value={releaseDate}
                onChange={(e) => setReleaseDate(e.target.value)}
                required
              />
            </div>
            <div className="form-group">
              <label className="form-label">Quality:</label>
              <select
                className="form-input"
                value={quality}
                onChange={(e) => setQuality(e.target.value)}
                required
              >
                <option value="">Select Quality</option>
                <option value="HD">HD</option>
                <option value="SD">SD</option>
                <option value="4K">4K</option>
              </select>
            </div>
          </div>

          {/* Row 4: Genre & Language */}
          <div className="form-row two-column-row">
            <div className="form-group">
              <label className="form-label">Genre:</label>
              <select
                className="form-input"
                value={genre}
                onChange={(e) => setGenre(e.target.value)}
                required
              >
                <option value="">Select Genre</option>
                <option value="Action">Action</option>
                <option value="Drama">Drama</option>
                <option value="Comedy">Comedy</option>
                <option value="Horror">Horror</option>
              </select>
            </div>
            <div className="form-group">
              <label className="form-label">Language:</label>
              <select
                className="form-input"
                value={language}
                onChange={(e) => setLanguage(e.target.value)}
                required
              >
                <option value="">Select Language</option>
                <option value="English">English</option>
                <option value="Spanish">Spanish</option>
                <option value="French">French</option>
                <option value="German">German</option>
              </select>
            </div>
          </div>

          {/* Row 5: Categories (Full Width Grid) */}
          <div className="form-row full-width">
            <div className="form-group">
              <label className="form-label">Categories:</label>
              <div className="categories-container">
                {categories.map(category => (
                  <label key={category._id}>
                    <input
                      type="checkbox"
                      checked={selectedCategories.includes(category._id)}
                      onChange={() => handleCategorySelection(category._id)}
                    />
                    {category.name}
                  </label>
                ))}
              </div>
            </div>
          </div>

          {/* Row 6: Cast (Full Width) */}
          <div className="form-row full-width">
            <div className="form-group">
              <label className="form-label">Cast:</label>
              {cast.map((member, index) => (
                <div key={index} className="cast-member">
                  <input
                    type="text"
                    className="form-input"
                    placeholder="Actor Name"
                    value={member.name}
                    onChange={(e) => handleCastChange(index, 'name', e.target.value)}
                    required
                  />
                  <input
                    type="text"
                    className="form-input"
                    placeholder="Role"
                    value={member.role}
                    onChange={(e) => handleCastChange(index, 'role', e.target.value)}
                    required
                  />
                  <button
                    type="button"
                    className="remove-cast-button"
                    onClick={() => removeCastMember(index)}
                  >
                    🗑
                  </button>
                </div>
              ))}
              <button type="button" className="add-cast-button" onClick={addCastMember}>
                + Add Cast Member
              </button>
            </div>
          </div>

          {/* Row 7: Picture & Video */}
          <div className="form-row two-column-row">
            <div className="form-group">
              <label className="form-label">Picture:</label>
              <input
                type="file"
                className="form-input"
                accept="image/*"
                onChange={(e) => setPicture(e.target.files[0])}
              />
            </div>
            <div className="form-group">
              <label className="form-label">Video:</label>
              <input
                type="file"
                className="form-input"
                accept="video/*"
                onChange={(e) => setVideo(e.target.files[0])}
              />
            </div>
          </div>

          {successMessage && <div className="success-message">{successMessage}</div>}

          <button type="submit" className="submit-button" disabled={loading}>
            {loading ? 'Creating...' : 'Create'}
          </button>
        </form>
      </div>
    </div>
  );
};

export default CreateMovieForm;
