/* Kirill Sabitov, 10-6, 30.10.2020 */

#define SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <glut.h>

#include "compl.h"

/* Frame Size */
#define FRAME_H 500
#define FRAME_W 500

/* Frame Massive */
unsigned char Frame[FRAME_H][FRAME_W][3];

/* Zoom Size */
float Zoom = 1;

DBL SyncTime, FPS;

void Timer( void )
{
  long t;
  static long StartTime = -1, FPSTime, FrameCount;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = t;
  SyncTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
    FPSTime = t;
  }
}

/* Drawing Function */
void PutPixel( int x, int y, int r, int g, int b )
{
  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

void DrawMandel( int (*Func)(COMPL Z, COMPL C) )
{
  DBL x0 = -3, x1 = 3, y0 = -3, y1 = 3, xs, ys, n;
  COMPL Z, C;
  
  Timer();
  
  C = CompleSetCompl(0.38 + 0.08 * sin(SyncTime + 3) * floor(SyncTime + 3), 0.39 + 0.1 * sin(1.1 * SyncTime) * ceil(FPS / 3));

  for (ys = 0; ys < FRAME_H; ys++)
    for (xs = 0; xs < FRAME_W; xs++)
    {
      Z = CompleSetCompl((xs * (x1- x0)) / FRAME_W + x0, (ys * (y1 - y0)) / FRAME_H + y0 );

      n = Func(Z, C);

      PutPixel(xs, ys, sinh(n * n), ceil(n), n * 8);
    }
}

/* Redraw Function */
void Display( void )
{        
  DrawMandel(Julia);

  /* Clear Functions */
  glClearColor(0.35, 0.55, 0.98, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  /*Frame Drawing*/
  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  /* Finishing */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

/* Keyboard Processing Function */
void Keyboard( unsigned char key, int x, int y )
{
  if (key == 27)
    exit(0);
  if (key == 'F' || key == 'f')
    glutFullScreen();
}

/* Main Function */
void main( int argc, char *argv[] )
{ 
  /* Libs Initialisation */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  /* Window Creating */
  glutInitWindowSize(FRAME_W * Zoom, FRAME_H * Zoom);
  glutCreateWindow("MANDLE");

  /* Funks Registration */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  /* Inf Loop */
  glutMainLoop();
}