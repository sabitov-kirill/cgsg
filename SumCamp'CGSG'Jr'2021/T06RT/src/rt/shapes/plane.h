/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : plane.h
 * PURPOSE     : Ray tracing project.
 *               Plane handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __plane_h_
#define __plane_h_

#include "shape.h"

/* Math library namespace */
namespace kirt
{
  /* Sphere handle class */
  class plane : public shape
  {
  public:
    vec3 N; // Normal to plane
    DBL D;  // Normal distance to plane

    /* Class constructor.
     * ARGUMENTS:
     *   - radius:
     *       vec3 Normal;
     *   - distance:
     *       DBL T;
     *   - shape surface data:
     *       const surface &Surface;
     *   - shape enviroment:
     *       const enviroment &Enviroment;
     */
    plane( vec3 Normal, DBL T, const surface &Surface, const enviroment &Enviroment = {} ) :
      shape(Surface, Enviroment), N(Normal.Normalizing()), D(T)
    {
    } // End of 'plane' function

    /* Ray intersection function. 
     * ARGUMENTS:
     *   - ray:
     *       const ray<DBL> &Ray;
     *   - veariable to set intersection point in:
     *       intersection<DBL> *Inter;
     * RETURNS:
     *   (BOOL) intersection flag.
     */
    BOOL Intersect( const ray &Ray, intersection *Inter ) const override
    {
      DBL nd = Ray.Dir & N;
      if (fabs(nd) < Threshold)
        return FALSE;

      Inter->T = -((Ray.Org & N) - D) / nd;
      if (Inter->T < Threshold)
        return FALSE;
      
      Inter->P = Ray(Inter->T);
      Inter->IsP = TRUE;
      Inter->Shp = const_cast<plane *>(this);
      return TRUE;
    } // End of 'Intersect' function

    /* Shape and ray intersection getting succses flag function.
     * ARGUMENTS:
     *   - ray:
     *       const ray<type> &Ray;
     * RETURNS:
     *   (BOOL) intersection flag.
     */
    BOOL IsIntersect( const ray &Ray ) const override
    {
      DBL nd = Ray.Dir & N;
      if (fabs(nd) < Threshold)
        return FALSE;

      DBL t = -((Ray.Org & N) - D) / nd;
      if (t < Threshold)
        return FALSE;
      
      return TRUE;
    } // End of 'IsIntersect' function

    /* Evaluate normal function. 
     * ARGUMENTS:
     *   - pointer to intersection:
     *       intersection *Inter;
     * RETURNS: None.
     */
    VOID GetNormal( intersection *Inter ) override
    {
      Inter->N = N;
      Inter->IsN = TRUE;
    } // End of 'GetNormal' function

  }; // End of 'plane' class

} // End of 'kirt' namespace

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */