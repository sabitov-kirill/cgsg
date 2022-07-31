#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <glut.h>

#include "WARM.h"

/* Frame Size */
int
  FrameW = 973,
  FrameH = 568;

/* Frame Massive */
unsigned char *Frame;

/* Zoom Size */
float Zoom = 2;

/* Drawing Function */
void PutPixel( int x, int y, int r, int g, int b )
{
  if (x < 0 || x >= FrameW || y < 0 || y >= FrameH)
    return;

  Frame[(y * FrameW + x) * 3 + 0] = b;
  Frame[(y * FrameW + x) * 3 + 1] = g;
  Frame[(y * FrameW + x) * 3 + 2] = r;
}

/* Drawing ellement function */
void PutElement( int x, int y, int r, int g, int b )
{
  int i, j;

  for (i = 0; i < ELEMENT_H; i++)
    for (j = 0; j < ELEMENT_W; j++)
    {
      if (i == 0 || j == 0|| i == ELEMENT_H - 1 || j == ELEMENT_W - 1)
        PutPixel(x + i, y + j, r - 10, g - 10, b - 10);
      else 
        PutPixel(x + i, y + j, r, g, b);
    }
}

/* Redraw Function */
void Display( void )
{
  /* Game Functions */
  FieldInit();

  /* Clear Functions */
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  /*Frame Drawing*/
  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  glDrawPixels(FrameW, FrameH, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  /* Finishing  */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}


/* Keyboard Processing Function */
void Keyboard( unsigned char key, int x, int y )
{
  WarmKeyboard(key);
  
  if (key == 27)
    exit(0);
}

/* Frame array reallocation function */
void Resize( int W, int H )
{
  FrameW = W / Zoom;
  FrameH = H / Zoom;

  free(Frame);
  Frame = malloc(FrameW * FrameH * 3 + 1, 1);
  memset(Frame, 0, FrameW * FrameH * 3);
}

/* Main Function */
void main( int argc, char *argv[] )
{
  LoadFont();
  GameStart();

  /* Libs Initialisation */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  /* Window Creating */
  glutInitWindowSize(FrameW * Zoom, FrameH * Zoom);
  glutCreateWindow("WARM");

  /* Funks Registration */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Resize);

  /* Inf Loop */
  glutMainLoop();
}