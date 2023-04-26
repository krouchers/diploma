#pragma once

#include <string>

void Log(std::string fmt, ...);
std::string GetFileName(std::string file_path);

#ifdef _DEBUG 

#define info(fmt, ...) Log("%s:%d [INFO]: " fmt "\n", GetFileName(__FILE__).c_str(), __LINE__ __VA_OPT__(,) __VA_ARGS__);
#define warn(fmt, ...) Log("%s:%d [WARN]: " fmt "\n", GetFileName(__FILE__).c_str(), __LINE__ __VA_OPT__(,) __VA_ARGS__);

#else
#define info(fmt, ...)
#define warn(fmt, ...)
#endif
