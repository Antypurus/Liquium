@echo off
Rem this script runs the cmake script and open the visual studio project

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

call ./scripts/msvc/cmake.bat
if errorlevel 1 (
    echo "CMake script failed for the msvc configuration"
    exit /b %errorlevel%
)

cd build/msvc
if errorlevel 1 (
    echo "Failed to find MSVC build directory"
    exit /b %errorlevel%
)

start Liquium.sln