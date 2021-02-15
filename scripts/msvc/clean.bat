@echo off
Rem cleans builds files related to an msvc compilation

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

cd build
RMDIR msvc /s /q
exit /b %errorlevel1%