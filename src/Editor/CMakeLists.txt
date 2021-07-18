set(LIQUIUM_EDITOR "Editor")

file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS
        *.cpp
        *.hpp
        ../Common/*.cpp
        ../Common/*.hpp)
add_executable(${LIQUIUM_EDITOR} WIN32  ${EDITOR_SOURCES})

target_include_directories(${LIQUIUM_EDITOR} PRIVATE ../Engine)
target_link_libraries(${LIQUIUM_EDITOR} PRIVATE Liquium)

target_compile_options(${LIQUIUM_EDITOR} PRIVATE /W4 /WX)
target_compile_options(${LIQUIUM_EDITOR} PRIVATE ${CMAKE_CXX_FLAGS} /MP /nologo)

# disabling annoying stupid warnings that come with w4
target_compile_options(${LIQUIUM_EDITOR} PRIVATE ${CMAKE_CXX_FLAGS} /wd26812 /wd4100)
target_link_options(${LIQUIUM_EDITOR} PUBLIC /DEBUG)

set_target_properties(${LIQUIUM_EDITOR} PROPERTIES PREFIX "")
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES SUFFIX ".exe")
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES CXX_STANDARD 20)

set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)# required by clang
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(${LIQUIUM_EDITOR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)# required by msvc