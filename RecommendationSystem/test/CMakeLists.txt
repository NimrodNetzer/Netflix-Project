cmake_minimum_required(VERSION 3.29)
project(my_test)
set(CMAKE_CXX_STANDARD 20)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
add_executable(my_test test1.cpp
        test2.cpp
        test2.h
        test_movie.cpp
        test_movie.h
        ../src/movie.cpp
        ../src/movie.h
        ../src/user.cpp
        ../src/user.h
        test_user.cpp
        test_user.h
        test_persistence.cpp
        ../src/FilePersistence.cpp)
target_link_libraries(my_test gtest gtest_main)