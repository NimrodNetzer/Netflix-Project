cmake_minimum_required(VERSION 3.11)
project(RecommendationSystem)

set(CMAKE_CXX_STANDARD 20)

# Explicitly list all the source and header files
set(SOURCES
        src/add.cpp
        src/app.cpp
        src/ConsoleMenu.cpp
        src/FilePersistence.cpp
        src/help.cpp
        src/ICommand.cpp
        src/IMenu.cpp
        src/main.cpp
        src/Movie.cpp
        src/recommend.cpp
        src/recommendAlgo.cpp
        src/User.cpp
)

set(HEADERS
        src/add.h
        src/app.h
        src/ConsoleMenu.h
        src/FilePersistence.h
        src/help.h
        src/ICommand.h
        src/IMenu.h
        src/IPersistence.h
        src/Movie.h
        src/recommend.h
        src/recommendAlgo.h
        src/User.h
)

# Add the executable
add_executable(RecommendationSystem ${SOURCES} ${HEADERS})

# Include the src directory for header file lookups
target_include_directories(RecommendationSystem PRIVATE ${CMAKE_SOURCE_DIR}/src)
