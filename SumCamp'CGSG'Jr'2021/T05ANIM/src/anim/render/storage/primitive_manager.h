/* FILE NAME  : primitive_manager.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Primitive manager type declaration module.
 */

#ifndef __primitive_manager_h_
#define __primitive_manager_h_

#include "resourses_manager.h"
#include "../resourses/primitive.h"
#include <string>

namespace kigl
{
  // Primitive manager type
  class primitive_manager : public resourses_manager<primitive, INT>
  {
  public:
    /* Primitive creation and addition it to storage.
     * ARGUMENTS:
     *   - topology:
     *       const topology::base &Topo;
     *   - primitive material pointer from storage;
     *       material *Mtl;
     * RETURNS:
     *   (primitive *) pointer to create primitive from storage.
     */
    template<typename vertex_type>
    primitive * PrimitiveCreate( topology::base<vertex_type> &Topo, material *Mtl = nullptr )
    {
      primitive Prim;
      Prim.Create(Topo, Mtl);

      return Add(Prim);
    } // End of 'PrimitiveCreate' function

    /* Primitive delition function.
     * ARGUMENTS:
     *   - primitive:
     *       primitive *Prim;
     * RETURNS: None.
     */
    VOID PrimitiveFree( primitive *Prim )
    {
      if (Prim != nullptr)
        Delete(Prim);
    } // End of 'PrimitiveCreate' function
  };
}

#endif // !__primitive_manager_h_

// END OF 'primitive_manager.h' FILE