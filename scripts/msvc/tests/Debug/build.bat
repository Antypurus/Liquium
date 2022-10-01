@echo off
setlocal EnableDelayedExpansion
Rem compiles the project tests in debug mode with msvc

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

Rem check if the build directory is configured to be in debug mode
set cmake_config_present=0
if exist .\build\msvc\build_type (
    set /p build_type=< ./build/msvc/build_type
    if !build_type!==Debug (
        echo build folder already configured for debug build, skipping cmake config step
        set cmake_config_present=1
    )
)
 
Rem runs the cmake scripts if either the buld file did not exists or the old build type was not debug
(
    call .\scripts\msvc\cmake.bat -DENABLE_TESTS=ON
    if errorlevel 1 (
        echo Failed to run cmake configuration for debug build type
        exit /b %errorlevel%
    )
    if exist .\build\msvc\build_type (
        del /q /f .\build\msvc\build_type
        if errorlevel 1 (
           echo Failed to reset build_type file
           exit /b %errorlevel%
        )
    )
    echo Debug>> .\build\msvc\build_type
    if errorlevel 1 (
        echo Failed to write build type to build folder, rebuld script may not work
        exit /b %errorlevel%
    )
)

Rem compiles the test code
cd build\msvc

cmake --build . --target liquium_tests -j %NUMBER_OF_PROCESSORS% --config Debug
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)