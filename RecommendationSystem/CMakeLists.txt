cmake_minimum_required(VERSION 3.11)
project(RecommendationSystem)

set(CMAKE_CXX_STANDARD 20)

# Gather all .cpp and .h files in the src directory
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

# Add the executable and include all the source and header files
add_executable(RecommendationSystem ${SOURCES} ${HEADERS}
        src/help.cpp
        src/help.h
        src/IMenu.cpp
        src/IMenu.h
        src/ConsoleMenu.cpp
        src/ConsoleMenu.h)

# Optionally, include the src directory for header file lookups
target_include_directories(RecommendationSystem PRIVATE ${CMAKE_SOURCE_DIR}/src)
