@ECHO OFF

@REM cmake -S . -B build_debug -GNinja -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build_debug --config Debug
@REM cmake --install ./build_debug --prefix .