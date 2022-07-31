/* FILE NAME  : draw.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Drawing to frame buffer definition module.
 */

#include <thread>

#include "../programm/frame/frame.h"
#include "../math/complex/cmpl.h"

enum Set
{
  Mandelbrot,
  Julia
};

class paralel_draw
{
private:
  std::thread *Threads;
  const int ThCount;

  static frame Frame;
  static Set DrawingSet;
  static cmpl C;

  static void DrawGroup( int StartX, int StartY );

public:
  paralel_draw( frame &FrameToDraw );

  void StartDrawSet( Set DrawingSet, double GlobalTime );
  void FinishDrawSet( void );
};

/* END OF 'draw.h' FILE */