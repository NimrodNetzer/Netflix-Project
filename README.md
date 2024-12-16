# Netflix-BIU
# Recommendation System

This project implements a recommendation system in C++ for suggesting movies to users based on their viewing preferences. The system operates with the following functionalities:

1. Add Users and Movies: Assign movies to specific users, allowing dynamic updates to the database.
2. Generate Recommendations: Suggest up to 10 movies for a user based on the viewing history of users with similar preferences.
3. Persistent Data Handling: Ensures that data persists across program sessions by saving and loading from files.
4. Command-Line Interface: Supports commands for adding data, generating recommendations, and displaying help.

The project follows SOLID principles and is designed for scalability, enabling seamless updates and extensions to the codebase. The recommendation algorithm is based on calculating the similarity of users and their movie-watching patterns, prioritizing movies watched by users with higher similarity scores.


## Build the Docker Image
To build the Docker image, run the following command:
```bash
docker build -t recommendation-build .
```

## Running the Container

### First Run
To create and run the container for the first time, execute:
```bash
docker run -it --init --name recommendation-system recommendation-build
```

### Subsequent Runs
To start the container after it has already been created, use:
```bash
docker start -ai recommendation-system
```

## Running Tests
To run the tests, use the following command:
```bash
docker run --rm recommendation-build ./test/build/RecommendationSystem_Tests
```
This command will run the tests in a disposable container, which will be removed after the tests complete.

# Run Example:
![image](https://github.com/user-attachments/assets/74dc3698-b499-4e5d-9c72-a5450c970b94)

