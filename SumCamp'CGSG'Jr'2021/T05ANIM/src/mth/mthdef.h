/* FILE NAME  : mthdef.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Math definitions module.
 */

#ifndef __mthdef_h_
#define __mthdef_h_

#include <cmath>

#include <windows.h>

typedef double DBL;
typedef float FLT;

namespace mth
{
  // PI constant
  const DBL PI = 3.14159265358979323846;

  // Getting smallest number function
  template <typename T>
  T Min( T Num1, T Num2 )
  {
    return Num1 < Num2 ? Num1 : Num2;
  }

  // Getting max number function
  template <typename T>
  T Max( T Num1, T Num2 )
  {
    return Num1 > Num2 ? Num1 : Num2;
  }

  // Degre to radians translating function
  template <typename T>
  T Deg2Rad( T AngleInDegree )
  {
    return AngleInDegree * (PI / 180);
  }

  // Radians to degree translating function
  template <typename T>
  T Rad2Deg( T AngleInRadians )
  {
    return AngleInRadians * (180 / PI);
  }

  // Number clamp function
  template <typename T>
  T Clamp( T Num, T Min = 0, T Max = 1 )
  {
    return Num < Min ? Min : Num > Max ? Max : Num;
  }

  // Linear interpolation function
  template <typename T>
  T Lerp( T Start, T End, T Current )
  {
    return Start + (End - Start) * Current;
  }

  // Getting random number in range 0 to 1
  template <typename T>
  T Rnd0( VOID )
  {
    return static_cast<T>(rand()) / RAND_MAX;
  }

  // Getting random number in range -1 to 1
  template <typename T>
  T Rnd1( VOID )
  {
    return rand() / RAND_MAX * 2 - 1;
  }

  // Getting random number in any range
  template <typename T>
  T Rnd( INT Max )
  {
    return Rnd0<T> * Max;
  }

  // Getting random number in any range
  template <typename T>
  T Rnd( INT Min, INT Max )
  {
    return Min + (rand() % static_cast<int>(Max - Min + 1));
  }
}

#endif // !__mthdef_h_

/* END OF 'mthdef.h' FILE */
