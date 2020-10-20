Rem this script must be called from the liquium project root
Rem this script runs the cmake conrfiguration and compiles the project for the msvc configuration

cmake -Bbuild/msvc .
cd build/msvc
cmake --build .
