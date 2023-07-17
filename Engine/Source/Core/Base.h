#pragma once

#ifdef CORE_WINDOWS_PLATFORM

#ifdef CORE_BUILD_DLL
#define CE_API __declspec(dllexport)
#else
#define CE_API __declspec(dllimport)
#endif

#endif