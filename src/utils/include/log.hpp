#pragma once

#include <string>

void log(std::string fmt, ...);
std::string get_file_name(std::string file_path);

#ifdef _DEBUG
#define info(fmt, ...) log("%s:%d [info]: " fmt, get_file_name(__FILE__).c_str(), __LINE__ __VA_OPT__(__VA_ARG__));
#else
#define info(fmt, ...)
#endif
