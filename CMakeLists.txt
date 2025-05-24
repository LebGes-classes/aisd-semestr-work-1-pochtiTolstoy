cmake_minimum_required(VERSION 3.14)
project(avltree)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    src
    src/avltree
    src/utils
)

# Main executable with all required sources
add_executable(avltree_app 
    src/main.cpp
    src/utils/menu.cpp  # Add missing source file
)

# GoogleTest configuration
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable with required sources
add_executable(avltree_tests
    tests/avltree_test.cpp
    src/utils/menu.cpp  # Add if tests need menu functionality
)
target_link_libraries(avltree_tests
    GTest::gtest_main
    pthread
)

enable_testing()
add_test(NAME avltree_tests COMMAND avltree_tests)
