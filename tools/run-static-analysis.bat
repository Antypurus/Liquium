@echo off
Rem this script should be called from the liquium project root
Rem this script will run static analysis via clang tidy

set "directory=%cd%"
call ./config-clang-tidy.bat
cd build/clang
python ../../CI/Static Analysis/run-clang-tidy.py
cd %directory%

