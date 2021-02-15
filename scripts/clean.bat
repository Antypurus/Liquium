@echo off
Rem this script must be run from the liquium project root
Rem this script removes all build files and folders

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

RMDIR build /s /q