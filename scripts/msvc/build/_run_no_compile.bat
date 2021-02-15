@echo off

Rem allows this script to be called from anywhere
cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

if exist ./build/msvc/bin (
	echo Please compile your code at least once
	exit /b %errorlevel1%
)

cd build/msvc/bin

Editor.exe
if errorlevel 1 (
    echo Failed to compile code
    exit /b %errorlevel%
)