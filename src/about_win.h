#ifndef ABOUT_WIN_H_
#define ABOUT_WIN_H_

// This file is for separating out declarations from the main application about_win.cc file
// Use it for forward declaring the main window processing functions, extern keywords for
// handles, and system DLL pointer types.

#include "framework.h"

#include "resource.h"

// Maximum size of string that can be loaded from resource table with LoadString().
#define MAX_LOADSTRING 255

/* Global Variables */

// current instance
extern HINSTANCE hInst;

// The title bar text
static WCHAR szTitle[MAX_LOADSTRING];

// The main window class name
static WCHAR szWindowClass[MAX_LOADSTRING];

/* End of global variables */

/* Forward declarations of functions included in this translation unit. */

// Creates the main window with CreateWindowW()
BOOL InitInstance(HINSTANCE, int);

// Window procedure function https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Registers the window class.
ATOM RegisterWndClass(HINSTANCE hInstance);

// Message handler for the "About" dialog box.
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

#endif // ABOUT_WIN_H_
