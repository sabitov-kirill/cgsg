/* FILE NAME:  input.h
 * PROGRAMMER: KS6
 * DATE:       31.07.2021
 * PURPOSE:    Animation input defenitions functions sample.
 */

#ifndef __input_h_
#define __input_h_

#include "../kigl.h"

#pragma comment(lib, "winmm")

// namespace for input
namespace kigl 
{
  // class mouse
  class mouse 
  {
  private:
    INT &Wheel; // mouse wheel
    HWND hWnd;  // handle window discribtor

  public:
    INT Mx, My, Mz, Mdx, Mdy, Mdz; // coordinates for mouse

   /* Mouse constructor function.
    * ARGUMENTS:
    *   - window handle:
    *       HWND hWnd;
    *   - mouse wheel:
    *       int &WheelRef;
    * RETURNS: None.
    */
    mouse( HWND hWnd, INT &WheelRef ) : Wheel(WheelRef), hWnd(hWnd), 
      Mx(0), My(0), Mz(0), Mdx(0), Mdy(0), Mdz(0)
    {
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);

      Mx = pt.x, My = pt.y;

    } /* End of 'mouse' function */

   /* Mouse interframe response function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    VOID Response( VOID )
    {
      POINT pt;

      /* Obtain position */
      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);

      /* Delta (relative) values */
      Mdx = pt.x - Mx;
      Mdy = pt.y - My;

      /* Absolute values */
      Mx = pt.x;
      My = pt.y;

      /* Wheel (z) */
      Mdz = Wheel;
      Mz += Mdz;
      Wheel = 0;
    } /* End of 'Response' function */
  };

  // class for keyboard
  class keyboard 
  {  
  public:
    BYTE Keys[256];      // array of keys
    BYTE KeysOld[256];   // array of old clicked keys
    BYTE KeysClick[256]; // array of clicked keys

   /* Keyboard interframe init function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */ 
    keyboard( VOID )
    {
      auto _ = GetKeyboardState(Keys);
      memcpy(KeysOld, Keys, 256);
      memcpy(KeysClick, Keys, 256);
    }

    VOID Response( VOID )
    {
      auto _ = GetKeyboardState(Keys);
      for (INT i = 0; i < 256; i++)
      {
        Keys[i] >>= 7;
        KeysClick[i] = Keys[i] && !KeysOld[i];
      }
      memcpy(KeysOld, Keys, 256);
    } /* End of 'keyboard' function */
  };

  // class joystick
  class joystick 
  {
  public:
    BYTE 
      JBut[32], JButOld[32], JButClick[32]; // arrays for keys for joystick
    INT JPov;                               // pov of joystick
    DBL
      JX, JY, JZ, JR;                       // axis for rotate for joystick

   /* Keyboard interframe response function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */ 
    VOID Response( VOID )
    {
      if (joyGetNumDevs() > 0)
      {
        JOYCAPS jc;

        if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
        {
          JOYINFOEX ji;
      
          ji.dwSize = sizeof(JOYINFOEX);
          ji.dwFlags = JOY_RETURNALL;
          if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
          {
            for (INT i = 0; i < 32; i++)
            {
              JBut[i] = (ji.dwButtons >> i) & 1;
              JButClick[i] = JBut[i] && !JButOld[i];
              JButOld[i] = JBut[i];
            }

            JX = 2.0 * (ji.dwXpos - jc.wXmin) / (jc.wXmax - jc.wXmin) - 1;
            JY = 2.0 * (ji.dwYpos - jc.wYmin) / (jc.wYmax - jc.wYmin) - 1;
            JZ = 2.0 * (ji.dwZpos - jc.wZmin) / (jc.wZmax - jc.wZmin) - 1;
            JR = 2.0 * (ji.dwRpos - jc.wRmin) / (jc.wRmax - jc.wRmin) - 1;

            JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
          }
        }
      }
    } /* End of 'Response' function */ 

    
   /* Joystick interframe init function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */ 
    joystick( VOID )
    {
      Response();
     for (INT i = 0; i < 32; i++)
     {
       JButClick[i] = 0;
       JButOld[i] = JBut[i];
     }
    } /* End of 'joystick' function */
  };

  // class input
  class input : public keyboard, public mouse, public joystick
  {
  public:
    
   /* Input( constructor ) init function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */ 
    input( HWND hWnd, INT &WheelRef ) : mouse(hWnd, WheelRef), keyboard(), joystick()
    {
    }
    
   /* Input interframe response function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */ 
    VOID Response( VOID )
    {
      keyboard::Response();
      mouse::Response();
      joystick::Response();
    } /* End of 'Response' function */
  };
} // end of 'kigl' namespace


#endif /* __input_h_ */

/* END OF 'input.h' FILE */