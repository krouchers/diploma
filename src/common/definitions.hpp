#pragma once

#ifdef DLL_EXPORT
#define GEODIP_API __declspec(dllexport)
#else
#define GEODIP_API __declspec(dllimport)
#endif