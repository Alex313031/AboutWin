// framwork.h: include file for standard system include files like windows.h,
// or project wide specific include files, such as C or C++ standard library
// headers. It can be precompiled, in which case, add a "framework.cc" file.

#ifndef ABOUT_FRAMEWORK_H_
#define ABOUT_FRAMEWORK_H_

#include "version.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// We need to define _UNICODE and UNICODE for TCHAR
#ifndef UNICODE
 #define UNICODE
#endif

#ifndef _UNICODE
 #define _UNICODE
#endif

// Windows Header Files
#include <windows.h> // Main Windows header
#include <commctrl.h> // Common controls header

// C Runtime Headers
#include <tchar.h> // For TCHAR, and automatically deducing wchar_t type

// C++ STL Headers
#include <iostream> // std::cout and std::wcout
#include <string> // std::string std::wstring

#endif // ABOUT_FRAMEWORK_H_
