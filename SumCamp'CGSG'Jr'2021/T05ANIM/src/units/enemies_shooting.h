/* FILE NAME  : enemies_shoting.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Unit handle modules.
 */

#ifndef __enemies_shoting_h_
#define __enemies_shoting_h_

#include "../anim/anim.h"
#include <array>

const INT enem_count = 10;

namespace kigl
{
  namespace units
  {
    class enemies_shoting : public kigl::unit
    {
      class enemie
      {
      private:
        // All point to move
        std::vector<vec3> MovingPoints;

        // Moving betwen points speed
        FLT Speed;

        // Current Route
        INT CurrentTargetPoint;
        vec3 RouteStart, RouteEnd;
        DBL RouteDuration, RouteTime;
        INT Index;

        // Moving params
        const FLT Size = 2;
        const FLT PlacingRadius = 300;
        const FLT Height = 5;

      public:
        // Sphere target for intersection
        sphere Target;

        // Initializing constructor
        enemie( VOID ) : CurrentTargetPoint(0), Target(Size, vec3(0))
        {
          GenerateTargetPoints();
          StartRoute();
        }

        // Generating new route points
        VOID GenerateTargetPoints( VOID )
        {
          if (!MovingPoints.empty())
            MovingPoints.clear();

          INT point_count = mth::Rnd<INT>(3, 20);
          for (INT i = 0; i < point_count; i++)
            MovingPoints.push_back(vec3::Rnd0() * vec3(PlacingRadius, 0, PlacingRadius) + vec3(0, Height, 0));

          Speed = mth::Rnd0<FLT>() * 10 + 1;

          Target.Center = MovingPoints[0];
        }

        // Starting new route betwen 2 points
        VOID StartRoute( VOID )
        {
          if (++CurrentTargetPoint >= MovingPoints.size())
            CurrentTargetPoint = 1;

          RouteStart = MovingPoints[CurrentTargetPoint - 1];
          RouteEnd = MovingPoints[CurrentTargetPoint];

          RouteTime = 0;
          RouteDuration = !(RouteEnd - RouteStart) / Speed;
        }

        // Changing enemie possition on route
        VOID GoRoute( DBL DeltaTime )
        {
          RouteTime = mth::Clamp<FLT>(RouteTime + DeltaTime, 0, RouteDuration);
          FLT Current = RouteTime / RouteDuration;
          Target.Center = vec3
          (
            mth::Lerp<FLT>(RouteStart[0], RouteEnd[0], Current),
            Height,
            mth::Lerp<FLT>(RouteStart[2], RouteEnd[2], Current)
          );

          if (RouteTime == RouteDuration)
            StartRoute();
        }
      };

      std::array<enemie, enem_count> Enemies;
      ray PlayerRay;

      material *enem_mtl;
      primitive *sphere;
      model enem_model = model("bin/models/bear.g3dm");

    public:
      enemies_shoting( anim *Ani )
      {
        topology::sphere target_topology;
        enem_mtl = Ani->MaterialCreateNoTexture("enemie mtl", material::material_data(vec3(0.1), vec3(0.8), vec3(0), 30, 1));
        sphere = Ani->PrimitiveCreate(target_topology, enem_mtl);
      }

      ~enemies_shoting( VOID ) override
      {
        anim *Ani = anim::GetPtr();
        Ani->PrimitiveFree(sphere);
        Ani->MaterialFree(enem_mtl);
      }

      VOID Response( anim *Ani ) override
      {
        if (Ani->KeysClick[VK_LBUTTON])
        {
          PlayerRay.Dir = Ani->Camera.Dir;
          PlayerRay.Org = Ani->Camera.Loc;
          for (auto &enem: Enemies)
            if (enem.Target.Intersect(PlayerRay))
            {
              enem.GenerateTargetPoints();
              enem.StartRoute();
              break;
            }
        }

        for (auto &enem: Enemies)
          enem.GoRoute(Ani->DeltaTime);
      }

      VOID Render( anim *Ani ) override
      {
        for (auto &enem: Enemies)
        {
          static matr sc = matr::Scale(vec3(enem.Target.Rad));

          Ani->ModelDraw(enem_model, sc * matr::Translate(enem.Target.Center - vec3(0, 0.5, 0)));
        #if _DEBUG
          Ani->PrimitiveDraw(sphere, sc * matr::Translate(enem.Target.Center));
        #endif // !_DRBUG
        }
      }
    };
  }
}

#endif // !__enemies_shoting_h_

/* END OF 'enemies_shoting.h' FILE */