add_library(IWindow INTERFACE)
set_target_properties(IWindow PROPERTIES INTERFACE_LINK_LIBRARIES math)
target_include_directories(IWindow INTERFACE ${CMAKE_SOURCE_DIR}/src)

add_library(IGui INTERFACE)
target_include_directories(IGui INTERFACE ${CMAKE_SOURCE_DIR}/src)