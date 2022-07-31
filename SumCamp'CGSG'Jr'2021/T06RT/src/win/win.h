/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.h
 * PURPOSE     : Ray tracing project.
 *               Window class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __win_h_
#define __win_h_

#include "../def.h"
#include <string>

namespace kirt
{
  // Window class declaration
  class win
  {
  protected:
    HWND hWnd;           // Window handle
    INT W, H;            // Window size
    HINSTANCE hInstance; // Application handle

    INT MouseWheel;      // Mouse wheel state

  private:
    // Window messgaes handle function
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

    const INT InitTimer = 0;      // Timer to call initialisation
    const INT ResponseTimer = 30; // Every frame response call timer

    BOOL IsInit;             // Window initialised flag
    BOOL IsFullScreen;       // Fullscreen or windowed mode
    RECT FullScreenSaveRect; // Window rectangle

    // Overridable callbacks, to call in message loop
    virtual VOID Init( VOID );
    virtual VOID Close( VOID );
    virtual VOID Resize( VOID );
    virtual VOID Timer( VOID );
    virtual VOID Activate( VOID );
    virtual VOID Idle( VOID );
    virtual VOID Erase( HDC hDC );
    virtual VOID Paint( HDC hDC );
    virtual VOID KeyPressed( UINT Key );

  public:
    // Window active state
    BOOL IsActive;

    /* Window class constructor.
     * ARGUMENTS:
     *   - window name:
     *       const std::string &Title;
     */
    win( const std::string &Title = "Default Window" );
    // Window destructor
    virtual ~win( VOID );

    // Message loop running function. Runs programm
    WPARAM Run( VOID );
    // Flipping Fullscreen or windowed mode
    VOID FlipFullScreen( VOID );
    // Getting window descriptor function
    const HWND &GetWndH( VOID );
    // Getting window width function
    INT GetW( VOID );
    // Getting window height function
    INT GetH( VOID );

  private:
    // Messages cracks
    BOOL OnCreate( CREATESTRUCT *CS );
    VOID OnSize( UINT State, INT W, INT H );
    VOID OnTimer( INT Id );
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );
    BOOL OnEraseBackground( HDC hDC );
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    BOOL OnClose( VOID );
    VOID OnDestroy( VOID );
    VOID OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags );
    VOID OnButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys );
    VOID OnButtonUp( INT X, INT Y, UINT Keys );
  };
}

#endif // !__win_h_

// END OF '' FILE