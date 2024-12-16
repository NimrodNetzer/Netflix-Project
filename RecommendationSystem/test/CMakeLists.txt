cmake_minimum_required(VERSION 3.11)
project(RecommendationSystem_Tests)
set(CMAKE_CXX_STANDARD 20)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Test source files
set(TEST_SOURCES
        test_movie.cpp
        test_user.cpp
        test_add.cpp
        test_persistence.cpp
        test_recommendAlgo.cpp
)

set(TEST_HEADERS
        test_movie.h
        test_user.h
        test_add.h
        test_persistence.h
)

# Application source files
set(APP_SOURCES
        ../src/objects/Movie.cpp
        ../src/objects/User.cpp
        ../src/Core/app.cpp
        ../src/Commands/add.cpp
        ../src/Interfaces/ICommand.cpp
        ../src/Data/FilePersistence.cpp
        ../src/Commands/recommendAlgo.cpp
        ../src/Data/DataManager.cpp
)

set(APP_HEADERS
        ../src/objects/Movie.h
        ../src/objects/User.h
        ../src/Core/app.h
        ../src/Commands/add.h
        ../src/Interfaces/ICommand.h
        ../src/Interfaces/IPersistence.h
        ../src/Data/FilePersistence.h
        ../src/Data/DataManager.h
)

# Add executable for tests
add_executable(RecommendationSystem_Tests
        ${TEST_SOURCES}
        ${TEST_HEADERS}
        ${APP_SOURCES}
        ${APP_HEADERS}
)

# Link Google Test libraries
target_link_libraries(RecommendationSystem_Tests gtest gtest_main)