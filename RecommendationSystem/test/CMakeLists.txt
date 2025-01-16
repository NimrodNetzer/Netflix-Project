cmake_minimum_required(VERSION 3.11)
project(RecommendationSystem_Tests)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test source files
set(TEST_SOURCES
        test_movie.cpp
        test_user.cpp
        test_add.cpp
        test_persistence.cpp
        test_recommendAlgo.cpp
        test_Delete.cpp
)

set(TEST_HEADERS
        test_movie.h
        test_user.h
        test_add.h
        test_persistence.h
        test_Delete.h
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
        ../src/Commands/Delete.cpp
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
        ../src/Commands/Delete.h
        test_recommendAlgo.h
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