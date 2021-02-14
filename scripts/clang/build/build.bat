@echo off
setlocal EnableDelayedExpansion

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

if not exist ./build/clang (
    echo Build system not configured, please run a build of the project before using this command.
    exit /b %errorlevel%
)
if not exist ./build/clang/build_type (
    echo Build system not configured, please run a bulid of the project before using this command.
    exit /b %errorlevel1%
)

set /p build_type=< ./build/clang/build_type
if errorlevel 1 (
    echo Failed to read build configuration from build_type file
    exit /b %errorlevel%
)

call ./scripts/clang/build/!build_type!/build.bat
if errorlevel 1 (
    echo Failed to rebuild code
    exit /b %errorlevel%
)
