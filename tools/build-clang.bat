@echo off

cmake -E env LDFLAGS="-fuse-ld=lld-link" PATH="C:\ProgramData\chocolatey\lib\ninja\tools"
cmake -H. -G Ninja -Bbuild/clang -DCMAKE_C_COMPILER:PATH="%ProgramFiles%\LLVM\bin\clang.exe" -DCMAKE_CXX_COMPILER:PATH="%ProgramFiles%\LLVM\bin\clang.exe" -DCMAKE_C_COMPILER_ID="Clang" -DCMAKE_CXX_COMPILER_ID="Clang" -DCMAKE_SYSTEM_NAME="Generic"
cd build/clang
ninja
