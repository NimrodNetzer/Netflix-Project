cmake_minimum_required(VERSION 3.29)
project(RecommendationSystem_Tests)
set(CMAKE_CXX_STANDARD 20)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
add_executable(RecommendationSystem_Tests test1.cpp
        test2.cpp
        test2.h
        test_movie.cpp
        test_movie.h
        ../src/Movie.cpp
        ../src/Movie.h
        ../src/User.cpp
        ../src/User.h
        test_user.cpp
        test_user.h
        test_persistence.cpp
        ../src/IPersistence.h
        ../src/FilePersistence.cpp
        ../src/FilePersistence.h
        )
target_link_libraries(RecommendationSystem_Tests gtest gtest_main)