@echo off
Rem this script must be called from the liquium project root
Rem this script run the cmake script and open the visual studio project

cmake -Bbuild/msvc .
cd build/msvc
start Liquium.sln