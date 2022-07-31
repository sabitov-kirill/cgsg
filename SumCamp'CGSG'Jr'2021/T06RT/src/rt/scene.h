/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : scene.h
 * PURPOSE     : Ray tracing project.
 *               Ray tracing scene class handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __scene_h_
#define __scene_h_

#include "shapes/shape.h"
#include "lights/light.h"

#include <vector>

/* Project namespace */
namespace kirt
{
  /* Ray tracing scene class */
  class scene
  {
  private:
    friend class raytracer;

    // Scene storage
    std::vector<shape *> Shapes;       // Scene shapes
    std::vector<light *> Lights;       // Scene lights

    // Scene params
    vec3 BackgroundColor = vec3(0);       // Background color
    enviroment Air = enviroment(1, 0.01); // Scene space enviroment illumination data
    const INT MaxRecursion = 5;           // Max illumination algorithms recursion depth

  public:
    /* Scene destructor. */
    ~scene( VOID )
    {
      for (auto sh: Shapes)
        delete sh;

      for (auto lgt: Lights)
        delete lgt;
    } // End of '~scene' function

    /* Adding shapes to scene function.
     * ARGUMENTS:
     *   - shape to add:
     *       shape *Sh;
     * RETURNS:
     *   (scene &) self reference.
     */
    scene &operator<<(shape *Sh)
    {
      Shapes.push_back(Sh);

      return *this;
    } // End of 'operator<<' function

    /* Adding lights to scene function.
     * ARGUMENTS:
     *   - shape to add:
     *       shape *Sh;
     * RETURNS:
     *   (scene &) self reference.
     */
    scene &operator<<(light *Lgt)
    {
      Lights.push_back(Lgt);

      return *this;
    } // End of 'operator<<' function

    /* Intersection with all scene shapes function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - pointer to set intersection data in:
     *       intersection *Inter;
     */
    BOOL Intersect( const ray &Ray, intersection *Inter )
    {
      intersection inter;
      intersection inter_nearest;
      inter_nearest.T = INFINITY;

      // Calculate all intersections, set nearest
      for (auto sh: Shapes)
        if (sh->Intersect(Ray, &inter) && inter.T < inter_nearest.T)
        {
          inter_nearest = inter;
        }

      // Return true if nearest intersection is not infinite.
      if (inter_nearest.T != INFINITY)
      {
        *Inter = inter_nearest;
        return TRUE;
      }
      return FALSE;
    } // End of 'Intersect' function

    /* Scene shading function.
     * ARGUMENTS:
     *   - frame ray rirection:
     *       const vec3 &RayDir;
     *   - intersection data:
     *       intersection *Inter;
     *   - shading enviroment data:
     *       const enviroment &Media;
     *   - shade weight:
     *       DBL Weight;
     *   - shading recursion level:
     *       INT &RecLevel;
     * RETUSN:
     *   (vec3) color;
     */
    vec3 Shade( const vec3 &RayDir, intersection *Inter, const enviroment &Media, DBL Weight, INT &RecLevel )
    {
      vec3 color(0);
      DBL att;
      light_info li;
      intersection Intr;
      vec3 spec, dif, amb;
      
      amb = Inter->Shp->Surface.Ka;
      
      vec3 R(Inter->N.Reflecting(RayDir));
      vec3 N(vec3::Faceforward(Inter->N, RayDir, Inter->N));

      for (auto lgt: Lights)
      {
        att = lgt->Shadow(Inter, &li);

        if (!Intersect(ray(Inter->P + li.Dir * Threshold, li.Dir), &Intr) || Intr.T + Threshold > li.Dist)
        {
          color += (Inter->Shp->Surface.Ka * att +
            li.Color * (Inter->Shp->Surface.Kd * mth::Clamp(N & li.Dir) +
                        Inter->Shp->Surface.Ks * pow(mth::Clamp(R & li.Dir),
                        Inter->Shp->Surface.Ph))) * att;
        }
        else
          color += Inter->Shp->Surface.Ka * att;
      }
      
      DBL eta1 = Media.RefractionCoef, eta2 = Inter->Shp->Envi.RefractionCoef;
      enviroment OutEnv = Inter->Shp->Envi;
      if ((RayDir & Inter->N) > 0)
        eta2 = 1, OutEnv = Air;
      
      ray Rray = ray(Inter->P + R * Threshold, R);
      vec3 T = (RayDir - N * (RayDir & N)) * eta2 / eta1 -
                N * sqrt(1 - (1 - (N & RayDir) * (N & RayDir) * eta2 * eta2 / (eta1 * eta1)));
      ray Tray = ray(Inter->P + T * Threshold, T);

      return vec3::Clamp
      (
        color * Weight * amb +
        Trace(Tray, OutEnv, Weight * Inter->Shp->Surface.Kt, RecLevel) * exp(-Inter->T * Media.DecayCoef) * Inter->Shp->Surface.Kt +
        Trace(Rray, OutEnv, Weight * Inter->Shp->Surface.Kr, RecLevel) * exp(-Inter->T * Media.DecayCoef) * Inter->Shp->Surface.Kr
      );
    } // End of 'Shade' function

    /* Scene tracing function.
     * ARGUMENTS:
     *   - ray to trace:
     *       const ray &R;
     *   - enviroment illumintaion data:
     *       const enviroment &Env;
     *   - shade weight:
     *       DBL Weight;
     *   - current reursion depth parametr:
     *       INT CurrentRecursion;
     * RETURNS:
     *   (vec3) color;
     */
    vec3 Trace( const ray &R, const enviroment &Env, DBL Weight, INT &CurrentRecursion )
    {
      vec3 color = BackgroundColor;
      intersection Intr;
      if (CurrentRecursion < MaxRecursion && Weight > Threshold)
      {
        CurrentRecursion++;
        if (Intersect(R, &Intr))
        {
          if (!Intr.IsN)
            Intr.Shp->GetNormal(&Intr);
          if (!Intr.IsP)
            Intr.P = R(Intr.T);
          
          color = Shade(R.Dir, &Intr, Env, Weight, CurrentRecursion);
        }
        CurrentRecursion--;
      }
      return color;
    } // End of 'Trace' function

  }; // End of 'scene' class

} // End of 'kirt' class

#endif // !__scene_h_

// END OF 'scene.h' FILE