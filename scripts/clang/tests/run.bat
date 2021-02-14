@echo off
setlocal EnableDelayedExpansion

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

if exist ./build/clang/build_type (
    set /p build_type=< ./build/clang/build_type
) else (
    echo Please compile the tests at least once in one of the configurations
    exit /b %errorlevel%
)

call ./scripts/clang/tests/!build_type!/build.bat
if errorlevel 1 (
    exit /b %errorlevel%
)

cd build/clang/bin/tests
liquium_tests.exe
exit /b %errorlevel%