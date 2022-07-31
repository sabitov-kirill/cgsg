/* FILE NAME  : cmpl.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Complex numbers type handle module.
 */

#include <cmath>

#include "cmpl.h"

cmpl::cmpl( void ) : Re(0), Im(0)
{
}

cmpl::cmpl( double Imaginary, double Real ) : Re(Real), Im(Imaginary)
{
}

cmpl cmpl::operator+ (const cmpl &C) const
{
  return cmpl(Re + C.Re, Im + C.Im);
}

cmpl cmpl::operator* (const cmpl &C) const
{
  return cmpl(Re * C.Re - Im * C.Im, Re * C.Im + Im * C.Re);
}

double cmpl::operator~ ( void )
{
  return Im * Im + Re * Re;
}

int cmpl::Mandel( void )
{
  int n = 0; 
  cmpl ZN = *this;

  do 
  {
    *this = ZN * ZN + *this; 
    ZN = *this;
    n++;
  } while (n < 255 && ~ZN < 4);

  return n;
}

int cmpl::Mandel( cmpl C )
{
  return Mandel();
}

int cmpl::Julia( cmpl C )
{
  int n = 0; 
  cmpl ZN = *this;

  do
  {
    ZN = ZN * ZN + C;
    n++;
  } while (n < 255 && ~ZN < 4);

  return n;
}

/* END OF 'cmpl.cpp' FILE */