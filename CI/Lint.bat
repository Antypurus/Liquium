@echo off
Rem run code style checks

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

python ./CI/Linting/lint.py
exit /b %errorlevel%