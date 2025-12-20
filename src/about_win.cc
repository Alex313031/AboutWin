// about_win.cc : Defines the entry point for the application, handles the window
// class and window messages, and initializes any global variables..

#include "about_win.h"

#include "framework.h"

HINSTANCE g_hInst;
HWND hTextOut;
HWND hGetInfoButton;
HWND hRefreshButton;
HWND hClearButton;
HWND hAboutButton;
HWND hStatusBar;

static std::wstring textout;
static int current_width;
static int current_height;

// The main entry point, equivalent to int main()
int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow) {
  // Contains HINSTANCE from previous running instance, unused.
  UNREFERENCED_PARAMETER(hPrevInstance);

  // Import ComCtl32.dll
  InitCommonControls();
  // Check that we can load osinfo.dll and run init function.
  if (!InitOsInfoDll()) {
    MessageBoxW(nullptr, L"osinfo.dll init failed!", L"Error!", MB_OK | MB_ICONERROR);
    return -1;
  }

  // Allow and allocate conhost for cmd.exe logging window
  if (!AllocConsole()) {
    return 1;
  }

  // File handler pointer to a dummy file, possibly an actual logfile
  FILE* fNonExistFile = fDummyFile;
#ifndef __MINGW32__
  freopen_s(&fNonExistFile, "CONOUT$", "w", stdout); // Standard error
  freopen_s(&fNonExistFile, "CONOUT$", "w", stderr); // Standard out
#else
  // freopen_s doesn't exist in MinGW...
  fNonExistFile = freopen("CONOUT$", "w", stdout); // Standard error
  fNonExistFile = freopen("CONOUT$", "w", stderr); // Standard out
#endif // __MINGW32__
  if (!fNonExistFile) {
    return 1;
  }

  // Initialize global strings.
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_ABOUTWIN, szWindowClass, MAX_LOADSTRING);

  // Create and register the window class.
  RegisterWndClass(hInstance);

  // Perform application initialization.
  if (!InitInstance(hInstance, nCmdShow)) {
    return FALSE;
  } else {
    std::wcout << L"Welcome to AboutWin ver. " << VERSION_STRING << std::endl;
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
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW); // Choose window client area background color
  wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ABOUTWIN); // Attach menu to window
  wcex.lpszClassName  = szWindowClass; // Use our unique window class name
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // Load titlebar icon

  // Returns a "class atom", a win32 specific data type.
  return RegisterClassExW(&wcex);
}

// Saves global instance handle and creates the main window.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  bool success = false; // 
  g_hInst = hInstance; // Store instance handle in our global variable

  // The all important Win32 function that every GUI app must have to create
  // the Window.
  HWND hWnd = CreateWindowExW(WS_EX_WINDOWEDGE,
                              szWindowClass,
                              szTitle,
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              DEFAULT_WIDTH,
                              DEFAULT_HEIGHT,
                              nullptr,
                              nullptr,
                              hInstance,
                              nullptr);

  // Early fail if we can't create the window.
  if (!hWnd) {
    success = false;
  } else {
    // Actually show the window (or hide it).
    ShowWindow(hWnd, nCmdShow);

    // Sucessfully created the window
    success = UpdateWindow(hWnd); // Start painting by sending the WM_PAINT message
  }

  return success;
}

void InitControls(HWND hWnd) {
  // Create text control
  hTextOut = CreateWindowExW(0, WC_EDIT, nullptr,
      WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE |
      ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
      STATIC_LEFT,
      STATIC_TOP,
      200,
      300,
      hWnd, (HMENU)IDC_TEXT1, g_hInst, nullptr);
  // Main "get info" button
  hGetInfoButton = CreateWindowExW(0, WC_BUTTON, L"Get Info!",
      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      STATIC_LEFT,
      300,
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      hWnd, (HMENU)IDC_GETINFO, g_hInst, nullptr
  );
  hRefreshButton = CreateWindowExW(0, WC_BUTTON, L"Refresh",
      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      STATIC_LEFT + BUTTON_WIDTH + INTRA_PAD,
      300,
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      hWnd, (HMENU)IDC_REFRESH, g_hInst, nullptr
  );
  hClearButton = CreateWindowExW(0, WC_BUTTON, L"Clear",
      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      STATIC_LEFT,
      300 + BUTTON_HEIGHT,
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      hWnd, (HMENU)IDC_CLEAR, g_hInst, nullptr
  );
  hAboutButton = CreateWindowExW(0, WC_BUTTON, L"About",
      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
      STATIC_LEFT + BUTTON_WIDTH + INTRA_PAD,
      300 + BUTTON_HEIGHT,
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      hWnd, (HMENU)IDC_ABOUT, g_hInst, nullptr
  );
  // Lastly, create the status bar
  hStatusBar = CreateWindowExW(
      0, STATUSCLASSNAME, nullptr,
      WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
      0,
      0,
      0,
      0,
      hWnd, nullptr, g_hInst, nullptr
  );
  const int kStatusSplit = DEFAULT_WIDTH - 100;
  const int kStatusParts[2] = { kStatusSplit, -1 }; // -1 = extend to right edge
  SendMessageW(hStatusBar, SB_SETPARTS, 2, (LPARAM)kStatusParts);
  SendMessageW(hStatusBar, SB_SETTEXT, 1, (LPARAM)L"Status");
}

