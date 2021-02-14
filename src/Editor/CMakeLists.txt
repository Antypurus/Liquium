set(LIQUIUM_EDITOR "Editor")

file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS
        *.cpp
        *.hpp
        ../Common/*.cpp
        ../Common/*.hpp)
add_executable(${LIQUIUM_EDITOR} ${EDITOR_SOURCES})

target_include_directories(${LIQUIUM_EDITOR} PRIVATE ../Engine)
target_link_libraries(${LIQUIUM_EDITOR} PRIVATE Liquium)

set_target_properties(${LIQUIUM_EDITOR} PROPERTIES PREFIX "")
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES SUFFIX ".exe")

set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)# required by clang
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)# required by msvc