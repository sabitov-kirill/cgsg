/* FILE NAME  : shader_manager.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Shader manager type declaration module.
 */

#ifndef __shader_manager_h_
#define __shader_manager_h_

#include "../resourses/shader.h"
#include "resourses_manager.h"

#include <string>

namespace kigl
{
  // Primitive manager type
  class shader_manager : public resourses_manager<shader, std::string>
  {
  public:
    /* Shader creation and addition it to storage.
     * ARGUMENTS:
     *   - shader programm name:
     *       std::string Name;
     * RETURNS:
     *   (primitive *) pointer to create primitive from storage.
     */
    shader * ShaderCreate( std::string Name )
    {
      // Check if shader with passed name already exist
      shader *SuitabelShd;
      if ((SuitabelShd = Find(Name)) != nullptr)
        return SuitabelShd;

      // Create new otherwise
      shader Shd;
      Shd.Create(Name);
      if (Shd.GetId() != 0)
        return Add(Shd);
      return nullptr;
    } // End of 'PrimitiveCreate' function

    /* Shader delition storage.
     * ARGUMENTS:
     *   - shader:
     *       shader *Shd;
     * RETURNS: None.
     */
    VOID ShaderFree( shader *Shd )
    {
      if (Shd != nullptr)
        Delete(Shd);
    } // End of 'PrimitiveCreate' function

    /* All shaders in storage update function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID ShadersUpdate( VOID )
    {
      for (auto &shd: Storage)
        shd.second.Update();
    } // End of 'ShadersUpdate' function
  };
}

#endif // !__shader_manager_h_

// END OF 'shader_manager.h' FILE