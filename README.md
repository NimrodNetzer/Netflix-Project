<div align="center">
  <img src="https://github.com/user-attachments/assets/287abe5b-9e8d-4be0-9e79-98ce6ce3edc4" alt="image_with_exercise3" width="500">
</div>
<br>

# Recommendation System

This project integrates a recommendation system in C++ with a Node.js server and MongoDB database, providing functionalities for user management, authentication, dynamic database operations, and personalized movie suggestions based on viewing preferences. <br>
The system operates with the following functionalities:

1. Server-Based Architecture: A robust Node.js server acts as the backbone of the system, handling all API requests and coordinating between the client and the recommendation system.

2. MongoDB Database: Persistent storage is achieved using MongoDB, allowing scalable and efficient data management.

3. Connection to Recommendation System: The server communicates with the recommendation system developed in Task 1 and 2 to fetch personalized movie recommendations.

4. Dynamic Updates: Add, update, and delete users and movies dynamically through API calls.

5. Authentication and Authorization: Users are authenticated through tokens for secure access to the system.

The project follows SOLID principles and ensures scalability and extensibility.  <br>
It supports a wide range of functionalities including user management, authentication, dynamic database operations, and personalized movie recommendations, making it a comprehensive platform for managing and exploring user-specific movie content.\
<br>

**The server exposes the following key endpoints:**
### User Management

- **`POST /api/users`**: Create a new user by submitting their details in JSON format.
- **`GET /api/users/:id`**: Retrieve specific user details using their unique ID.

### Movie Management

- **`GET /api/movies`**: Retrieve a list of all movies, optionally filtered by categories or user preferences.
- **`POST /api/movies`**: Add a new movie by submitting its details in JSON format.
- **`GET /api/movies/:id/recommend`**: Fetch movie recommendations for a specific user based on their unique ID and viewing preferences.

### Authentication

- **`POST /api/tokens`**: Authenticate a user by submitting their credentials and receive an access token for secure API interaction.

### Categories Management

- **`GET /api/categories`**: Retrieve all available movie categories.
- **`POST /api/categories`**: Add 




## How to run
```bash
cd MainApi
```

## Build and Run the Docker Image
To build the Docker image, run the following command:
```bash
docker compose up --build -d
```
The recommendation server will run on port 8080, the nodejs server will be on port 3000 (the port can be modified in the docker-compose.yml).

# Run Example:
![image](https://github.com/user-attachments/assets/d06d622b-0306-45e4-ba21-6ffa834802e4)

# Run the test script
"C:\Users\orlib\AppData\Local\Programs\Python\Python313\python.exe" test.py


