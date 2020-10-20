@echo off
Rem this script must be run from the liquium project root
Rem this script removes build files and folders associated with the msvc configuration

cd build
RMDIR msvc /s /q
cd ..