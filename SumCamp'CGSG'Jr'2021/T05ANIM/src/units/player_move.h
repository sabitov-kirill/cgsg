/* FILE NAME  : player_move.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Game units declaration modules.
 */

#ifndef __player_move_h_
#define __player_move_h_

#include "../anim/anim.h"
#include <string>

namespace kigl
{
  namespace units
  {
    // Programm player_move unit class
    class player_move : public unit
    {
    private:
      model gun = model("bin/models/gun.g3dm");

      matr def = matr::RotateY(185) * matr::RotateZ(3) * matr::Scale(vec3(0.35)) * matr::Translate(vec3(2, -2, 1.5));
      matr scope = matr::RotateY(180) * matr::RotateZ(3) * matr::Scale(vec3(0.35)) * matr::Translate(vec3(1.5, -1.4, 0));

      const FLT anim_duration = 0.2;
      FLT anim_time = 0;

      BOOL is_scope = FALSE;
      BOOL is_anim = FALSE;

    public:
      player_move(anim* Ani)
      {
#if !_DEBUG
        ShowCursor(FALSE);
#endif
        SetCursorPos(400, 400);
        Ani->Camera.SetLocAtUp(vec3(0, 1, 0), vec3(0, 1, -1));
      }

      ~player_move(VOID)
      {
      }

      VOID Response(anim* Ani) override
      {
        // Always set cursor in center
#if !_DEBUG
        SetCursorPos(400, 400);
        Ani->input::mouse::Response();
#endif

        // Player moving
        if (Ani->Keys['W'] || Ani->Keys['A'] || Ani->Keys['S'] || Ani->Keys['D'])
          Ani->Camera.Move((vec3(Ani->Camera.Dir[0], 0, Ani->Camera.Dir[2]) * ((Ani->Keys['W'] - Ani->Keys['S'])) +
            vec3(Ani->Camera.Right[0], 0, Ani->Camera.Right[2]) * ((Ani->Keys['D'] - Ani->Keys['A']))) * 20 * Ani->GlobalDeltaTime);

        if (Ani->Keys[VK_CONTROL] || Ani->Keys[VK_SPACE])
          Ani->Camera.Move(vec3(0, 20 * Ani->GlobalDeltaTime, 0) * (Ani->Keys[VK_SPACE] - Ani->Keys[VK_CONTROL]));

        if (Ani->Mdx != 0)
          Ani->Camera.Rotate(vec3(0, 1, 0), Ani->Mdx * Ani->GlobalDeltaTime * 200);

        if (Ani->Mdy != 0)
          Ani->Camera.Rotate(Ani->Camera.Right, Ani->Mdy * Ani->GlobalDeltaTime * 200);

        if (Ani->KeysClick[VK_RBUTTON] && !is_scope && !is_anim)
          is_scope = TRUE, anim_time = 0;
        else if (Ani->KeysClick[VK_RBUTTON] && is_scope && !is_anim)
          is_scope = FALSE, anim_time = 0;
        anim_time += Ani->DeltaTime;
        is_anim = anim_time < anim_duration;
      }

      VOID Render(anim* Ani) override
      {
        matr m = matr
        (
          Ani->Camera.Dir[0], Ani->Camera.Dir[1], Ani->Camera.Dir[2], 0,
          Ani->Camera.Up[0], Ani->Camera.Up[1], Ani->Camera.Up[2], 0,
          Ani->Camera.Right[0], Ani->Camera.Right[1], Ani->Camera.Right[2], 0,
          Ani->Camera.Loc[0], Ani->Camera.Loc[1], Ani->Camera.Loc[2], 1
        );
        matr tr;

        if (is_anim)
          if (is_scope)
            tr = matr::Lerp(def, scope, anim_time / anim_duration);
          else
            tr = matr::Lerp(scope, def, anim_time / anim_duration);
        else
          if (is_scope)
            tr = scope;
          else
            tr = def;

        Ani->ModelDraw(gun, tr * m);
      }
    };
  }
}

#endif // __player_move_h_

/* END OF 'player_move.h' FILE */