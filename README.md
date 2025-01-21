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

1. **Create the `.env.prod` file**:  
   Before running the services, you need to create a `.env.prod` file in the `config` directory within `./MainApi`.

   #### **Commands to create the file**:
   - **Linux/Mac**:
     ```bash
     mkdir -p ./MainApi/config
     touch ./MainApi/config/.env.prod
     ```
   - **Windows** (works in both Command Prompt and PowerShell):
     ```cmd
     mkdir MainApi\config && type nul > MainApi\config\.env.prod
     ```

   #### **Example `config/.env.prod`**:
   ```plaintext
   RECOMMENDATION_PORT=4000
   PORT=5000
   Note: You can leave this file empty if you don't wish to change the default ports. The default ports are:
   
   Recommendation server: 8080
   App: 3000
   MongoDB: 27017
   
2. ### **Navigate to the server's root directory**
   ```bash
   cd MainApi
3. ### **Build and Run the Docker Containers**
   Build and run the application using:
   ```bash
   docker compose up --build -d
4. ### Optional - Run the test case:
   
   ```bash
   docker compose run --rm test_case
#### Running this will create 100 movies, 100 users, 10 categories, and add 1000 movies to users watched movie list.
## **Run Examples**

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
