// about_win.cc : Defines the entry point for the application, handles the window
// class and window messages, and initializes any global variables..

#include "about_win.h"

#include "framework.h"

HINSTANCE hInst;

// The main entry point, equivalent to int main()
int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow) {
  // Contains HINSTANCE from previous running instance, unused.
  UNREFERENCED_PARAMETER(hPrevInstance);

  // Import ComCtl32.dll
  InitCommonControls();

  // Allow and allocate conhost
  if (!AllocConsole()) {
    return 1;
  }

  // File handler pointer to a dummy file, possibly an actual logfile
  FILE* fNonExistFile = fDummyFile;
  //freopen_s(&fNonExistFile, "CONOUT$", "w", stdout); // Standard error
  //freopen_s(&fNonExistFile, "CONOUT$", "w", stderr); // Standard out

  // Initialize global strings.
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_ABOUTWIN, szWindowClass, MAX_LOADSTRING);

  // Create and register the window class.
  RegisterWndClass(hInstance);

  // Perform application initialization.
  if (!InitInstance(hInstance, nCmdShow)) {
    return FALSE;
  }

  // Load keyboard accelerators.
  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ABOUTWIN));

  MSG msg;
  // Main window message loop:
  while (GetMessage(&msg, nullptr, 0, 0)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return static_cast<int>(msg.wParam);
}

// Register the WNDCLASSEXW structure
ATOM RegisterWndClass(HINSTANCE hInstance) {
  // Declare and set size of this window class struct.
  WNDCLASSEXW wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);

  // Set styles, icons, and window message handling function.  
  wcex.style          = CS_HREDRAW | CS_VREDRAW; // Drawing style
  wcex.lpfnWndProc    = WndProc; // Window Procedure function
  wcex.cbClsExtra     = 0; // Extra bytes to add to end of this window class
  wcex.cbWndExtra     = 0; // Extra bytes to add to end hInstance
  wcex.hInstance      = hInstance; // This instance
  wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ABOUTWIN)); // Load our main app icon
  wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // Choose default cursor style to show
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // Choose window client area background color
  wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ABOUTWIN); // Attach menu to window
  wcex.lpszClassName  = szWindowClass; // Use our unique window class name
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // Load titlebar icon

  // Returns a "class atom", a win32 specific data type.
  return RegisterClassExW(&wcex);
}

// Saves global instance handle and creates the main window.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  bool success; // 
  hInst = hInstance; // Store instance handle in our global variable

  // The all important Win32 function that every GUI app must have to create
  // the Window.
  HWND hWnd = CreateWindowW(szWindowClass,
                            szTitle,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            0,
                            CW_USEDEFAULT,
                            0,
                            nullptr,
                            nullptr,
                            hInstance,
                            nullptr);

  // Early fail if we can't create the window.
  if (!hWnd) {
    success = false;
  } else {
    // Actually show the window (or hide it).
    success = ShowWindow(hWnd, nCmdShow);

    // If we showed the window, now the status will be set 
    if (success) {
      // Sucessfully created the window
      success = UpdateWindow(hWnd); // Start painting by sending the WM_PAINT message
    }
  }

  
  return true;
}

//  Processes window messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//  WM_RESIZE   - Handle window resizing
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_COMMAND: {
      int wmId = LOWORD(wParam);
      // Parse the menu selections:
      switch (wmId) {
        case IDM_ABOUT:
          // Show "About" dialog box
          DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
          break;
        case IDM_EXIT:
          // Send WM_DESTROY message to close window 
          DestroyWindow(hWnd);
          break;
        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
      }
    } break;
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      // TODO: Add any drawing code that uses hdc here...
      if (hdc) {
      }
      EndPaint(hWnd, &ps);
    } break;
    case WM_DESTROY:
      // Exit the application
      PostQuitMessage(0);
      break;
    // Fall through to DefWindowProc, any unhandled messages will be sent here
    // and Windows will decide what to do with it.
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Processes window messages for the "About" dialog box window procedure.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);

  bool AboutHandled = false; // Stores status of whether dialog has been handled user-wise.
  switch (message) {
    case WM_INITDIALOG:
      // Showed the dialog
      AboutHandled = true;
      break;
    case WM_COMMAND:
      // Exit the dialog
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
        if (EndDialog(hDlg, LOWORD(wParam))) {
          AboutHandled = true;
          return (INT_PTR)AboutHandled;
        } else {
          AboutHandled = false;
          break;
        }
      } break;
    default:
      AboutHandled = false;
      break;
  }

  // About dialog failed
  return (INT_PTR)AboutHandled;
}
