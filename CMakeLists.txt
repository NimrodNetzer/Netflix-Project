cmake_minimum_required(VERSION 3.28.1)
project(Netflix-BIU)

set(CMAKE_CXX_STANDARD 20)

add_executable(Netflix-BIU

        RecommendationSystem/src/main.cpp
        RecommendationSystem/src/user.cpp
        RecommendationSystem/src/movie.cpp
        RecommendationSystem/src/recommendations.cpp
        RecommendationSystem/src/recommendations.h
)