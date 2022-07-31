/* FILE NAME  : unit.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 31.07.2021
 * PURPOSE    : Base unit handle module.
 */

#ifndef __unit_h_
#define __unit_h_

#include "../kigl.h"

namespace kigl
{
  // Forward declaration
  class anim;

  // Units base class
  class unit
  {
  public:
    /* Default deconstructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual ~unit( VOID )
    {
    } /* End of '~unit' functiion */

    /* Response function.
     * ARGUMENTS: 
     *   - unitation context:
     *       unit *Ani
     * RETURNS: None.
     */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' functiion */

    /* Render function
     * ARGUMENTS: 
     *   - unitation context:
     *       unit *Ani
     * RETURNS: None.
     */
    virtual VOID Render( anim *Ani )
    {
    } /* End of 'Render' functiion */
  };
}

#endif // !__unit_h_

// END OF 'unit.h' FILE