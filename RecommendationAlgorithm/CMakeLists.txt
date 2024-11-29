# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard (use at least C++11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories (for header files)
include_directories(include)

# Add the source files (all .cpp files in the src folder)
file(GLOB SOURCES "src/*.cpp")

# Create the executable from the source files
add_executable(MyProject ${SOURCES})