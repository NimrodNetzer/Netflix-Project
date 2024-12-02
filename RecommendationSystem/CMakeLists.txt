cmake_minimum_required(VERSION 3.29)
project(RecommendationSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(RecommendationSystem src/main.cpp
        src/movie.cpp
        src/user.cpp
        src/user.h
        src/recommendAlgo.cpp
        src/recommendAlgo.h
)
