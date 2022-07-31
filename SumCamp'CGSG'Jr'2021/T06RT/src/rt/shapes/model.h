/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : model.h
 * PURPOSE     : Ray tracing project.
 *               Model handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __model_h_
#define __model_h_

#include "shape.h"
#include "box.h"
#include "triangle.h"
#include <vector>
#include <fstream>

/* Math library namespace */
namespace kirt
{
  /* Sphere handle class */
  class model : public shape
  {
  public:
    // Shapes setting model
    std::vector<triangle *> Polygons;
    // Model bounds
    box BoundBox;

    /* Bounf box evaluation method.
     * ARGUMENTS:
     *   - vector of vertices to calculate bound box:
     *       const std::vector<vec3> &Vert;
     * RETURNS: None.
     */
    VOID EvaluateBoundBox( const std::vector<vec3> &Vert, vec3 *MinBB, vec3 *MaxBB )
    {
      for (auto v: Vert)
      {
        *MinBB = vec3::Min(*MinBB, v);
        *MaxBB = vec3::Max(*MaxBB, v);
      }
    } // End of 'EvaluateBoundBox' function
      
    /* Class constructor.
     * ARGUMENTS:
     *   - model file name:
     *       const std::string &FileName;
     *   - model transform matrix:
     *       matr TransformMatrix;
     *   - shape surface data:
     *       const surface &Surface;
     *   - shape enviroment:
     *       const enviroment &Enviroment;
     */
    model( const std::string &FileName, matr TransformMatrix, const surface &Surface, const enviroment &Enviroment = {} ) :
      shape(surfaces_lib::Default), BoundBox(vec3(0), vec3(0), surfaces_lib::Default, {})
    {
      std::fstream f(FileName, std::fstream::in);
      std::vector<vec3> V;
      std::vector<INT> I;

      if (!f.is_open())
        return;

      // Getting vertecies and indexes from file, pushing to arrays
      CHAR Buf[1000];
      while (!f.eof())
      {
        f.getline(Buf, sizeof(Buf) - 1);

        if (Buf[0] == 'v' && Buf[1] == ' ')
        {
          FLT x, y, z;

          sscanf_s(Buf + 2, "%f%f%f", &x, &y, &z);
          V.push_back(TransformMatrix.TransformPoint(vec3(x, y, z)));
        }
        else if (Buf[0] == 'f' && Buf[1] == ' ')
        {
          INT n1, n2, n3;

          /* Read one of possible facet references */
          sscanf_s(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
            sscanf_s(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
            sscanf_s(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
            sscanf_s(Buf + 2, "%d %d %d", &n1, &n2, &n3);
          n1--;
          n2--;
          n3--;
          I.push_back(n1);
          I.push_back(n2);
          I.push_back(n3);
        }
      }
      f.close();

      // Making triangles of vecrtices and indexes
      for (INT i = 0; i < I.size(); i += 3)
      {
        triangle *tr = new triangle(V[I[i]], V[I[i + 1]], V[I[i + 2]], Surface, Enviroment);
        Polygons.push_back(tr);
      }

      // Evaluating model boundbox
      vec3 min, max;
      EvaluateBoundBox(V, &min, &max);
      BoundBox = box(min, max, surfaces_lib::Default, {});
    } // End of 'model' function

    /* Class destructor. */
    ~model( VOID )
    {
      for (auto poly: Polygons)
        delete poly;
    } // End of '~model' function

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
      if (!BoundBox.IsIntersect(Ray))
        return FALSE;

      auto n = Polygons.size();
      for (INT i = 0; i < n; ++i)
        if (Polygons[i]->Intersect(Ray, Inter))
        {
          Inter->I[0] = i;
          Inter->Shp = Polygons[i];
          return TRUE;
        }
      return FALSE;
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
      if (!BoundBox.IsIntersect(Ray))
        return FALSE;

      auto n = Polygons.size();
      for (INT i = 0; i < n; ++i)
        if (Polygons[i]->IsIntersect(Ray))
          return TRUE;
      return FALSE;
    } // End of 'IsIntersect' function

    /* Evaluate normal function. 
     * ARGUMENTS:
     *   - pointer to intersection:
     *       intersection *Inter;
     * RETURNS: None.
     */
    VOID GetNormal( intersection *Inter ) override
    {
      Polygons[Inter->I[0]]->GetNormal(Inter);
    } // End of 'GetNormal' function

  }; // End of 'model' class

} // End of 'kirt' namespace

#endif /* __model_h_ */

/* END OF 'model.h' FILE */