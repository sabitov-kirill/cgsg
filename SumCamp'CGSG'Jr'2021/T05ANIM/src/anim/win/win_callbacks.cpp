/* FILE NAME  : win_callb.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Window virtual callback declaration module.
 */

#include "win.h"

using namespace kigl;

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

// END OF 'win_callb.cpp' FILE