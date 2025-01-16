<img src="https://github.com/user-attachments/assets/07f90e3a-d4d7-473c-920f-6d83e9693cc5" alt="Netflix-BIU Logo" width="300">

# Recommendation System

This project implements a recommendation system in C++ for suggesting movies to users based on their viewing preferences. The system operates with the following functionalities:

# Features
1. Add Users and Movies: Assign movies to specific users, allowing dynamic updates to the database.
2. Generate Recommendations: Suggest up to 10 movies for a user based on the viewing history of users with similar preferences.
3. Persistent Data Handling: Ensures that data persists across program sessions by saving and loading from files.
4. Command-Line Interface: Supports commands for adding data, generating recommendations, and displaying help.
5. Server-Based Architecture: The system is centered around a C++ server that handles core functionalities, including managing user data, movies, and generating recommendations.
6. Python Client Integration: Clients connect to the server using a Python-based client, facilitating communication and interactions with the recommendation system.

The project follows SOLID principles and is designed for scalability, enabling seamless updates and extensions to the codebase. The recommendation algorithm is based on calculating the similarity of users and their movie-watching patterns, prioritizing movies watched by users with higher similarity scores.


## How to run
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
To run the server execute:
```bash
docker compose up server
```

### Run the client
To connect to the server with the python client:
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
![image](https://github.com/user-attachments/assets/d06d622b-0306-45e4-ba21-6ffa834802e4)


