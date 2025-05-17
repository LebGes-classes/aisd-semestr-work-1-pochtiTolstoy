cmake_minimum_required(VERSION 3.14)
project(avltree)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include AVLTree headers as a library (header-only)
add_library(avltree INTERFACE)
target_include_directories(avltree INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Main executable (if you have a main program)
add_executable(avltree_app src/main.cpp)
target_link_libraries(avltree_app avltree)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
enable_testing()
add_executable(avltree_tests
    tests/avltree_test.cpp  # Updated test file
)
target_link_libraries(avltree_tests
    avltree
    GTest::gtest_main
)

# Discover and add tests
include(GoogleTest)
gtest_discover_tests(avltree_tests)
