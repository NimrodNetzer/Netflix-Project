# Netflix-BIU
שלום, מאחר והצוות היה במילואים יש לנו הארכה. נא לא לבדוק את הפרוייקט כרגע, תודה רבה.

# Recommendation System

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

