cmake_minimum_required(VERSION 3.29)
project(RecommendationSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(RecommendationSystem src/main.cpp
        src/Movie.cpp
        src/FilePersistence.cpp
        src/FilePersistence.h
        src/User.h
        src/User.cpp)
