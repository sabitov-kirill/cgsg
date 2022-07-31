/* FILE NAME  : cmpl.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Complex numbers type definition module.
 */

struct cmpl
{
  double Re, Im;

  cmpl( void );
  cmpl( double Imaginary, double Real );

  cmpl operator+ (const cmpl &C) const;
  cmpl operator* (const cmpl &C) const;
  double operator~ ( void );

  int Mandel( void );
  int Mandel( cmpl C );
  int Julia( cmpl C );
};

/* END OF 'cmpl.cpp' FILE */