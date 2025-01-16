<img src="https://github.com/user-attachments/assets/287abe5b-9e8d-4be0-9e79-98ce6ce3edc4" alt="image_with_exercise3" width="300">

# Recommendation System

This project integrates a recommendation system in C++ with a Node.js server and MongoDB database, providing functionalities for user management, authentication, dynamic database operations, and personalized movie suggestions based on viewing preferences. The system operates with the following functionalities:

1. Server-Based Architecture: A robust Node.js server acts as the backbone of the system, handling all API requests and coordinating between the client and the recommendation system.

2. MongoDB Database: Persistent storage is achieved using MongoDB, allowing scalable and efficient data management.

3. Connection to Recommendation System: The server communicates with the recommendation system developed in Task 1 and 2 to fetch personalized movie recommendations.

4. Dynamic Updates: Add, update, and delete users and movies dynamically through API calls.

5. Authentication and Authorization: Users are authenticated through tokens for secure access to the system.

The project follows SOLID principles and ensures scalability and extensibility. It supports a wide range of functionalities including user management, authentication, dynamic database operations, and personalized movie recommendations, making it a comprehensive platform for managing and exploring user-specific movie content.


The server exposes the following key endpoints:
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


## Cd to RecommendationSystem
```bash
cd RecommendationSystem
```

## Build the Docker Image
To build the Docker image, run the following command:
```bash
docker compose build
```

## Running the Container

### Run the server
To create and run the container for the first time, execute:
```bash
docker compose up server
```

### Run the client
To start the container after it has already been created, use:
```bash
docker compose run --rm client
```

## Running Tests
To run the tests, use the following command:
```bash
docker compose run --rm test
```
This command will run the tests in a disposable container, which will be removed after the tests complete.

# Run Example:
![image](https://github.com/user-attachments/assets/74dc3698-b499-4e5d-9c72-a5450c970b94)

