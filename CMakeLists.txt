cmake_minimum_required(VERSION 3.14)

project(Liquium VERSION 0.0.1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(warnings "/W4 /WX /EHsc")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd26812")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /nologo /Oi")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        #clang frontend
endif()

#add_subdirectory(./Tests)

file(GLOB_RECURSE  SRCS
        "src/Engine/*.cpp"
        "src/Engine/*.hpp"
	"src/Engine/*.h")

add_compile_definitions(WIN32_LEAN_AND_MEAN)

add_executable(${CMAKE_PROJECT_NAME} WIN32 src/Engine/Liquium_main.cpp ${SRCS})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(Liquium PRIVATE
        "d3d12.lib"
        "dxgi.lib"
        "d3dcompiler.lib"
        "windowscodecs.lib"
        )