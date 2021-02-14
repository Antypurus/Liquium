@echo off
setlocal EnableDelayedExpansion
Rem compiles the project tests in release mode with clang

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

Rem check if the build directory is configured to be in release mode
set cmake_config_present=0
if exist .\build\clang\build_type (
    set /p build_type=< ./build/clang/build_type
    if !build_type!==release (
        echo build folder already configured for release build, skipping cmake config step
        set cmake_config_present=1
    )
)
 
Rem runs the cmake scripts if either the buld file did not exists or the old build type was not release
if %cmake_config_present%==0 (
    call ./scripts/clang/cmake.bat  -DCMAKE_BUILD_TYPE=release -DENABLE_TESTS=ON
    if errorlevel 1 (
        echo Failed to run cmake configuration for release build type
        exit /b %errorlevel%
    )
    if exist ./build/clang/build_type (
        del /q /f .\build\clang\build_type
        if errorlevel 1 (
           echo Failed to reset build_type file
        )
    )
    echo release>> ./build/clang/build_type
    if errorlevel 1 (
        echo Failed to write build type to build folder, rebuld script may not work
    )
)

Rem compiles the test code
cd build/clang
ninja liquium_tests -j %NUMBER_OF_PROCESSORS%
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)