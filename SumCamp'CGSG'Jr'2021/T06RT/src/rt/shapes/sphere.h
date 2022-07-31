/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Ray tracing project.
 *               Sphere handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "shape.h"

/* Math library namespace */
namespace kirt
{
  /* Sphere handle class */
  class sphere : public shape
  {
  public:
    vec3 Center; // Sphere central point
    DBL Rad;     // Sphere radius
    DBL Rad2;    // Sphere radius pow 2

    /* Class constructor.
     * ARGUMENTS:
     *   - radius:
     *       DBL Radius;
     *   - center:
     *       vec3<DBL> Center;
     *   - shape surface data:
     *       const surface &Surface;
     *   - shape enviroment:
     *       const enviroment &Enviroment;
     */
    sphere( DBL Radius, vec3 Center, const surface &Surface, const enviroment &Enviroment = {} ) :
      shape(Surface, Enviroment), Center(Center), Rad(Radius), Rad2(Radius * Radius)
    {
    } // End of 'sphere' function

    /* Shape and ray intersection function. 
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
      vec3 a = Center - Ray.Org;
      DBL OC2 = a & a;
      DBL OK = a & Ray.Dir;
      DBL OK2 = OK * OK;

      DBL H2 = Rad - (OC2 - OK2); 
      if (H2 < 0)
        return FALSE;

      if (OC2 < Rad2)
      {
        Inter->T = OK - sqrt(H2);
        Inter->P = Ray(Inter->T);
        Inter->IsP = TRUE;
        Inter->Shp = const_cast<sphere *>(this);
        return TRUE;
      }

      if (OK < 0)
        return FALSE;

      Inter->T = OK - sqrt(H2);
      Inter->P = Ray(Inter->T);
      Inter->IsP = TRUE;
      Inter->Shp = const_cast<sphere *>(this);
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
      vec3 a = Center - Ray.Org;
      DBL OC2 = a & a;

      DBL OK = a & Ray.Dir;
      if (OK < 0)
        return FALSE;

      DBL OK2 = OK * OK;
      if (OC2 < Rad2)
        return TRUE;

      DBL H2 = Rad - (OC2 - OK2); 
      if (H2 < 0)
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
      Inter->N = (Inter->P - Center).Normalizing();
      Inter->IsN = TRUE;
    } // End of 'GetNormal' function

  }; // End of 'sphere' class

} // End of 'kirt' namespace

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */