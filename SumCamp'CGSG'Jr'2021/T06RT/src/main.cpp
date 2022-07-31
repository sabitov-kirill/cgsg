/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Ray tracing project.
 *               Main programm module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        :
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "rt/raytracer.h"

/* Build gods colt scene function.
 * ARGUMNETS:
 *   - ray tracer:
 *       const kirt::raytracer &RT;
 * RETURNS: None.
 */
VOID BuildGodsCult( kirt::raytracer &RT )
{
  RT.Camera.SetLocAtUp(kirt::vec3(45, 30, 20), kirt::vec3(0, 9, 0), kirt::vec3(0, 1, 0));

  RT.Scene << new kirt::point(kirt::vec3(0, 50, 0), kirt::vec3(1),             20, 0.00005, 0.00000000009) <<

              new kirt::point(kirt::vec3(5, 15, 0), kirt::vec3(0.5, 0, 0),      1, 0.00000005, 0.000009) <<
              new kirt::point(kirt::vec3(-5, 15, 0), kirt::vec3(0, 0.5, 0),     1, 0.00000005, 0.000009) <<

              new kirt::point(kirt::vec3(0, 35, 5), kirt::vec3(0, 0, 0.5),      1, 0.005, 0.0000009) <<
              new kirt::point(kirt::vec3(0, 35, -5), kirt::vec3(0.5, 0.5, 0.5), 1, 0.005, 0.0000009);

  // PLANE
  RT.Scene << new kirt::plane(kirt::vec3(0, 1, 0), 0, kirt::surfaces_lib::Turquoise);;

  // RING
  {
    const INT ring_w = 10;
  
    DBL angle_addition = static_cast<DBL>(360) / ring_w;
    DBL angle = 0;
    kirt::vec3 start(3, 23, 0);
    for (INT i = 0; i < ring_w; i++, angle += angle_addition)
    {
      kirt::matr m = kirt::matr::RotateY(angle);
      RT.Scene << new kirt::sphere(0.3, m.TransformPoint(start), kirt::surfaces_lib::Ruby);
    }
  }
  
  // TOWER
  {
    INT n = 20;
  
    DBL angle_addition = 2 * mth::PI / n;
    DBL angle = 0;
    for (INT i = 0; i < n; i++, angle += angle_addition)
    {
      DBL c = (cos(angle) + 3) / 1.5;
      kirt::vec3 p1(-c, i, -c);
      kirt::vec3 p2(c, i + 1, c);
      RT.Scene << new kirt::box(p1, p2, kirt::surfaces_lib::Emerald);
    }
  }

  // COLOMNS
  {
    INT colomns_n = 15;
    DBL colomn_w = 2;

    DBL angle_addition = static_cast<DBL>(360) / colomns_n;
    DBL angle = 0;
    kirt::vec3 start(14, 0, 0);
    kirt::vec3 start1 = start - kirt::vec3(colomn_w / 2, 0, colomn_w / 2);
    kirt::vec3 start2 = start + kirt::vec3(colomn_w / 2, 12, colomn_w / 2);
    for (INT i = 0; i < colomns_n; i++, angle += angle_addition)
    {
      kirt::matr m = kirt::matr::RotateY(angle);
      RT.Scene << new kirt::box(m.TransformPoint(start1), m.TransformPoint(start2), kirt::surfaces_lib::Obsidian);
    }
  }
} // End of 'BuildGodsCult' function

/* Main programm function.
 * ARGMUNETS:
 *   - programm instance handler:
 *       HINSTANCE hInstance;
 *   - programm previous instance handler:
 *       HINSTANCE hPrevInstance;
 *   - command line pointer:
 *       CHAR *CmdLine;
 *   - window hide flag:
 *       INT ShouldShow;
 * RETURNS:
 *   (INT) System return code.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShouldShow )
{
  kirt::raytracer RT("CGSG'SumCamp'2021 Ray Tracing Rendering Window.");

  //BuildGodsCult(RT);
  RT.Camera.SetLocAtUp(kirt::vec3(-50, 25, 45), kirt::vec3(0, 0, 0), kirt::vec3(0, 1, 0));
  RT.Scene << new kirt::point(kirt::vec3(100, 15, 0), kirt::vec3(1), 1, 0.00005, 0.0000000009);
  RT.Scene << new kirt::plane(kirt::vec3(0, 0.5, 0), 0, kirt::surfaces_lib::Default);

  const INT ring_w = 10;
  
  DBL angle_addition = static_cast<DBL>(180) / ring_w;
  DBL angle = -90;
  kirt::vec3 start(100, 0, 0);
  // for (INT i = 0; i < ring_w; i++, angle += angle_addition)
  // {
  //   kirt::matr m = kirt::matr::Scale(kirt::vec3(3)) * kirt::matr::RotateY(180) * kirt::matr::Translate(start) * kirt::matr::RotateY(angle);
  //   RT.Scene << new kirt::model("bin/models/cow.obj", m, kirt::surfaces_lib::Ruby);
  // }
  RT.Scene << new kirt::sphere(5, kirt::vec3(3, 2.5, 0), kirt::surfaces_lib::PolishedGold);
  RT.Scene << new kirt::triangle(kirt::vec3(0, 1, 0), kirt::vec3(0, 0, 2.5), kirt::vec3(2.5, 0, 0), kirt::surfaces_lib::PolishedGold);

  return RT.Run();
} // End of 'WinMain' function

/* END OF 'main.cpp' FILE */