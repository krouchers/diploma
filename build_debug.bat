@ECHO OFF

cmake -S . -B build_debug
cmake --build ./build_debug
cmake --install ./build_debug --prefix .