/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : light.h
 * PURPOSE     : Ray tracing project.
 *               Base light handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __light_h_
#define __light_h_

#include "../shapes/shape.h"

/* Project namespace */
namespace kirt
{
  /* Light info class. */
  class light_info
  {
  public:
    vec3 Dir;   // Light source direction
    vec3 Color; // Light source color
    DBL Dist;   // Distance to light source
  };

  /* Abstract light class. */
  class light
  {
  public:
    // Light color
    vec3 Col;
    // Attenuation coefficients
    DBL Cc, Cl, Cq;

    /* Class constructor.
     * ARGUMENTS:
     *   - light color:
     *       vec3 Color;
     *   - light attenuation coefficients:
     *       DBL Cc, Cl, Cq;
     */
    light( const vec3 &Color, DBL Cc, DBL Cl, DBL Cq ) : Col(Color), Cc(Cc), Cl(Cl), Cq(Cq)
    {
    } // End of 'light' function

    /* Shade scene by light function.
     * ARGUMNETS:
     *   - intersection with shape:
     *       intersection *Inter;
     *   - light info:
     *       light_info *Lgt;
     * RETURNS:
     *   (vec3) shape shaded color.
     */
    virtual DBL Shadow( intersection *Inter, light_info *Lgt ) = 0;

  }; // End of 'light' class

} // End of 'kirt' namespace

#endif /* __light_h_ */

/* END OF 'light.h' FILE */