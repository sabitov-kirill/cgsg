/* Kirill Sabitov, 10-6, 30.10.2020 */

#define SECURE_NO_WARNINGS

#include <math.h>

#include "compl.h"

COMPL CompleSetCompl( DBL Re, DBL Im )
{
  COMPL Z;
  Z.Re = Re;
  Z.Im = Im;
  return Z;
}

COMPL CompleAddCompl( COMPL Z1, COMPL Z2 )
{
  COMPL Z;
  Z.Re = Z1.Re + Z2.Re;
  Z.Im = Z1.Im + Z2.Im;

  return Z;
}

COMPL CompleMulCompl( COMPL Z1, COMPL Z2 )
{
  COMPL Z;
  Z.Re = Z1.Re * Z2.Re - Z1.Im * Z2.Im;
  Z.Im = Z1.Re * Z2.Im + Z2.Re * Z1.Im;

  return Z;
}

DBL CompleNorm( COMPL Z1 )
{
  return sqrt(pow(Z1.Re, 2) + pow(Z1.Im, 2)); 
}

DBL CompleNorm2( COMPL Z1 )
{
  return Z1.Re * Z1.Re + Z1.Im * Z1.Im; 
}

int Mandel( COMPL Z, COMPL C  )
{
  int n = 0; 
  COMPL ZN = Z;

  do 
  {
    ZN = CompleAddCompl(CompleMulCompl(ZN, ZN), Z);
    n++;
  } while (n < 255 && CompleNorm2(ZN) < 4);

  return n;
}

int Julia( COMPL Z, COMPL C )
{
  int n = 0; 
  COMPL ZN = Z;

  do 
  {
    ZN = CompleAddCompl(CompleMulCompl(ZN, ZN), C);
    n++;
  } while (n < 255 && CompleNorm2(ZN) < 4);

  return n;
}