// {{NO_DEPENDENCIES}}
// For #define-ing static resources for resource script file(s).
// Used by resource.rc

// Icons
#define IDI_ABOUTWIN                101
#define IDI_SMALL                   102
#define IDI_ABOUT                   199

// App title
#define IDS_APP_TITLE               103

// Dialogs
#define IDD_ABOUTWIN_DIALOG         104
#define IDD_ABOUTBOX                105

// Menu items
#define IDM_EXIT                    200
#define IDM_ABOUT                   201
#define IDM_HELP                    202
#define IDM_CLEAR                   203

// Controls
#define IDC_ABOUTWIN                300
#define IDC_TEXT1                   301
#define IDC_GETINFO                 302
#define IDC_REFRESH                 303
#define IDC_CLEAR                   304
#define IDC_ABOUT                   305

// Main application resource
#define IDR_MAINFRAME               128

// For resources to be loaded without an ID from the system.
#ifndef IDC_STATIC
 #define IDC_STATIC                 -1
#endif // IDC_STATIC

#ifdef APP_MANIFEST
 #warning "APP_MANIFEST" should not already be defined
#else
 #define APP_MANIFEST               1
#endif // APP_MANIFEST

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
 #ifndef APSTUDIO_READONLY_SYMBOLS
  #define _APS_NO_MFC               130
  #define _APS_NEXT_RESOURCE_VALUE  129
  #define _APS_NEXT_COMMAND_VALUE   32771
  #define _APS_NEXT_CONTROL_VALUE   1000
  #define _APS_NEXT_SYMED_VALUE     110
 #endif // APSTUDIO_READONLY_SYMBOLS
#endif // APSTUDIO_INVOKED
