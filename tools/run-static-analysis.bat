@echo off
Rem this script should be called from the liquium project root
Rem this script will run static analysis via clang tidy

set "directory=%cd%"
call tools/config-clang-tidy.bat
cd build/clang
xcopy "..\\..\\.clang-tidy*" ".clang-tidy*" /y
python ../../CI/StaticAnalysis/run-clang-tidy.py
cd %directory%

