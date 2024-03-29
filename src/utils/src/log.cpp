#include <cstdarg>

#include "utils/log.hpp"

std::string GetFileName(std::string file_path)
{
    return file_path.substr(file_path.find_last_of('/') + 1);
}

void Log(std::string fmt, ...)
{
    std::va_list args;
    va_start(args, fmt);
    std::vprintf(fmt.c_str(), args);
    va_end(args);
}