cmake_minimum_required(VERSION 3.10)

# Project setup
project(my_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

# Add the test executable
add_executable(my_test
        test1.cpp
        test2.cpp
        test2.h
        test_movie.cpp
        test_movie.h
        ../src/movie.cpp
        ../src/movie.h
        ../src/user.cpp
        ../src/user.h
        ../src/recommendAlgo.cpp
        ../src/recommendAlgo.h
        test_user.cpp
        test_user.h
        testWatchedDesiredMovie.cpp
        test_algo.h
        SumMoviesRelevanceTest.cpp
        SumMoviesRelevanceTest.h
        combineAlgoTest.cpp
        combineAlgoTest.h
        TestcountCommonMoviesWithGivenUser.cpp
        TestcountCommonMoviesWithGivenUser.h
)

# Link GoogleTest libraries
target_link_libraries(my_test gtest gtest_main)

# Enable testing and add the test
enable_testing()
add_test(NAME MyTest COMMAND my_test)
