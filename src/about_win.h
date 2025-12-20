#ifndef ABOUT_WIN_H_
#define ABOUT_WIN_H_

// This file is for separating out declarations from the main application about_win.cc file
// Use it for forward declaring the main window processing functions, extern keywords for
// handles, and system DLL pointer types.

#include "framework.h"

#include "os_info_dll.h"
#include "resource.h"

// Maximum size of string that can be loaded from resource table with LoadString().
#define MAX_LOADSTRING 255

/* Global Variables */

// current instance
extern HINSTANCE hInst;
extern HWND hTextOut;

// The title bar text
static WCHAR szTitle[MAX_LOADSTRING];

// The main window class name
static WCHAR szWindowClass[MAX_LOADSTRING];

// Dummy file output for conhost
static FILE* fDummyFile;

// Static layout constants
static constexpr unsigned int MIN_WIDTH = 150;
static constexpr unsigned int MIN_HEIGHT = 300;
static constexpr unsigned int DEFAULT_WIDTH = 360;
static constexpr unsigned int DEFAULT_HEIGHT = 480;

/* End of global variables */

/* Forward declarations of functions included in this translation unit. */

// Registers the window class.
ATOM RegisterWndClass(HINSTANCE hInstance);

// Creates the main window with CreateWindowW()
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

// Appends a line of text to the edit control.
void AppendTextToEditControl(HWND hWnd, const std::wstring line);

// Paints text to edit control
void ShowText(HWND hWnd);

// Window procedure function https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Message handler for the "About" dialog box.
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// Returns the HINSTANCE of a given Window's HWND
HINSTANCE GetHinstanceFromHwnd(HWND hWnd);

#endif // ABOUT_WIN_H_
