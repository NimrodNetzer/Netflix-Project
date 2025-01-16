<img src="https://github.com/user-attachments/assets/287abe5b-9e8d-4be0-9e79-98ce6ce3edc4" alt="image_with_exercise3" width="300">
# Recommendation System

This project implements a recommendation system in C++ for suggesting movies to users based on their viewing preferences. The system operates with the following functionalities:

1. Add Users and Movies: Assign movies to specific users, allowing dynamic updates to the database.
2. Generate Recommendations: Suggest up to 10 movies for a user based on the viewing history of users with similar preferences.
3. Persistent Data Handling: Ensures that data persists across program sessions by saving and loading from files.
4. Command-Line Interface: Supports commands for adding data, generating recommendations, and displaying help.

The project follows SOLID principles and is designed for scalability, enabling seamless updates and extensions to the codebase. The recommendation algorithm is based on calculating the similarity of users and their movie-watching patterns, prioritizing movies watched by users with higher similarity scores.


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

