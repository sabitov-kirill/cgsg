/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : timer.h
 * PURPOSE     : Ray tracing project.
 *               Timer defenitions functions sample.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 02.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __timer_h_
#define __timer_h_

#include "../def.h"

// namespace definition timer
namespace kirt
{
  // class for timer
  class timer 
  {
    private:
      UINT64
        StartTime,        // start of time
        OldTime,          // old time
        OldTimeFPS,       // old time of fps
        PauseTime = 0,    // pause time counter
        TimePerSec,       // time per second
        FrameCounter = 0; // frame counter

   public:

     BOOL IsPause = FALSE; // flag of exist pause
     DBL FPS = 30,         // default fps
         GlobalTime,       // global time
         GlobalDeltaTime,  // global delta time
         DeltaTime,        // delta time
         Time;             // time

    /* Timer initializing function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
     timer( VOID )
     {
       LARGE_INTEGER t;
      
       QueryPerformanceFrequency(&t);
       TimePerSec = t.QuadPart;
       QueryPerformanceCounter(&t);
       StartTime = OldTime = OldTimeFPS = t.QuadPart;
     } /* End of 'timer' function */

    /* Timer interframe response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
     VOID Response( VOID )
     {
       LARGE_INTEGER t;

       QueryPerformanceCounter(&t);
       /* Global time */
       GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
       GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
       /* Time with pause */
       if (IsPause)
       {
         DeltaTime = 0;
         PauseTime += t.QuadPart - OldTime;
       }
       else
       {
         DeltaTime = GlobalDeltaTime;
         Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
       }
       /* FPS */
       FrameCounter++;
       if (t.QuadPart - OldTimeFPS > TimePerSec)
       {
         FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
         OldTimeFPS = t.QuadPart;
         FrameCounter = 0;
       }
       OldTime = t.QuadPart;
     } // End of 'Response' function

  }; // End of 'Timer' class

} // End of 'kigl' namespace

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */
