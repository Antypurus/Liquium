@echo off
Rem this script must be run from the liquium project root
Rem this script remove build file and folder associated with the clang configuration

cd build
RMDIR clang /s /q
cd ..