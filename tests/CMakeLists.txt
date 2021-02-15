enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        ./src/*.cpp
        ./src/*.hpp)
add_executable(liquium_tests ${TEST_SOURCES})

add_subdirectory(./ThirdParty/catch2)
include(./ThirdParty/catch2/contrib/Catch.cmake)
target_link_libraries(liquium_tests Catch2::Catch2)

target_include_directories(liquium_tests PRIVATE ./ThirdParty/)
target_include_directories(liquium_tests PRIVATE ../src/Engine)
target_include_directories(liquium_tests PRIVATE ../src/Editor)
target_include_directories(liquium_tests PRIVATE ../src/Common)

include(CTest)
catch_discover_tests(liquium_tests)

set_target_properties(liquium_tests PROPERTIES PREFIX "")
set_target_properties(liquium_tests PROPERTIES SUFFIX ".exe")
set_target_properties(liquium_tests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(liquium_tests PROPERTIES CXX_STANDARD 20)

# warning blob of gabage incoming
set_target_properties(liquium_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)# required by clang
set_target_properties(liquium_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/tests)# required by msvc
set_target_properties(liquium_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/tests)# required by msvc
set_target_properties(liquium_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin/tests)# required by msvc