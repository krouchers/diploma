@ECHO OFF

cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build_debug --config Debug
cmake --install ./build_debug --prefix .