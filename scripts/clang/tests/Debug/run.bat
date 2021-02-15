@echo off

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

call ./scripts/clang/tests/Debug/build.bat
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)

cd build/clang/bin/tests
liquium_tests.exe
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)