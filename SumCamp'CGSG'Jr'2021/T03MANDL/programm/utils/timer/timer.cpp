/* FILE NAME  : timer.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Timer handle module.
 */

#include "timer.h"

timer::timer() : 
  OldTime(0), StartTime(-1), FPSTime(0), FrameCount(0), 
  GlobalTime(0), FPS(0), DeltaTime(0)
{
}

void timer::Response( void )
{
  long t;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = t;
  GlobalTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
    FPSTime = t;
  }

  DeltaTime = GlobalTime - OldTime;
  OldTime = GlobalTime;
}

/* END OF 'timer.cpp' FILE */