include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

build_library_with_type(utils STATIC ${MODULE_COMPILE_FLAGS})

target_sources(utils PRIVATE 
   src/log.cpp)   

target_include_directories(utils PUBLIC include)