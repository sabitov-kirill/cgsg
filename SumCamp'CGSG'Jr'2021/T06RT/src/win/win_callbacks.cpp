/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win_callbacks.cpp
 * PURPOSE     : Ray tracing project.
 *               Window virtual callbacks handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "win.h"

using namespace kirt;

/* Window Initialisation virtual callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Init( VOID )
{
} // End of 'win::Init function

/* Window Closing virtual callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Close( VOID )
{
} // End of 'win::Close function

/* Window Resize virtual callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Resize( VOID )
{
} // End of 'win::Resize function

/* Window Timer tick virtual callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Timer( VOID )
{
} // End of 'win::Timer function

/* Window Activation virtual callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Activate( VOID )
{
} // End of 'win::Activate function

/* Window message loop Idle virtual callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Idle( VOID )
{
} // End of 'win::Idle function

/* Window background Erase virtual callback function.
 * ARGUMENTS:
 *   - DC handler structure:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID win::Erase( HDC hDC )
{
} // End of 'win::Erase function

/* Window paint ability virtual callback function.
 * ARGUMENTS:
 *   - DC handler structure:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID win::Paint( HDC hDC )
{
} // End of 'win::Paint function

/* Key click virtual callback function.
 * ARGUMENTS:
 *   - clicked key number:
 *       UINT Key;
 * RETURNS: None.
 */
VOID win::KeyPressed( UINT Key )
{
} // End of 'win::KeyClick' function

// END OF 'win_callb.cpp' FILE