void HandleResize(HWND hWnd) {
  const int width = current_width;
  const int height = current_height;
  if (hWnd) {
    const int textedit_bottom = height - BOTTOM_AREA - END_PADDING;
    const int textedit_right = width - END_PADDING;
    const int button_top = textedit_bottom + END_PADDING;
    const int button2_top = button_top + BUTTON_HEIGHT + INTRA_PAD;
    const int buttoncol2 = STATIC_LEFT + BUTTON_WIDTH + INTRA_PAD;
    const int kStatusSplit = width - 100;
    MoveWindow(hTextOut, STATIC_LEFT, STATIC_TOP, textedit_right, textedit_bottom, TRUE);
    MoveWindow(hGetInfoButton, STATIC_LEFT, button_top, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
    MoveWindow(hRefreshButton, buttoncol2, button_top, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
    MoveWindow(hClearButton, STATIC_LEFT, button2_top, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
    MoveWindow(hAboutButton, textedit_right - BUTTON_WIDTH - INTRA_PAD, button2_top, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
    if (hStatusBar) {
      SendMessageW(hStatusBar, WM_SIZE, 0, 0);
      const int kStatusParts[2] = { kStatusSplit, -1 };
      SendMessageW(hStatusBar, SB_SETPARTS, 2, (LPARAM)kStatusParts);
    }
  } else {
    return;
  }
}

std::wstring GetWinInfo() {
  std::wostringstream wostr;
  wostr << std::fixed << std::setprecision(8) << std::showbase << std::hex;
  wostr << L"(Windows NT " << GetWinVersionW() << L")\r\n"
        << L"System reported " << GetOSNameW() << L"\r\n";
  wostr << std::dec << std::endl;
  const std::wstring retval = wostr.str();
  return retval;
}

void AppendTextToEditControl(HWND hWnd, const std::wstring line) {
  const WCHAR* text = line.c_str();
  int length = GetWindowTextLength(hWnd); // Get current text length
  SendMessageW(hWnd, EM_SETSEL, (WPARAM)length, (LPARAM)length); // Set cursor at the end
  SendMessageW(hWnd, EM_REPLACESEL, FALSE, (LPARAM)text); // Append the text
}

void ShowText(HWND hWnd) {
  textout = GetWinInfo();
  AppendTextToEditControl(hTextOut, textout);
  std::wstring kNTVer = L"hawk";
  const unsigned long short_nt_ver = GetShortNTVer();
  std::wostringstream wostr;
  wostr << L"Raw NTVER: "
        << std::fixed << std::setprecision(8) << std::showbase << std::hex
        << short_nt_ver << std::dec << std::endl;
  kNTVer = wostr.str();
  std::wcout << kNTVer.c_str();
  if (hStatusBar) {
    SendMessageW(hStatusBar, SB_SETTEXT, 0, (LPARAM)kNTVer.c_str());
  }
}

//  Processes window messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//  WM_RESIZE   - Handle window resizing
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    // Handle commands sent to window via wParam
    case WM_COMMAND: {
      int wmId = LOWORD(wParam);
      // Parse the menu selections:
      switch (wmId) {
        case IDC_TEXT1:
          break;
        case IDC_GETINFO:
          ShowText(hWnd);
          break;
        case IDC_REFRESH:
          SetWindowTextW(hTextOut, kBlank);
          SendMessageW(hStatusBar, SB_SETTEXT, 0, (LPARAM)kBlank);
          ShowText(hWnd);
          break;
        case IDC_CLEAR:
        case IDM_CLEAR:
          SetWindowTextW(hTextOut, L"");
          SendMessageW(hStatusBar, SB_SETTEXT, 0, (LPARAM)kBlank);
          std::wcout << L"Cleared controls" << std::endl;
          break;
        case IDM_HELP:
          MessageBoxW(hWnd, L"No Help implemented yet", L"Help", MB_OK | MB_ICONINFORMATION);
          break;
        case IDM_ABOUT:
        case IDC_ABOUT:
          // Show "About" dialog box
          DialogBoxW(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutDlgProc);
          break;
        case IDM_EXIT:
          // Send WM_DESTROY message to close window 
          DestroyWindow(hWnd);
          break;
        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
      }
    } break;
    // Begin painting
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      // TODO: Add any drawing code that uses hdc here...
      if (hdc) {
      }
      EndPaint(hWnd, &ps);
    } break;
    case WM_CREATE: {
      InitControls(hWnd);
    } break;
    // Get/Set min/max window size
    case WM_GETMINMAXINFO: {
      // Set the minimum size for the window
      LPMINMAXINFO pMinMaxInfo = (LPMINMAXINFO)lParam;
      pMinMaxInfo->ptMinTrackSize.x = MIN_WIDTH;
      pMinMaxInfo->ptMinTrackSize.y = MIN_HEIGHT;
    } break;
    // Handle resize events
    case WM_SIZE: {
      current_width = LOWORD(lParam);
      current_height = HIWORD(lParam);
      HandleResize(hWnd);
    } break;
    // When close button is pressed
    case WM_CLOSE:
      PostQuitMessage(0); // Exit the application
      break;
    // Handle destroy message
    case WM_DESTROY:
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
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);

  bool AboutHandled = false; // Stores status of whether dialog has been handled user-wise.
  const HICON kSmallIcon = LoadIcon(GetHinstanceFromHwnd(hDlg), MAKEINTRESOURCE(IDI_SMALL));
  switch (message) {
    case WM_INITDIALOG: {
      // Set icon in titlebar of about dialog
      SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)kSmallIcon);
      SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)kSmallIcon);
      AboutHandled = true;
    } break;
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
      break;
  }

  // About dialog failed
  return (INT_PTR)AboutHandled;
}

// Grabs the HINSTANCE of a given Window's HWND
HINSTANCE GetHinstanceFromHwnd(HWND hWnd) {
  // GetWindowLongPtr is the recommended function for 64-bit compatibility
  LONG_PTR hInstancePtr = GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
  // Cast the result to HINSTANCE
  HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(hInstancePtr);

  return hInstance;
}
