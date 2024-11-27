cmake_minimum_required(VERSION 3.10)
project(my_test)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
add_executable(my_test test1.cpp
        test2.cpp
        test2.h)
target_link_libraries(my_test gtest gtest_main)