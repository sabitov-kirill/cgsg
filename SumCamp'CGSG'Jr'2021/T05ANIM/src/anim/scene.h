/* FILE NAME  : scene.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 31.07.2021
 * PURPOSE    : Animation scene handle module.
 */

#ifndef __scene_h_
#define __scene_h_

#include "unit.h"

namespace kigl
{
  // Animation scene class
  class scene : public unit
  {
  private:
    // Units stock
    stock<unit *> Units;

  public:
    /* Default constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    scene( anim *Ani )
    {
    } // End of 'scene' function

    /* Default deconstructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~scene( VOID ) override
    {
    } /* End of '~scene' functiion */

    /* Response function.
     * ARGUMENTS: 
     *   - sceneation context:
     *       scene *Ani
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
      Units.ForEach([Ani](unit *Uni)
        {
          Uni->Response(Ani);
        });
    } // End of 'Response' function

    /* Render function
     * ARGUMENTS: 
     *   - sceneation context:
     *       scene *Ani
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    {
      Units.ForEach([Ani](unit *Uni)
        {
          Uni->Render(Ani);
        });
    } // End of 'Render' functiion

    /* Add unit to scene function.
     * ARGUMENTS:
     *   - unit to add:
     *       unit *Uni;
     * RETURNS: None.
     */
    scene & operator<<( unit *Uni )
    {
      Units.Add(Uni);
      return *this;
    } // End of 'operator<<' function
  };
}

#endif // !__scene_h_

// END OF 'scene.h' FILE