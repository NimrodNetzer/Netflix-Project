import requests
import random
import string
from datetime import datetime, timedelta
from pymongo import MongoClient

# MongoDB Connection
MONGO_URI = "mongodb://localhost:27017/"  # Update with your MongoDB URI if different
DB_NAME = "NetFlix"  # Replace with your database name

# Base URLs
USER_URL = "http://localhost:3000/api/users/"
CATEGORY_URL = "http://localhost:3000/api/categories/"
MOVIE_URL = "http://localhost:3000/api/movies/"
RECOMMEND_URL = "http://localhost:3000/api/movies/{movie_id}/recommend"

def clear_database():
    """Clears all collections in the MongoDB database."""
    client = MongoClient(MONGO_URI)
    db = client[DB_NAME]
    
    collections_to_clear = ["categories", "counters", "movies", "users"]
    for collection in collections_to_clear:
        db[collection].delete_many({})
        print(f"Cleared collection: {collection}")
    
    client.close()

def random_string(length):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def random_date(start_date, end_date):
    delta = end_date - start_date
    random_days = random.randint(0, delta.days)
    return start_date + timedelta(days=random_days)

# Create Users
def create_users():
    users = []
    for i in range(100):
        user = {
            "email": f"user{i}@example.com",
            "password": "password123",
            "nickname": f"User{i}",
            "picture": f"https://example.com/pictures/user{i}.jpg"
        }
        response = requests.post(USER_URL, json=user)
        if response.status_code == 201:
            users.append(1)
        else:
            print(f"Failed to create user {i}: {response.text}")
    return users

# Create Categories
def create_categories(user_count):
    category_ids = []
    for i in range(10):
        category = {
            "name": f"Category {i}",
            "promoted": random.choice([True, False])
        }
        headers = {"user-id": str(random.randint(1, user_count))}
        response = requests.post(CATEGORY_URL, json=category, headers=headers)
        if response.status_code == 201:
            # Parse the response to get the ID of the created category
            category_id = response.headers.get("Location").split("/")[-1]
            if category_id:
                category_ids.append(category_id)
        else:
            print(f"Failed to create category {i}: {response.text}")
    return category_ids

# Create Movies
def create_movies(category_ids, user_count):
    movies = []
    for i in range(100):
        # Assign multiple random categories
        selected_categories = random.sample(category_ids, random.randint(1, 3))  # Select 1 to 3 categories
        age = random.randint(1, 18)
        movie = {
            "name": f"Movie {i}",
            "picture": f"https://example.com/movies/movie{i}.jpg",
            "description": f"This is the description of Movie {i}",
            "age": age,
            "time": f"{random.randint(1, 3)}h {random.randint(0, 59)}m",
            "releaseDate": random_date(datetime(2000, 1, 1), datetime(2025, 1, 1)).isoformat(),
            "quality": random.choice(["HD", "SD", "4K"]),
            "categories": selected_categories,  # Assign multiple categories
            "cast": [
                {"name": random_string(8), "role": random.choice(["Lead", "Supporting"])}
                for _ in range(random.randint(2, 5))
            ],
            "properties": {
                "genre": random.choice(["Action", "Drama", "Comedy", "Horror"]),
                "language": random.choice(["English", "Spanish", "French", "German"])
            },
            "movieData": {
                "rating": random.uniform(1, 10),
                "boxOffice": random.randint(1000000, 100000000)
            },
            "author": f"Author {i}"
        }
        headers = {"user-id": str(random.randint(1, user_count))}
        response = requests.post(MOVIE_URL, json=movie, headers=headers)
        if response.status_code == 201:
            movies.append(1)
        else:
            print(f"Failed to create movie {i}: {response.text}")
    return movies

# Add Movie to Watched List
def add_movie_to_watched(movie_id, user_id):
    user_id = random.randint(1, 90)
    movie_id = random.randint(1, 90)

    headers = {"user-id": str(user_id)}
    url = RECOMMEND_URL.format(movie_id=movie_id)
    response = requests.post(url, headers=headers)
    if response.status_code == 201:
        print(f"Movie {movie_id} successfully added to watched list for user {user_id}.")
    else:
        print(f"Failed to add movie {movie_id} to watched list for user {user_id}: {response.text}")

# Main Execution
def main():
     print("Clearing database...")
     clear_database()  # Clears all existing data

     print("Creating users...")
     users = create_users()
     print(f"Created {len(users)} users.")

     print("Creating categories...")
     category_ids = create_categories(len(users))
     print(f"Created {len(category_ids)} categories.")

     print("Creating movies...")
     movies = create_movies(category_ids, len(users))
     print(f"Created {len(movies)} movies.")

     # Example: Add first movie to the watched list of first user
     for i in range(1, 1000):
        add_movie_to_watched(1, 1)

if __name__ == "__main__":
    main()
