/* FILE NAME  : programm.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Programm definition module.
 */

#include "string"

#include "frame/frame.h"

class programm
{
private:
  frame Frame;

  static void Render( void );
  static void InputHandle( void );
  static void ReshapeWindow( void );

public:
  // Dummy Programm contructor
  programm( const std::string Title = "Simple 2D Graphics Programm", int W = 800, int H = 800 );


  programm( const std::string Title = "Simple 2D Graphics Programm", int W, int H,
            void (*Render)());

  void Init( int ArgC, char *ArgV[] );
  void InputHandle();
};

/* END OF 'programm.cpp' FILE */