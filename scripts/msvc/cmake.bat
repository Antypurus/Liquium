@echo off
Rem configures cmake to build with msvc

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

cmake -Bbuild/msvc . %*
if errorlevel 1 (
    echo "Failed to run CMake configuration script for the MSVC configuration"
    exit /b %errorlevel%
)