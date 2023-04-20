#pragma once

#include <string>

void Log(std::string fmt, ...);
std::string GetFileName(std::string file_path);

#ifdef DEBUG_ 

#define info(fmt, ...) log("%s:%d [INFO]: " fmt "\n", get_file_name(__FILE__).c_str(), __LINE__ __VA_OPT__(,) __VA_ARGS__);
#define warn(fmt, ...) log("%s:%d [WARN]: " fmt "\n", get_file_name(__FILE__).c_str(), __LINE__ __VA_OPT__(,) __VA_ARGS__);

#else
#define info(fmt, ...)
#define warn(fmt, ...)
#endif
