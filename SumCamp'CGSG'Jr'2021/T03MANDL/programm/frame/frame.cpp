/* FILE NAME  : frame.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Programm frame buffer handle module.
 */

#include "frame.h"

frame::frame() : PrivateW(0), PrivateH(0), Buffer(nullptr), W(PrivateW), H(PrivateH)
{
}

frame::frame(int W, int H) : PrivateW(W), PrivateH(H), Buffer(new unsigned char[W * H * 4]), W(PrivateW), H(PrivateH)
{
}

frame::~frame()
{
  if (Buffer != nullptr)
    delete[] Buffer;
}

void frame::Resize( int W, int H )
{
  this->PrivateW = W;
  this->PrivateW = H;

  if (Buffer != nullptr)
    delete[] Buffer;

  Buffer = new unsigned char[PrivateW * PrivateH * 4];
}

void frame::Clear( void )
{
  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

void frame::Render( void )
{
  glDrawPixels(PrivateW, PrivateH, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Buffer);
  glRasterPos2d(-1, 1);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void frame::CopyBuffer( const frame &FrameToCopy )
{
  // Check if old buffer exist
  if (Buffer != nullptr)
    delete[] Buffer;

  // Set new size and allocate memory
  PrivateW = FrameToCopy.W;
  PrivateH = FrameToCopy.H;
  Buffer = new unsigned char[PrivateW * PrivateH *4];

  // Copy pixels
  for (int i = 0; i < PrivateW * PrivateH *4; i++)
    Buffer[i] = FrameToCopy.Buffer[i];
}

void frame::SetPixel( int X, int Y, unsigned char r, unsigned char g, unsigned char b )
{
  if (X >= 0 && X < PrivateW &&
      Y >= 0 && Y < PrivateH)
  {
    Buffer[(Y * PrivateW + X) * 4 + 0] = r;
    Buffer[(Y * PrivateW + X) * 4 + 1] = g;
    Buffer[(Y * PrivateW + X) * 4 + 2] = b;
  }
}

frame & frame::operator= (const frame &Frame)
{
  PrivateW = Frame.W;
  PrivateH = Frame.H;
  Buffer = Frame.Buffer;
  return *this;
}

/* END OF 'frame.cpp' FILE */