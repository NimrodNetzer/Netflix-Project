cmake_minimum_required(VERSION 3.28.1)
project(Netflix-BIU)

set(CMAKE_CXX_STANDARD 20)

add_executable(Netflix-BIU
        RecommendationSystem/algorithm/commonMovies.cpp

        RecommendationSystem/src/main.cpp
        RecommendationSystem/src/main.cpp
        RecommendationSystem/src/user.cpp
        RecommendationSystem/src/movie.cpp
)