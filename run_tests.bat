@ECHO OFF

cmake --build ./build_debug 
PUSHD build_debug
ctest 
POPD
timeout /t 300