@ECHO OFF

cmake --build ./build_debug 
PUSHD build_debug
ctest -V
POPD
timeout /t 300