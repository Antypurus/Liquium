@echo off
Rem cleans build files related to clang compilations

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

cd build
RMDIR clang /s /q