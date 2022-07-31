/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : triangle.h
 * PURPOSE     : Ray tracing project.
 *               Triangle handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "shape.h"

/* Math library namespace */
namespace kirt
{
  /* Sphere handle class */
  // class triangle : public shape
  // {
  // public:
  //   // Triangle vertices
  //   vec3 V0, V1, V2;
  //   mutable vec3 V0V1, V0V2;
  // 
  //   /* Class constructor.
  //    * ARGUMENTS:
  //    *   - radius:
  //    *       DBL Radius;
  //    *   - center:
  //    *       vec3<DBL> Center;
  //    *   - shape surface data:
  //    *       const surface &Surface;
  //    */
  //   triangle( vec3 Vertex0, vec3 Vertex1, vec3 Vertex2, const surface &Surface ) : shape(Surface), V0(Vertex0), V1(Vertex1), V2(Vertex2)
  //   {
  //   } // End of 'triangle' function
  // 
  //   /* Shape and ray intersection function.
  //    * ARGUMENTS:
  //    *   - ray:
  //    *       const ray<DBL> &Ray;
  //    *   - veariable to set intersection point in:
  //    *       intersection<DBL> *Inter;
  //    * RETURNS:
  //    *   (BOOL) intersection flag.
  //    */
  //   BOOL Intersect( const ray &Ray, intersection *Inter ) const override
  //   {
  //     DBL u, v;
  // 
  //     V0V1 = V1 - V0;
  //     V0V2 = V2 - V0;
  //     vec3 pvec = Ray.Dir % V0V2;
  //     FLT det = V0V1 & pvec;
  // 
  //     // if the determinant is negative the triangle is backfacing
  //     // if the determinant is close to 0, the ray misses the triangle
  //     if (det < Threshold)
  //       return FALSE; 
  // 
  //     // ray and triangle are parallel if det is close to 0
  //     if (fabs(det) < Threshold)
  //       return FALSE; 
  //     FLT invDet = 1 / det; 
  // 
  //     vec3 tvec = Ray.Org - V0; 
  //     u = (tvec & pvec) * invDet;
  //     if (u < 0 || u > 1)
  //       return FALSE; 
  // 
  //     vec3 qvec = tvec % V0V1;
  //     v = (Ray.Dir & qvec) * invDet; 
  //     if (v < Threshold || u + v > 1)
  //       return FALSE; 
  // 
  //     Inter->T = (V0V2 & qvec) * invDet; 
  //     Inter->P = Ray(Inter->T);
  //     Inter->IsP = TRUE;
  //     Inter->Shp = const_cast<triangle *>(this);
  //     return TRUE;
  //   } // End of 'Intersect' function
  // 
  //   /* Shape and ray intersection getting succses flag function.
  //    * ARGUMENTS:
  //    *   - ray:
  //    *       const ray<type> &Ray;
  //    * RETURNS:
  //    *   (BOOL) intersection flag.
  //    */
  //   BOOL IsIntersect( const ray &Ray ) const override
  //   {
  //     DBL u, v;
  // 
  //     V0V1 = V1 - V0;
  //     V0V2 = V2 - V0;
  //     vec3 pvec = Ray.Dir % V0V2;
  //     FLT det = V0V1 & pvec;
  // 
  //     // if the determinant is negative the triangle is backfacing
  //     // if the determinant is close to 0, the ray misses the triangle
  //     if (det < Threshold)
  //       return FALSE; 
  // 
  //     // ray and triangle are parallel if det is close to 0
  //     if (fabs(det) < Threshold)
  //       return FALSE; 
  //     FLT invDet = 1 / det; 
  // 
  //     vec3 tvec = Ray.Org - V0; 
  //     u = (tvec & pvec) * invDet;
  //     if (u < 0 || u > 1)
  //       return FALSE; 
  // 
  //     vec3 qvec = tvec % V0V1;
  //     v = (Ray.Dir & qvec) * invDet; 
  //     if (v < Threshold || u + v > 1)
  //       return FALSE; 
  // 
  //     return TRUE;
  //   } // End of 'IsIntersect' function
  // 
  //   /* Evaluate normal function. 
  //    * ARGUMENTS:
  //    *   - pointer to intersection:
  //    *       intersection *Inter;
  //    * RETURNS: None.
  //    */
  //   VOID GetNormal( intersection *Inter ) override
  //   {
  //     Inter->N = (V0V1 % V0V2).Normalizing();
  //   } // End of 'GetNormal' function
  // 
  // }; // End of 'triangle' class

/* Triangle intersection class */
  class triangle : public shape
  {
  public:
    vec3 N;      // Plane normal
    DBL D;       // Plane coefficient
    vec3 U1, V1; // triangle
    DBL u0, v0;  // Triangle coefficients

    /* Class constructor */
    triangle( vec3 P0, vec3 P1, vec3 P2, const surface &Surface, const enviroment &Enviroment = {} ) :
      shape(Surface, Enviroment)
    {
      N = ((P1 - P0) % (P2 - P0)).Normalizing();
      vec3 M0 = P0, P;
      D = N[0] * M0[0] + N[1] * M0[1] + N[2] * M0[2];
      P = vec3(D / N[0], D / N[1], D / N[2]);

      vec3 r = P - P0, s1 = P1 - P0, s2 = P2 - P0;
      DBL s12 = s1 & s1, s22 = s2 & s2;

      U1 = ((s1 * s22) - (s2 * (s1 & s2))) / ((s12 * s22) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1; 

      V1 = ((s2 * s12) - (s1 * (s1 & s2))) / ((s12 * s22) - (s1 & s2) * (s1 & s2));
      v0 = P0 & V1; 
    } /* End of 'triangle' function */

    /* Is intersection exist function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     * RETURNS: (TRUE) if intersected, FALSE otherwise.
     */
    BOOL IsIntersect( const ray &R ) const override
    {
      DBL t = (D - (N & R.Org)) / (N & R.Dir);
      if (t < Threshold)
        return FALSE;

      vec3 P = R(t);
      
      DBL u = (P & U1) - u0;
      DBL v = (P & V1) - v0;
      if (u >= Threshold && u <= 1 && v >= Threshold && v <= 1 && (u + v) <= 1)
        return TRUE;
      return FALSE;
    } // End of 'IsIntersected' function

    /* Find intersection between ray and plane function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - pointer to intersection type:
     *       intersection *Inter;
     * RETURNS:
     *   (BOOL) TRUE if intersection exist, FALSE otherwise.
     */
    BOOL Intersect( const ray &R, intersection *Inter ) const override
    {
      Inter->T = (D - (N & R.Org)) / (N & R.Dir);
      if (Inter->T < Threshold)
        return FALSE;

      Inter->P = R(Inter->T);
      
      DBL u = (Inter->P & U1) - u0;
      DBL v = (Inter->P & V1) - v0;
      if (u >= Threshold && v >= Threshold && (u + v) <= 1)
      {
        Inter->Shp = const_cast<triangle *>(this);
        return TRUE;
      }
      return FALSE;
    } /* End of 'Intersection' function */

    /* Get noramal function.
     * ARGUMENTS:
     *   - pointer to intersection results class:
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intersection *I ) override
    {
      I->N = N;
    } /* End of 'GetNormal' function */
  }; /* End of 'triangle' class */

} // End of 'kirt' namespace

#endif /* __triangle_h_ */

/* END OF 'triangle.h' FILE */