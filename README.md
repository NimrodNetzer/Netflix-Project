# Netflix-BIU
שלום, מאחר והצוות היה במילואים יש לנו הארכה. נא לא לבדוק את הפרוייקט כרגע, תודה רבה.

`docker build -t recsys .`
first run:
`docker run -it --name recommendation recsys`

second run:
`docker start -ai recommendation`

To run the tests:
`docker run --rm "build_name" ./test/build/RecommendationSystem_Tests`
