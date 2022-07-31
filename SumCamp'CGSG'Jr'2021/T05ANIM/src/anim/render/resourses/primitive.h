/* FILE NAME:  prim.h
 * PROGRAMMER: kigl
 * DATE:       23.07.2021
 * PURPOSE:    Mathematics realise.
 */

#ifndef __prim_h_
#define __prim_h_

#include "../../../kigl.h"
#include "material.h"
#include "topology.h"

namespace kigl
{
  // Primitive class
  class primitive
  {
  public:
    UINT
      IBuf,                        // Index buffer id
      VBuf,                        // Vertex buffer id
      VA;                          // Vertex array buffer id
    INT NumOfEllements;            // Vertecies or indexes count

    topology::primitive_type Type; // Primitive type
    matr Trans = matr::Identity(); // Transform matrix
    BOOL IsTransMatrixSet = FALSE; // Translation matrix set flag
    vec3 Min, Max;                 // Minimum and maximum value for primitive

    material* Mtl = nullptr;       // Material pointer

    /* Class constructor */
    primitive(VOID) :
      VA(0), VBuf(0), IBuf(0), NumOfEllements(0),
      Type(topology::primitive_type::TRIMESH)
    {
    }

    /* Class destructor */
    ~primitive(VOID)
    {
    } /* End of '~prim' function */

    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     * RETURNS:
     *   (prim &) self reference.
     */
    template<typename vertex>
    VOID Create(const topology::base<vertex>& T, material* Mtl)
    {
      Free();

      if (!T.Vert.empty())
      {
        glGenBuffers(1, &VBuf);
        glGenVertexArrays(1, &VA);

        glBindVertexArray(VA);
        glBindBuffer(GL_ARRAY_BUFFER, VBuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * T.Vert.size(), T.Vert.data(), GL_STATIC_DRAW);

        // Setup data order due to vertex description string
        const std::string dsc = vertex::Description;
        INT attr = 0, offset = 0;
        for (auto c = dsc.begin(); c != dsc.end(); c++)
          if (*c == 'f' || *c == 'i')
          {
            CHAR type = *c++;
            INT n = *c - '0';

            if (n < 0 || n > 9)
              break;

            // Enable used attributes
            glEnableVertexAttribArray(attr);
            glVertexAttribPointer(attr, n, type == 'f' ? GL_FLOAT : GL_INT, FALSE,
              sizeof(vertex), reinterpret_cast<VOID*>(offset));

            offset += n * 4;
            attr++;
          }
          else
            break;

        glBindVertexArray(0);
      }
      if (!T.Ind.empty())
      {
        glGenBuffers(1, &IBuf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * T.Ind.size(), T.Ind.data(), GL_STATIC_DRAW);
        NumOfEllements = T.Ind.size();
      }
      else
        NumOfEllements = T.Vert.size();

      Min = T.Min;
      Max = T.Max;
      Type = T.Type;
      this->Mtl = Mtl;
    } // End of 'Create' function

  /* Free render primitive function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
    VOID Free(VOID)
    {
      if (VA != 0)
      {
        glBindVertexArray(VA);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBuf);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VA);

        VA = 0, VBuf = 0;
      }
      if (IBuf != 0)
      {
        glDeleteBuffers(1, &IBuf);

        IBuf = 0;
      }
    } // End of 'Free' function

    /* Set translation matrix function.
     * ARGUMENTS:
     *   - matrix:
     *       const matr &M;
     * RETURNS: None.
     */
    VOID SetTrans(const matr& M)
    {
      Trans = M;
      IsTransMatrixSet = TRUE;
    }// End of 'SetTrans' function
  }; // End of 'primitive' class
} // End of 'kigl' namespace

#endif /* __prim_h_ */

/* END OF 'prim.h' FILE */
