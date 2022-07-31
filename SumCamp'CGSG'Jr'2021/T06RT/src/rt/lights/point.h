/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : point.h
 * PURPOSE     : Ray tracing project.
 *               Spot handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __point_h_
#define __point_h_

#include "light.h"

/* Project namespace */
namespace kirt
{
  /* Abstract point class. */
  class point : public light
  {
  private:
    // Attitution coefficients
    vec3 Pos;   // Lamp possition

  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - lamp possition:
     *       vec3 Possition;
     *   - attenuation radiuses: 
     *       DBL Radius1, Radius2;
     *   - lamp color:
     *       vec3 Color;
     *   - light attenuation coefficients:
     *       DBL Cc, Cl, Cq;
     */
    point( vec3 Possition, vec3 Color, DBL Cc, DBL Cl, DBL Cq ) :
      light(Color, Cc, Cl, Cq), Pos(Possition)
    {
    } // End of 'point' function

    /* Adding shading by light function.
     * ARGUMNETS:
     *   - intersection with shape:
     *       intersection *Inter;
     *   - light info:
     *       light_info *Lgt;
     * RETURNS:
     *   (vec3) shape shaded color.
     */
    DBL Shadow( intersection *Inter, light_info *Lgt ) override
    {
      // Calculate distance to lamp from intersection point
      Lgt->Color = Col;
      Lgt->Dist = Pos.Distance(Inter->P);
      Lgt->Dir = (Pos - Inter->P).Normalizing();

      // Attenuation coefficient calculation
      return min(1 / (Cc + Cl * Lgt->Dist + Cq * Lgt->Dist * Lgt->Dist), 1);
    } // End of 'Shade' function

  }; // End of 'point' class

} // End of 'kirt' namespace

#endif /* __point_h_ */

/* END OF 'point.h' FILE */