@echo off
Rem this script must be run from the liquium project root
Rem this script runs the cmake configuration script and compile the project executable for the msvc and clang configurations

set "directory=%cd%"

call ./tools/build-clang.bat

cd %directory%
call ./tools/build-msvc.bat