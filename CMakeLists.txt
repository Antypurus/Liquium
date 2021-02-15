cmake_minimum_required(VERSION 3.14)

project(Liquium VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(src)

option(ENABLE_TESTS "Controls weather to compile tests or not" ON)
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()