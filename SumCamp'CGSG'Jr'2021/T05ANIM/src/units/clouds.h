/* FILE NAME  : clouds.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 31.07.2021
 * PURPOSE    : Clouds rendering unit.
 */

#ifndef __clouds_h_
#define __clouds_h_

#include "player_move.h"
#include "enemies_shooting.h"
#include "enviroment.h"

namespace kigl
{
  namespace units
  {
    class clouds : public unit
    {
    private:
      primitive* canvas;
      material* canvasMaterial;
      image canvasBuffer;

    public:
      clouds(anim* Ani)
      {
        // Canvas buffer creation


        // Canvas creation
        topology::base<topology::vertex::std> rect(
          topology::primitive_type::POINTS,
          { topology::vertex::std(vec3(0)) }
        );

        canvasMaterial = Ani->MaterialCreateFromImage(
          "canvasMaterial",
          material::material_data(),
          "clouds",
          "canvasTexture",
          canvasBuffer
        );

        canvas = Ani->PrimitiveCreate(rect, canvasMaterial);
      }

      ~clouds(VOID)
      {
        anim* Ani = anim::GetPtr();
        Ani->MaterialFree(canvasMaterial);
        Ani->PrimitiveFree(canvas);
      }

      VOID Response(anim* Ani) override
      {
      }

      VOID Render(anim* Ani) override
      {
        Ani->PrimitiveDraw(canvas);
      }
    };
  }
}

#endif // __clouds_h_

/* END OF 'game.h' FILE */
