@echo off

set "directory=%cd%"

call ./tools/build-clang.bat

cd %directory%
call ./tools/build-msvc.bat