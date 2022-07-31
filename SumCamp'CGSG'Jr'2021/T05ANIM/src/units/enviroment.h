/* FILE NAME  : enviroment.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Unit handle modules.
 */

#ifndef __enviroment_h_
#define __enviroment_h_

#include "../anim/anim.h"

namespace kigl
{
  namespace units
  {
    class enviroment : public kigl::unit
    {
    private:

      skysphere Sky = skysphere("bin/images/forest3.g32");

    public:
      enviroment( anim *Ani )
      {
        Ani->SkyActivate(Sky);
      }

      ~enviroment( VOID ) override
      {
      }

      VOID Response( anim *Ani ) override
      {
      }

      VOID Render( anim *Ani ) override
      {
      }
    };
  }
}

#endif // !__enviroment_h_

/* END OF 'enviroment.h' FILE */