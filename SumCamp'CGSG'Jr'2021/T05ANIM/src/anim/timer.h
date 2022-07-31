/* FILE NAME:  timer.h
 * PROGRAMMER: KS6
 * DATE:       31.07.2021
 * PURPOSE:    Animation timer defenitions functions sample.
 */

#ifndef __timer_h_
#define __timer_h_

#include "../kigl.h"

 // namespace definition timer
namespace kigl
{
  // class for timer
  class timer
  {
  private:
    UINT64
      StartTime = 0,        // start of time
      OldTime = 0,          // old time
      OldTimeFPS = 0,       // old time of fps
      PauseTime = 0,    // pause time counter
      TimePerSec = 0,       // time per second
      FrameCounter = 0; // frame counter

  public:

    BOOL IsPause = FALSE; // flag of exist pause
    DBL FPS = 30,         // default fps
      GlobalTime = 0,       // global time
      GlobalDeltaTime = 0,  // global delta time
      DeltaTime = 0,        // delta time
      Time = 0;             // time

 /* Timer initializing function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
    timer(VOID)
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
    VOID Response(VOID)
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
    } /* End of 'Response' function */
  };
} /* end of 'kigl' namespace */

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */
