/* FILE NAME  : timer.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Timer definition module.
 */

#include <ctime>

struct timer
{
private:
  double OldTime;
  long StartTime, FPSTime, FrameCount;
public:
  double GlobalTime, FPS, DeltaTime;

  timer();
  void Response( void );
};

/* END OF 'timer.cpp' FILE */