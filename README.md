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

# Run Example:
![image](https://github.com/user-attachments/assets/d06d622b-0306-45e4-ba21-6ffa834802e4)


