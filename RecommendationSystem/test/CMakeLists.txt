cmake_minimum_required(VERSION 3.11)
project(RecommendationSystem_Tests)
set(CMAKE_CXX_STANDARD 20)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Test source files
set(TEST_SOURCES
        test1.cpp
        test2.cpp
        test_movie.cpp
        test_user.cpp
        test_add.cpp
        test_persistence.cpp
        test_recommendAlgo.cpp
)

set(TEST_HEADERS
        test2.h
        test_movie.h
        test_user.h
        test_add.h
        test_persistence.h
)

# Application source files
set(APP_SOURCES
        ../src/Movie.cpp
        ../src/User.cpp
        ../src/app.cpp
        ../src/add.cpp
        ../src/ICommand.cpp
        ../src/FilePersistence.cpp
        ../src/recommendAlgo.cpp
        ../src/DataManager.cpp
)

set(APP_HEADERS
        ../src/Movie.h
        ../src/User.h
        ../src/app.h
        ../src/add.h
        ../src/ICommand.h
        ../src/IPersistence.h
        ../src/FilePersistence.h
        ../src/DataManager.h
        test_new.cpp
        test_new.h
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