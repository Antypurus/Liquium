@echo off

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

if exist ./build/clang/bin (
    echo Please compile the code at least once before running this script
    exit /b %errorlevel%
)

cd build/clang/bin/tests
liquium_tests.exe
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)