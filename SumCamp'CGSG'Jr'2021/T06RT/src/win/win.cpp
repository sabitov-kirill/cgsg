/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Ray tracing project.
 *               Window class handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "win.h"

using namespace kirt;

/* Window class constructor.
 * ARGUMENTS:
 *   - window instance:
 *       HINSTANCE hInstance;
 *   - window name:
 *       const std::string &Title;
 */
win::win( const std::string &Title ) : 
  W(100), H(100), IsInit(false), IsFullScreen(false), IsActive(false), MouseWheel(0)
{
  const char WND_CLASS_NAME[] = "Window Class CGSG Forever";

  WNDCLASS window_class;
  window_class.style = CS_VREDRAW | CS_HREDRAW;
  window_class.cbClsExtra = 0;
  window_class.cbWndExtra = sizeof(win *);
  window_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
  window_class.hCursor = LoadCursor(hInstance, IDC_CROSS);
  window_class.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  window_class.lpszMenuName = nullptr;
  window_class.hInstance = hInstance;
  window_class.lpfnWndProc = WinFunc;
  window_class.lpszClassName = WND_CLASS_NAME;

  // Register window class, check if succsess
  if (!RegisterClass(&window_class)) {
    MessageBox(nullptr, "Error register window class.", "ERROR", MB_OK);
    exit(0);
  }

  // Creating window
  HINSTANCE hInstance = GetModuleHandle(nullptr);
  hWnd = CreateWindow(
    WND_CLASS_NAME,
    Title.c_str(),
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    nullptr,
    nullptr,
    hInstance,
    reinterpret_cast<VOID *>(this));
  UpdateWindow(hWnd);
} // End of 'win::win' function

/* Window class constructor.
 * ARGUMENTS:
 *   - window instance:
 *       HINSTANCE hInstance;
 */
win::~win( VOID )
{
} // End of 'win::win' function

LRESULT CALLBACK win::WinFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  // Messages handle
  switch (Msg)
  {
  // Program only messages
  case WM_GETMINMAXINFO:
    MINMAXINFO *minmax;
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);

  // Messages, connected to win class
  default:
    // Get win class pointer, connected to programm window while creation
    win *Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));

    // Check is win object not empty, cracking messages
    if (Win != nullptr)
      switch (Msg)
      {
      // Window creation event
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;

      // Window size changing event
      case WM_SIZE:
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;

      // Backgr clearing event
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBackground((HDC)wParam);

      // Window paint event
      case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hDC;

        hDC = BeginPaint(hWnd, &ps);
        Win->OnPaint(hDC, &ps);
        EndPaint(hWnd, &ps);
        return 0;

      // Timer tick event
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;

      // Mouse wheel moved event
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (INT)(SHORT)HIWORD(wParam),
                          (UINT)(SHORT)LOWORD(wParam));
        return 0;

        case WM_KEYDOWN:
          Win->OnKey(wParam, TRUE, (INT)(SHORT)LOWORD(lParam), (UINT)HIWORD(lParam));
          return 0;

        case WM_KEYUP:
          Win->OnKey(wParam, FALSE, (INT)(SHORT)LOWORD(lParam), (UINT)HIWORD(lParam));
          return 0;

      // Mouse button down event
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        Win->OnButtonDown(FALSE,
                          (INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (UINT)(SHORT)LOWORD(wParam));

      // Mouse button double click event
      case WM_LBUTTONDBLCLK:
      case WM_RBUTTONDBLCLK:
      case WM_MBUTTONDBLCLK:
        Win->OnButtonDown(TRUE,
                          (INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (UINT)(SHORT)LOWORD(wParam));

      // Mouse button up event
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        Win->OnButtonUp((INT)(SHORT)LOWORD(lParam),
                        (INT)(SHORT)HIWORD(lParam),
                        (UINT)(SHORT)LOWORD(wParam));
        return 0;
      
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage(30);
        return 0;

      case WM_CLOSE:
        if (Win->OnClose())
          DestroyWindow(hWnd);
        return 0;
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} // End of 'win::WinFunc' function

/* Window message loop run function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
WPARAM win::Run( VOID )
{
  MSG msg;

  while (TRUE)
  {
    // Check message at window message queue
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        // Displatch message to window
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      Idle();
    }
  }
  return msg.wParam;
} // End of 'win::Run' function


/* Window full screen mode change function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::FlipFullScreen( VOID )
{
  if (!IsFullScreen)
  {
    // Set Fullscreen Mode
    HMONITOR hMon;
    MONITORINFOEX moninfo;
    RECT rc;
 
    IsFullScreen = TRUE;
 
    GetWindowRect(hWnd, &FullScreenSaveRect);
 
    hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
 
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);
 
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
 
    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    // Set Windowsed Mode
    IsFullScreen = FALSE;
 
    SetWindowPos(hWnd, HWND_NOTOPMOST,
      FullScreenSaveRect.left, FullScreenSaveRect.top,
      FullScreenSaveRect.right - FullScreenSaveRect.left, FullScreenSaveRect.bottom - FullScreenSaveRect.top,
      SWP_NOOWNERZORDER);
  }
} // End of 'win::FlipFullScreen' function

/* Getting window descriptor function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (HWND) 
 */
const HWND &win::GetWndH( VOID )
{
  return hWnd;
} // End of 'win::GetWndH' function

/* Getting window width function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT)  window size
 */
INT win::GetW( VOID )
{
  return W;
} // End  of 'win::GetW' function

/* Getting window height function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT)  window size
 */
INT win::GetH( VOID )
{
  return H;
} // End  of 'win::GetH' function

// END OF 'win.cpp' FILE