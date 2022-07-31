/* FILE NAME  : vertex.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Vertex type declaration module.
 */

#ifndef __vertex_h_
#define __vertex_h_

#include "../../../kigl.h"
#include <string>

namespace kigl
{
  /* Topology namespace */
  namespace topology
  {
    /* Vertex collection namespace */
    namespace vertex
    {
      /* Standard vertex representation type */
      struct std
      {
        vec3 P;  /* Vertex position */
        vec2 T;  /* Vertex texture coordinates */
        vec3 N;  /* Normal at vertex */
        vec4 C;  /* Vertex color */

        /* Vertex content description string */
        static const ::std::string Description;
 
        /* Class default constructor */
        std( VOID )
        {
        } /* End of 'std' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - new vertex position:
         *       const vec &NewP;
         *   - new vertex texture coordinates:
         *       const vec2 &NewT;
         *   - new vertex normal:
         *       const vec &NewN;
         *   - new vertex color:
         *       const vec4 &NewC;
         */
        std( const vec3 &NewP,
             const vec2 &NewT = vec2(0, 0),
             const vec3 &NewN = vec3(0, 1, 0),
             const vec4 &NewC = vec4(0) ) :
          P(NewP), T(NewT), N(NewN), C(NewC)
        {
        } // End of 'std' function
      }; // End of 'vertex' class
    } // End of 'vertex' namespace
  } // End of 'topology' namespace
} // End of 'kigl' namespace

#endif // !__vertex_h_

// END OF 'vertex.h' FILE  