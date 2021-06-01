@echo off

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

call ./scripts/msvc/tests/Debug/build.bat
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)

.\build\msvc\bin\tests\liquium_tests.exe
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)