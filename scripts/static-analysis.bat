@echo off
Rem this script will run static analysis via clang tidy

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

set "directory=%cd%"
call scripts/config-clang-tidy.bat
if errorlevel 1 (
    echo Failed to configurate clang tidy
    exit /b %errorlevel1%
)

cd build/clang
Rem xcopy "..\\..\\.clang-tidy*" ".clang-tidy*" /y Note(Tiago): this seems to no longer be requried but I am going to keep it around in case something weird happens and it breaks
python ../../CI/StaticAnalysis/run-clang-tidy.py
exit /b %errorlevel%