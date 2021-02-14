@echo off
Rem runs source code style checking

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

call ./CI/Lint.bat
exit /b %errorlevel1%