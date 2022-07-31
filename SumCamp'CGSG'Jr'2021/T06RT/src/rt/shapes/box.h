/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : box.h
 * PURPOSE     : Ray tracing project.
 *               Box handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __box_h_
#define __box_h_

#include "shape.h"

/* Math library namespace */
namespace kirt
{
  /* Box handle class */
  class box : public shape
  {
  public:
    // Box min and max points
    vec3 Min, Max;

    /* Class constructor.
     * ARGUMENTS:
     *   - min and max box points:
     *       vec3 Min, Max;
     *   - shape surface data:
     *       const surface &Surface;
     *   - shape enviroment:
     *       const enviroment &Enviroment;
     */
    box( vec3 Min, vec3 Max, const surface &Surface, const enviroment &Enviroment = {} ) :
      shape(Surface, Enviroment), Min(Min), Max(Max)
    {
    } // End of 'box' function

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
      INT Ind = 1, ind = 0;
      DBL tnear = -INFINITY, tfar = INFINITY, t0, t1;

      // X axis
      if (fabs(Ray.Dir[0]) < Threshold)
        if (Min[0] > Ray.Org[0] || Ray.Org[0] > Max[0])
          return FALSE;
      
      tnear = (Min[0] - Ray.Org[0]) / Ray.Dir[0];
      tfar = (Max[0] - Ray.Org[0]) / Ray.Dir[0];
      
      if (tnear > tfar)
        mth::Swap(tnear, tfar), Ind = 0;

      // Y axis
      if (fabs(Ray.Dir[1]) < Threshold)
        if (Min[1] > Ray.Org[1] || Ray.Org[1] > Max[1])
          return FALSE;
      
      t0 = (Min[1] - Ray.Org[1]) / Ray.Dir[1];
      t1 = (Max[1] - Ray.Org[1]) / Ray.Dir[1];
      ind = 3;
      if (t0 > t1)
        mth::Swap(t0, t1), ind = 2;
      if (t0 > tnear)
        tnear = t0, Ind = ind;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar || tfar < 0)
        return FALSE;

      // Z axis
      if (fabs(Ray.Dir[2]) < Threshold)
        if (Min[3] > Ray.Org[2] || Ray.Org[2] > Max[2])
          return FALSE;
      
      t0 = (Min[2] - Ray.Org[2]) / Ray.Dir[2];
      t1 = (Max[2] - Ray.Org[2]) / Ray.Dir[2];
      ind = 5;
      if (t0 > t1)
        mth::Swap(t0, t1), ind = 4;
      if (t0 > tnear)
        tnear = t0, Ind = ind;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar || tfar < 0)
        return FALSE;

      Inter->T = tnear;
      Inter->P = Ray(Inter->T);
      Inter->IsP = TRUE;
      Inter->I[0] = Ind;
      Inter->Shp = const_cast<box *>(this);

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
      INT Ind = 1, ind = 0;
      DBL tnear = -INFINITY, tfar = INFINITY, t0, t1;

      // X axis
      if (fabs(Ray.Dir[0]) < Threshold)
        if (Min[0] > Ray.Org[0] || Ray.Org[0] > Max[0])
          return FALSE;
      
      tnear = (Min[0] - Ray.Org[0]) / Ray.Dir[0];
      tfar = (Max[0] - Ray.Org[0]) / Ray.Dir[0];
      
      if (tnear > tfar)
        mth::Swap(tnear, tfar), Ind = 0;

      // Y axis
      if (fabs(Ray.Dir[1]) < Threshold)
        if (Min[1] > Ray.Org[1] || Ray.Org[1] > Max[1])
          return FALSE;
      
      t0 = (Min[1] - Ray.Org[1]) / Ray.Dir[1];
      t1 = (Max[1] - Ray.Org[1]) / Ray.Dir[1];
      ind = 3;
      if (t0 > t1)
        mth::Swap(t0, t1), ind = 2;
      if (t0 > tnear)
        tnear = t0, Ind = ind;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar || tfar < 0)
        return FALSE;

      // Z axis
      if (fabs(Ray.Dir[2]) < Threshold)
        if (Min[3] > Ray.Org[2] || Ray.Org[2] > Max[2])
          return FALSE;
      
      t0 = (Min[2] - Ray.Org[2]) / Ray.Dir[2];
      t1 = (Max[2] - Ray.Org[2]) / Ray.Dir[2];
      ind = 5;
      if (t0 > t1)
        mth::Swap(t0, t1), ind = 4;
      if (t0 > tnear)
        tnear = t0, Ind = ind;
      if (t1 < tfar)
        tfar = t1;
      if (tnear > tfar || tfar < 0)
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
      const static vec3 Normals[6] =
      {
        vec3(1, 0, 0), vec3(-1,  0,  0),
        vec3(0, 1, 0), vec3( 0, -1,  0),
        vec3(0, 0, 1), vec3( 0,  0, -1),
      };

      Inter->N = Normals[Inter->I[0]];
      Inter->IsN = TRUE;
    } // End of 'GetNormal' function

  }; // End of 'box' class

} // End of 'kirt' namespace

#endif /* __box_h_ */

/* END OF 'box.h' FILE */