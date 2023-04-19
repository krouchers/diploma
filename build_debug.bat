@ECHO OFF

cmake -S . -B build_debug -GNinja -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build_debug --config Debug
cmake --install ./build_debug --prefix .