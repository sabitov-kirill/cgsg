/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray tracing project.
 *               Mathematics library.
 *               Ray handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'mth'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_vec3.h"

/* Math library namespace */
namespace mth
{
  /* Ray handle class */
  template<class type>
    class ray
    {
    public:
      // Vectors setting ray
      vec3<type>
        Org, // Ray origin
        Dir; // Ray direction

      /* Class default constructor */
      ray( VOID )
      {
      } // End of 'ray' function

      /* Class constructor. 
       * ARGUMENTS:
       *   - ray origin:
       *       const vec3<type> &Origin;
       *   - ray direction
       *       const vec3<type> &Direction;
       */
      ray( const vec3<type> &Origin, const vec3<type> &Direction ) :
        Org(Origin), Dir(~Direction)
      {
      } // End of 'ray' fnction

      /* Obtain ray point function.
       * ARGUMENTS:
       *   - ray point parametr:
       *       type T;
       * RETURNS:
       *   (vec3) ray point.
       */
      vec3<type> Point( type T )
      {
        return Org + Dir * T;
      } // End of 'ObtainPoint' function
      /* Obtain ray point function.
       * ARGUMENTS:
       *   - ray point parametr:
       *       type T;
       * RETURNS:
       *   (vec3) ray point.
       */
      vec3<type> operator()( type T ) const
      {
        return Org + Dir * T;
      } // End of 'operator()' function

    }; // End of 'ray' class

} // End of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */