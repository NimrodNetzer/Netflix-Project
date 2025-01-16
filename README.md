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


# Project Design Overview

This section outlines how the project design addresses changes in requirements while adhering to best practices such as scalability, adaptability, and extensibility.

### Key Questions:

1. Does the fact that command names have changed require the code to be "closed for modification but open for extension"?  
2. Does adding new commands require the code to be "closed for modification but open for extension"?  
3. Does changing the output of commands require the code to be "closed for modification but open for extension"?  
4. Does changing the input/output method from the console to sockets require the code to be "closed for modification but open for extension"?

### Answers:

1. **Changes in Command Names:**  
   The fact that command names have changed did not require modifications to the core logic of the code, except for updating the dictionary used in `clientHandler` to map the new command names. For example, the `add` command was reused as an instance in operations like `post` and `patch` in this exercise without changing its internal logic.

2. **Adding New Commands:**  
   Adding new commands did not require modifying the existing code. This was achieved by designing the code according to the **Command Pattern**, where all operations implement a shared `ICommand` interface. This allowed the application to execute commands without needing to know their specific implementations, making the system open for extension but closed for modification.

3. **Changes in Command Outputs:**  
   Changes in the command outputs required minimal adjustments. For example, modifications were made to the `recommend` operation, which works independently, without impacting other commands like `add`. The changes involved only specific updates to the output format, such as error messages or status codes, without adding new logic or operations.

4. **Input/Output Transition from Console to Sockets:**  
   Transitioning the input/output from the console to sockets did not require core changes to the code. This was managed using the `IMenu` interface, which defines actions for displaying outputs to the user. This interface allowed swapping out the console-based implementation through **Dependency Injection**, making it adaptable to different input/output methods.


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


 
# Project Structure
src/: Contains the C++ recommendation engine.

server/: Node.js server implementation.

database/: MongoDB models and configuration.

client/: Python client implementation.

Dockerfile: Docker configuration for building the server.

docker-compose.yml: Docker Compose configuration for managing containers.

# Run Example:
![image](https://github.com/user-attachments/assets/d06d622b-0306-45e4-ba21-6ffa834802e4)


