/* Kirill Sabitov, 10-6, 27.10.2020 */

#include <stdlib.h>
#include <glut.h>

#include "life.h"

/* Frame Size */
#define FRAME_H 128
#define FRAME_W 128

/* Frame Massive */
unsigned char Frame[FRAME_H][FRAME_W][3];

/* Zoom Size */
float Zoom = 5;

/* Drawing Function */
void PutPixel( int x, int y, int r, int g, int b )
{
  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

/* Redraw Function */
void Display( void )
{
  /* Game functions */
  FieldInit();
  
  /* Clear Functions */
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  /*Frame Drawing*/
  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  /* Finishing  */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}


/* Keyboard Processing Function */
void Keyboard( unsigned char key, int x, int y )
{
  if (key == 27)
    exit(0);
  if (key == '=')
    Zoom++;
  if (key == '-')
    Zoom--;

  LifeKeyboard(key, x / Zoom, y / Zoom);
}


/* Main Function */
void main( int argc, char *argv[] )
{
  /* Game functions */
  GenerateField();
  
  /* Libs Initialisation */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  /* Window Creating */
  glutInitWindowSize(FRAME_W * Zoom, FRAME_H * Zoom);
  glutCreateWindow("MY LIFE");

  /* Funks Registration */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  /* Inf Loop */
  glutMainLoop();
}