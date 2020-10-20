Rem this script must be called from the liquium project root
cmake -Bbuild/msvc .
cd /build/msvc
cmake --build ../..
