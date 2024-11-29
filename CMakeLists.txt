# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.29)

# Set the project name
project(Netflix-BIU)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Add subdirectories for employee modules
add_subdirectory(RecommendationSystem)
add_subdirectory(RecommendationAlgorithm)