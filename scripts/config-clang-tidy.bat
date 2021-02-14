@echo off

cd %~dp0%
:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

call scripts/clang/cmake.bat -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DENABLE_TESTS=ON
if errorlevel 1 (
    echo "CMake buld script failed for the clang configuration, there clang-tidy cannot be run"
    exit /b %errorlevel%
)