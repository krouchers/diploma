#pragma once

#include <string>

void log(std::string fmt, ...);
std::string get_file_name(std::string file_path);

#ifdef _DEBUG 

#define info(fmt, ...) log("%s:%d [INFO]: " fmt "\n", get_file_name(__FILE__).c_str(), __LINE__ __VA_OPT__(,) __VA_ARGS__);
#define warn(fmt, ...) log("%s:%d [WARN]: " fmt "\n", get_file_name(__FILE__).c_str(), __LINE__ __VA_OPT__(,) __VA_ARGS__);

#else
#define info(fmt, ...)
#define warn(fmt, ...)
#endif
