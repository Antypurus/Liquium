@echo off
Rem document what it does

:git_search_start
if not exist .git (
    cd ..
    goto :git_search_start
)

Rem for msbuild remove -G Ninja and add -T llvm -A x64
cmake -E env LDFLAGS="-fuse-ld=lld-link"^
 cmake -H. -G Ninja -Bbuild/clang ^
    -DCMAKE_C_COMPILER:PATH="%ProgramFiles%\LLVM\bin\clang.exe" ^
    -DCMAKE_CXX_COMPILER:PATH="%ProgramFiles%\LLVM\bin\clang++.exe" ^
    -DCMAKE_C_COMPILER_ID="Clang" ^
    -DCMAKE_CXX_COMPILER_ID="Clang" ^
    -DCMAKE_SYSTEM_NAME="Generic" ^
    %*
exit /b %errorlevel%