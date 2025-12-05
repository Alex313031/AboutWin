#pragma once

// // Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#ifndef __MINGW32__
#include <WinSDKVer.h>
#endif

#define _WIN32_WINNT 0x0501 // Windows XP x86

#define _WIN64_WINNT 0x0502 // Minimum version for 64 bit

#define _WIN32_IE 0x0600 // Minimum Internet Explorer version

#ifndef __MINGW32__
#include <SDKDDKVer.h>
#endif
