/* Sabitov Kirill, 10-6, 29.10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#include "pcx.h"

/* Frame Size */
#define FRAME_H 1000
#define FRAME_W 1500

/* Frame Massive */
unsigned char Frame[FRAME_H][FRAME_W][3];

/* Zoom Size */
float Zoom = 0.5;

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
}


/* Main Function */
void main( int argc, char *argv[] )
{  
  char FN[100];
  
  printf("Enter file name: ");
  scanf("%s", FN);
  printf("\n");
  DrawPCX(FN);
  
  /* Libs Initialisation */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  /* Window Creating */
  glutInitWindowSize(FRAME_W * Zoom, FRAME_H * Zoom);
  glutCreateWindow("PCX DRAW");

  /* Funks Registration */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  /* Inf Loop */
  glutMainLoop();
}
