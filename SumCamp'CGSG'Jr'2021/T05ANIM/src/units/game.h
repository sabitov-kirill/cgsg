/* FILE NAME  : game.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Game units declaration modules.
 */

#ifndef __game_h_
#define __game_h_

#include "player_move.h"
#include "enemies_shooting.h"
#include "enviroment.h"

namespace kigl
{
  namespace units
  {
    // Programm game unit class
    class game : public unit
    {
    private:
      player_move Move;
      enemies_shoting Shooter;
      enviroment Env;

    public:
      game( anim *Ani ) : Move(Ani), Shooter(Ani), Env(Ani)
      {
      }

      ~game( VOID )
      {
      }

      VOID Response( anim *Ani ) override
      {
        Env.Response(Ani);
        Move.Response(Ani);
        Shooter.Response(Ani);
      }

      VOID Render( anim *Ani ) override
      {
        Env.Render(Ani);
        Move.Render(Ani);
        Shooter.Render(Ani);

        static DBL ReloadTime = 3;
        if ((ReloadTime += Ani->DeltaTime) > 3)
        {
          std::string title;
          title += "Window With Animation System Included.";
          title += " FPS - ";
          title += std::to_string(Ani->FPS);
          SetWindowText(Ani->GetWndH(), title.c_str());

          ReloadTime = 0;
        }
      }
    };
  }
}

#endif // __game_h_

/* END OF 'game.h' FILE */