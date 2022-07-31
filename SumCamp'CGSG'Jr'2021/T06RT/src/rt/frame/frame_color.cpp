/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win_callbacks.cpp
 * PURPOSE     : Ray tracing project.
 *               Frame colors converting module handle.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "frame.h"

using namespace kirt;

/* Color conversation from double to dword function. 
 * ARGUMENTS:
 *   - color (0 - 1):
 *       DBL R, G, B;
 * RETURNS:
 *   (DWORD) converted color.
 */
DWORD frame::ToRGB( DBL R, DBL G, DBL B )
{
  BYTE
    r = mth::Clamp(R) * 255,
    g = mth::Clamp(G) * 255,
    b = mth::Clamp(B) * 255;

  return (r << 16 | g << 8 | b);
} // End of 'frame::ToRGB'

/* Color conversation from double to dword function. 
 * ARGUMENTS:
 *   - color (0 - 1):
 *       DBL R, G, B;
 * RETURNS:
 *   (DWORD) converted color.
 */
DWORD frame::ToRGB( vec3 RGB )
{
  BYTE
    r = mth::Clamp(RGB[0]) * 255,
    g = mth::Clamp(RGB[1]) * 255,
    b = mth::Clamp(RGB[2]) * 255;

  return (r << 16 | g << 8 | b);
} // End of 'frame::ToRGB' 

/* Color conversation from double to dword function. 
 * ARGUMENTS:
 *   - color (0 - 1):
 *       DBL R, G, B;
 * RETURNS:
 *   (DWORD) converted color.
 */
DWORD frame::ToRGB( BYTE R, BYTE G, BYTE B )
{
  BYTE
    r = mth::Clamp(R),
    g = mth::Clamp(G),
    b = mth::Clamp(B);

  return (r << 16 | g << 8 | b);
} // End of 'frame::ToRGB' function

// END OF 'win_callb.cpp' FILE