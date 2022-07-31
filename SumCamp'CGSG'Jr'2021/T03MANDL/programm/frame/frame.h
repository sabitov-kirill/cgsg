/* FILE NAME  : frame.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Programm frame buffer definition module.
 *              Frame buffer - 
 */

#include <glut.h>

class frame
{
private:
  int PrivateW, PrivateH;
  unsigned char *Buffer;

public:
  const int &W, &H;

  frame();
  frame( int W, int H );
  ~frame();

  void Resize( int W, int H );
  void Clear( void );
  void Render( void );

  void CopyBuffer( const frame &FrameToCopy );
  void SetPixel( int X, int Y, unsigned char r, unsigned char g, unsigned char b );

  frame & operator= (const frame &Frame);
};

/* END OF 'frame.cpp' FILE */