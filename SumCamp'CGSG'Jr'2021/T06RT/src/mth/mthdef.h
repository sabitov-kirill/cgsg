/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Ray tracing project.
 *               Mathematics library.
 *               Math base definitions module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'mth'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mthdef_h_
#define __mthdef_h_

#include <cmath>

/* Math library namespace */
namespace mth
{
  // PI constant
  const double PI = 3.14159265358979323846;

  /* Types swap function.
   * ARGUMENTS:
   *   - varables to swap:
   *       type &A, type &B;
   * RETURNS: None.
   */
  template<typename type>
  void Swap(type &A, type &B)
  {
    type tmp = B;
    B = A;
    A = tmp;
  } // End of 'Swap' function

  /* Getting smallest number function.
   * ARGUMENTS:
   *   - two numbers to sellect smallest:
   *       type Num1, type Num2;
   * RETURNS:
   *   (type) smallest number.
   */
  template <typename type>
  type Min( type Num1, type Num2 )
  {
    return Num1 < Num2 ? Num1 : Num2;
  } // End of 'Min' function

  /* Getting greates number function.
   * ARGUMENTS:
   *   - two numbers to sellect greatest:
   *       type Num1, type Num2;
   * RETURNS:
   *   (type) greatest number.
   */
  template <typename type>
  type Max( type Num1, type Num2 )
  {
    return Num1 > Num2 ? Num1 : Num2;
  } // End of 'Max' function

  /* Degre to radians translating function
   * ARGUMENTS:
   *   - angle in degrees:
   *       type AngleInDegree;
   * RETURNS:
   *   (type) number in radians.
   */
  template <typename type>
  type Deg2Rad( type AngleInDegree )
  {
    return AngleInDegree * (PI / 180);
  } // End of 'Deg2Rad' function

  /* Radians to degree translating function
   * ARGUMENTS:
   *   - angle in radians:
   *       type AngleInRadians;
   * RETURNS:
   *   (type) angle ing degrees.
   */
  template <typename type>
  type Rad2Deg( type AngleInRadians )
  {
    return AngleInRadians * (180 / PI);
  } // End of 'Rad2Deg' function

  /* Number clamp function
   * ARGUMENTS:
   *   - number to clamp:
   *       type Num;
   *   - clamp range:
   *       type Min, Max;
   * RETURNS:
   *   (type) clamped number.
   */
  template <typename type>
  type Clamp( type Num, type Min = 0, type Max = 1 )
  {
    return Num < Min ? Min : Num > Max ? Max : Num;
  } // End of 'Clamp' function

  /* Linear interpolation function
   * ARGUMENTS:
   *   - interpolation range:
   *       type Start, End;
   *   - current value (0 - 1):
   *       type Current;
   * RETURNS:
   *   (type) interpolation result.
   */
  template <typename type>
  type Lerp( type Start, type End, type Current )
  {
    return Start + (End - Start) * Current;
  } // End of 'Lerp' function

  /* Getting random number in range 0 to 1 function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (type) random number.
   */
  template <typename type = double>
  type Rnd0( VOID )
  {
    return static_cast<type>(rand()) / RAND_MAX;
  } // End of 'Rnd0' function

  /* Getting random number in range -1 to 1 function.
   * ARGMUENTS: None.
   * RETURNS:
   *   (type) random number.
   */
  template <typename type = double>
  type Rnd1( VOID )
  {
    type r = rand();
    return r / RAND_MAX * 2 - 1;
  } // End of 'Rnd1' function
}

#endif // !__mthdef_h_

/* END OF 'mthdef.h' FILE */