/* FILE NAME  : win.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 06.03.2022
 * PURPOSE    : Window handle class declaration module.
 */

#ifndef __win_h_
#define __win_h_

#include <windows.h>

#include "../res/resource.h"

// Window class declaration
class win {
    protected:
        HWND hWnd;           // Window handle
        INT W, H;            // Window size
        HINSTANCE hInstance; // Application handle

        INT MouseWheel;      // Mouse wheel state

    private:
        // Window messgaes handle function
        static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                         WPARAM wParam, LPARAM lParam);

        const INT InitTimer = 0;      // Timer to call initialisation
        const INT ResponseTimer = 30; // Every frame response call timer

        BOOL IsInit;             // Window initialised flag
        BOOL IsFullScreen;       // Fullscreen or windowed mode
        RECT FullScreenSaveRect; // Window rectangle

        // Overridable callbacks, to call in message loop
        virtual VOID Init(VOID);
        virtual VOID Close(VOID);
        virtual VOID Resize(VOID);
        virtual VOID Timer(VOID);
        virtual VOID Activate(VOID);
        virtual VOID Hotkey(INT HotkeyID);
        virtual VOID KeyboardClick(INT KeyCode);
        virtual VOID Idle(VOID);
        virtual VOID Erase(HDC hDC);
        virtual VOID Paint(HDC hDC);

    public:
        // Window active state
        BOOL IsActive;

        // Window constructor
        win(HINSTANCE hInstance = GetModuleHandle(nullptr), const char *Title = "Default Window", BOOL IsShowed = false );
        // Window destructor
        virtual ~win(VOID);

        // Message loop running function. Runs programm
        WPARAM Run(VOID);
        // Flipping Fullscreen or windowed mode
        VOID FlipFullScreen(VOID);
        // Getting window descriptor function
        const HWND &GetWndH(VOID);
        // Getting window width function
        INT GetW(VOID);
        // Getting window height function
        INT GetH(VOID);

    private:
        // Messages cracks
        BOOL OnCreate(CREATESTRUCT *CS);
        VOID OnSize(UINT State, INT W, INT H);
        VOID OnTimer(INT Id);
        VOID OnMouseWheel(INT X, INT Y, INT Z, UINT Keys);
        VOID OnButtonDown(BOOL IsDblClick, INT X, INT Y, UINT Keys);
        VOID OnButtonUp(INT X, INT Y, UINT Keys);
        BOOL OnEraseBackground(HDC hDC);
        VOID OnPaint(HDC hDC, PAINTSTRUCT *PS);
        VOID OnActivate(UINT Reason, HWND hWndActDeact, BOOL IsMinimized);
        VOID OnHotkey(INT HotkeyID, UINT HotKeyModifiers, UINT VirtualKey);
        VOID OnKeyboardClick(INT KeyCode, UINT Params);
        BOOL OnClose(VOID);
        VOID OnDestroy(VOID);
};

#endif // !__win_h_

// END OF '' FILE