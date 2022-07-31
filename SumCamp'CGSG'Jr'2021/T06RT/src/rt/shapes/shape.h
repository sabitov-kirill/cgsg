/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : shape.h
 * PURPOSE     : Ray tracing project.
 *               Base shape handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __shape_h_
#define __shape_h_

#include "../../def.h"

/* Math library namespace */
namespace kirt
{
  // Forward declaration
  class shape;

  // Threshold value
  const DBL Threshold = 0.000001;

  /* Intersection data class. */
  struct intersection
  {
    shape *Shp; // Intersected shape

    DBL T;      // Distance to intersected object
    vec3 N;     // Shape normal
    BOOL IsN;   // Shape evaluation flag
    vec3 P;     // Intersection point
    BOOL IsP;   // Intersection evaluation flag

    // Addons
    INT I[5];
    DBL D[5];

    /* Default class constructor. */
    intersection( VOID ) : Shp(nullptr), IsN(FALSE), IsP(FALSE)
    {
    } // End of 'intersection' function

  }; // End of 'intersection' class

  /* Shape surface class. */
  struct surface
  {
  public:
    vec3 Ka, Kd, Ks; // Ambient, diffuse, specular
    DBL Ph;          // Bui Tong Phong coefficient
    DBL Kr, Kt;      // Reflected, transmitted

    /* Class constructor.
     * ARGUMENTS:
     *   - illumination cpefficients:
     *       vec3 Ka, Kd, Ks;
     *       DBL Ph, Kr, Kt;
     */
    surface( vec3 Ka, vec3 Kd, vec3 Ks, DBL Ph, DBL Kr, DBL Kt ) :
      Ka(Ka), Kd(Kd), Ks(Ks), Ph(Ph), Kr(Kr), Kt(Kt)
    {
    } // End of '' function
  }; // End of 'surface' function

  // Standard surfaces library namespace
  namespace surfaces_lib
  {
    const surface Default        = {{0.1, 0.1, 0.1},             {0.8, 0.8, 0.8},               {0.5, 0.5, 0.5},                 30,      0,    0};
    const surface Mirror         = {{0.1, 0.1, 0.1},             {0.8, 0.8, 0.8},               {0.5, 0.5, 0.5},                 30,      1,  0};
    const surface BlackPlastic   = {{0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},            {0.5, 0.5, 0.5},                 32,      0.01, 0};
    const surface Brass          = {{0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843},    27.8974, 0.1,  0};
    const surface Bronze         = {{0.2125,0.1275,0.054},        {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},    25.6,    0.1,  0};
    const surface Chrome         = {{0.25, 0.25, 0.25},           {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597},  76.8,    0.1,  0};
    const surface Copper         = {{0.19125,0.0735,0.0225},      {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},    12.8,    0.1,  0};
    const surface Gold           = {{0.24725,0.1995,0.0745},      {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},    51.2,    0.3,  0};
    const surface Peweter        = {{0.10588,0.058824,0.113725},  {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},        9.84615, 0.8,  0};
    const surface Silver         = {{0.19225,0.19225,0.19225},    {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},    51.2,    0.1,  0};
    const surface PolishedSilver = {{0.23125,0.23125,0.23125},    {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},    89.6,    0.6,  0};
    const surface Turquoise      = {{0.1, 0.18725, 0.1745},       {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678},   12.8,    0.3,  0};
    const surface Ruby           = {{0.1745, 0.01175, 0.01175},   {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959},  76.8,    0.8,  0};
    const surface PolishedGold   = {{0.24725, 0.2245, 0.0645},    {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006},  83.2,    0.9,  0};
    const surface PolishedBronze = {{0.25, 0.148, 0.06475},       {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621},  76.8,    0.7,  0};
    const surface PolishedCopper = {{0.2295, 0.08825, 0.0275},    {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2,    0.6,  0};
    const surface Jade           = {{0.135, 0.2225, 0.1575},      {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228},  12.8,    0.5,  0};
    const surface Obsidian       = {{0.05375, 0.05, 0.06625},     {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435},  38.4,    0.05, 0};
    const surface Pearl          = {{0.25, 0.20725, 0.20725},     {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648},  11.264,  0.5,  0};
    const surface Emerald        = {{0.0215, 0.1745, 0.0215},     {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},        76.8,    0.8,  0};
    const surface BlackRubber    = {{0.02, 0.02, 0.02},           {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                 10.0,    0.01, 0};

    const surface Stock[21] =
    {
      Default       ,
      Mirror        ,
      BlackPlastic  ,
      Brass         ,
      Bronze        ,
      Chrome        ,
      Copper        ,
      Gold          ,
      Peweter       ,
      Silver        ,
      PolishedSilver,
      Turquoise     ,
      Ruby          ,
      PolishedGold  ,
      PolishedBronze,
      PolishedCopper,
      Jade          ,
      Obsidian      ,
      Pearl         ,
      Emerald       ,
      BlackRubber   ,
    };
  }

  /* Scene enviroment illumination data struct. */
  struct enviroment
  {
  public:
    DBL RefractionCoef; // Refraction coefficient
    DBL DecayCoef;      // Decay coefficient

    /* Class default constructor. */
    enviroment( VOID ) : RefractionCoef(1), DecayCoef(1)
    {
    } // End of '' function

    /* Class constructor. */
    enviroment( DBL RefractionCoef, DBL DecayCoef ) :
      RefractionCoef(RefractionCoef), DecayCoef(DecayCoef)
    {
    } // End of 'enviroment' function

  }; // End of 'enviroment' class

  /* Abstract shape class. */
  class shape
  {
  public:
    // Shape surface
    surface Surface;
    // Shape enviroment
    enviroment Envi;

    /* Class constructor.
     * ARGUMENTS:
     *   - shape surface data:
     *       const surface &Surface;
     *   - shape enviroment:
     *       const enviroment &Enviroment;
     */
    shape( const surface &Surface, const enviroment &Enviroment = {} ) : Surface(Surface), Envi(Enviroment)
    {
    } // End of 'shape' function

    /* Class destructor. */
    virtual ~shape( VOID )
    {
    } // End of '~shape' function

    /* Shape and ray intersection function. 
     * ARGUMENTS:
     *   - ray:
     *       const ray<type> &Ray;
     *   - veariable to set intersection point in:
     *       intersection<type> *Inter;
     * RETURNS:
     *   (BOOL) intersection flag.
     */
    virtual BOOL Intersect( const ray &Ray, intersection *Inter ) const = 0;

    /* Shape and ray intersection getting succses flag function.
     * ARGUMENTS:
     *   - ray:
     *       const ray<type> &Ray;
     * RETURNS:
     *   (BOOL) intersection flag.
     */
    virtual BOOL IsIntersect( const ray &Ray ) const = 0;

    /* Evaluate normal function. 
     * ARGUMENTS:
     *   - pointer to intersection:
     *       intersection *Inter;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intersection *Inter ) = 0;

  }; // End of 'shape' class

} // End of 'kirt' namespace

#endif /* __shape_h_ */

/* END OF 'shape.h' FILE */