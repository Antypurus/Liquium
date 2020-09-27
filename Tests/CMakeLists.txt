cmake_minimum_required(VERSION 3.14)

project(example)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(./ThirdParty/googletest)
enable_testing()


include(GoogleTest)
add_executable(example test_main.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)