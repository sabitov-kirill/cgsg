/* FILE NAME  : t03mandl.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Mandelbrot set GLUT realisation task.
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>

#include "programm/utils/timer/timer.h"
#include "paralel_draw/paralel_draw.h"

/* Frame */
const DOUBLE ZoomX = 1, ZoomY = 1;
frame Frame(800, 800);
paralel_draw Draw(Frame);

/* Timer */
timer Timer;

/* Glut frame render function */
VOID Display( VOID )
{
  static DOUBLE time = 0;

  Timer.Response();
  time += Timer.DeltaTime;
  if (time > 0.1)
  {
    std::cout.width(5);
    std::cout.precision(1);
    std::cout << std::fixed << Timer.FPS << "\b\b\b\b\b";
    time = 0;
  }

  Draw.StartDrawSet(Julia, Timer.GlobalTime);
  Draw.FinishDrawSet();

  Frame.Clear();
  glPixelZoom(ZoomX, -ZoomY);
  Frame.Render();
} /* End of 'Display' function */

/* Keyboard handle function */
VOID Keyboard( unsigned char KeyCode, INT X, INT Y )
{
  if (KeyCode == 27)
    exit(0);
} /* End of 'Keyboard' function */

/* Main programm function*/
INT main( INT ArgC, CHAR *ArgV[] )
{
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(Frame.W * ZoomX, Frame.H * ZoomY);
  glutCreateWindow("CGSG'SummerCamp'2021 CPP Mandl");
  std::cout << "FPS: ";

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
  return 0;
} /* End of 'main' function */

/* END OF 't03mandl.cpp' FILE */