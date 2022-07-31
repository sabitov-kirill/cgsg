/* FILE NAME  : models.cpp
 * PROGRAMMER : AL6
 * LAST UPDATE: 28.07.2021
 * PURPOSE    : prims collection functions realization
 */

#include "../../anim.h"

using namespace kigl;

/* Class constructor */
skysphere::skysphere( VOID ) : Prim(nullptr), Mtl(nullptr)
{
} // End of 'skysphere::skysphere' function

 /* Class constructor.
 * ARGUMENTS:
 *   - file name to laod from:
 *       const std::string &FileName;
 */
skysphere::skysphere( const std::string &FileName )
{
  anim *Ani = anim::GetPtr();

  topology::base<topology::vertex::std> topo(topology::primitive_type::POINTS, {topology::vertex::std(vec3(0))});
  Mtl = Ani->MaterialCreate("sky_" + FileName, material::material_data(vec3(0.1), vec3(0.8), vec3(0), 30, 1), "sky_sphere", FileName);
  Prim = Ani->PrimitiveCreate(topo, Mtl);
} // End of 'skysphere::skysphere' function

/* Model destructor */
skysphere::~skysphere( VOID )
{
  anim *Ani = anim::GetPtr();

  Ani->MaterialFree(Mtl);
  Ani->PrimitiveFree(Prim);
} // End of 'skysphere::~skysphere' function

/* END OF 'models.cpp' FILE */
