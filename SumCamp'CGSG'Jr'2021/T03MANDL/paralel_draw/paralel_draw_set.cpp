/* FILE NAME  : frame.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Programm frame buffer handle module.
 */

#include "paralel_draw.h"

frame paralel_draw::Frame;
Set paralel_draw::DrawingSet;
cmpl paralel_draw::C;

paralel_draw::paralel_draw( frame &FrameToDraw ) : 
  ThCount(std::thread::hardware_concurrency() - 1), Threads(new std::thread[ThCount])
{
  Frame = FrameToDraw;
}

void paralel_draw::DrawGroup( int StartRow, int EndRow )
{
  double x0 = -3, x1 = 3, y0 = -3, y1 = 3, xs, ys, n;

  for (ys = StartRow; ys < EndRow; ys++)
    for (xs = 0; xs < Frame.W; xs++)
    {
      cmpl Z((xs * (x1- x0)) / Frame.W + x0, (ys * (y1 - y0)) / Frame.H + y0 );

      n = DrawingSet == Mandelbrot ? Z.Mandel() : Z.Julia(C);
      Frame.SetPixel(xs, ys, n * n, n, n * 8);
    }
}

void paralel_draw::StartDrawSet( Set Set, double GlobalTime )
{
  DrawingSet = Set;
  C = cmpl(0.47 + sin(GlobalTime), 0.3 * cos(GlobalTime));

  for (int i = 0; i < ThCount; i++)
  {
    int start_y = floor(Frame.H / ThCount * i), end_y = ceil(Frame.H / ThCount * (i + 1));

    Threads[i] = std::thread(DrawGroup, start_y, end_y);
  }
}

void paralel_draw::FinishDrawSet( void )
{
  for (int i = 0; i < ThCount; i++)
    Threads[i].join();
}

/* END OF 'frame.cpp' FILE */