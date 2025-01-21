# **Recommendation System**

This project integrates a **C++ recommendation system** with a **Node.js server** and **MongoDB database**, providing functionalities for user management, authentication, dynamic database operations, and personalized movie suggestions based on viewing preferences. 

The system operates with the following features:

### Key Features
1. **Server-Based Architecture**: A robust Node.js server handles API requests and coordinates between the client and the recommendation system.
2. **MongoDB Database**: Persistent storage for scalable and efficient data management.
3. **Recommendation System**: Integration with the C++ recommendation engine from **Task 1 and Task 2**, fetching personalized movie recommendations.
4. **Dynamic Updates**: Support for adding, updating, and deleting users and movies dynamically via API calls.
5. **Authentication and Authorization**: Token-based user authentication ensures secure access to the system.
6. **SOLID Principles**: Designed with scalability and extensibility in mind.

---

## **Key API Endpoints**

### **User Management**
- **`POST /api/users`**: Create a new user by submitting their details in JSON format.
- **`GET /api/users/:id`**: Retrieve specific user details using their unique ID.

### **Movie Management**
- **`GET /api/movies`**: Retrieve a list of all movies, optionally filtered by categories or user preferences.
- **`POST /api/movies`**: Add a new movie by submitting its details in JSON format.
- **`GET /api/movies/:id/recommend`**: Fetch personalized movie recommendations for a specific user.

### **Authentication**
- **`POST /api/tokens`**: Authenticate a user by submitting their credentials to receive an access token for secure interaction.

### **Categories Management**
- **`GET /api/categories`**: Retrieve all available movie categories.
- **`POST /api/categories`**: Add new categories dynamically.

---

## **How to Run**

### **Setup**
1. Navigate to the server's root directory:
   ```bash
   cd MainApi
   ```

### **Build and Run the Docker Image**
1. To build and run the application, execute:
   ```bash
   docker compose up --build -d
   ```
   - The **recommendation server** will run on port **8080**.
   - The **Node.js server** will run on port **3000** (modifiable in `docker-compose.yml`).

---

## **Run Examples**

1. **Run the Test Script**
   Use Python to run the provided test script:
   ```bash
   "C:\\Users\\orlib\\AppData\\Local\\Programs\\Python\\Python313\\python.exe" test.py
   ```

2. **Example Outputs**
   - Retrieve user by ID:
     ![get_user_by_id](https://github.com/user-attachments/assets/fbc72d9c-a471-4e97-82ff-9b4b67d7aeb5)

   - Get movies filtered by categories:
     ![get_movies_by_categories](https://github.com/user-attachments/assets/d5f78f21-4ac6-475c-94d0-64c4e7ba63d7)

   - Retrieve all categories:
     ![get_all_categories](https://github.com/user-attachments/assets/5abd65fb-dc47-4b6a-88c5-c9177dd2da89)

3. **More Examples**
   - Additional examples of run outputs can be found in the **`run__example`** folder.

---

This project provides a powerful platform for managing and exploring user-specific movie content. For additional help or troubleshooting, refer to the `run__example` folder for detailed examples and outputs. 
