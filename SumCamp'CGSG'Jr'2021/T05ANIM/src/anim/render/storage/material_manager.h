/* FILE NAME  : material_manager.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Material manager type declaration module.
 */

#ifndef __material_manager_h_
#define __material_manager_h_

#include "../resourses/material.h"
#include "resourses_manager.h"

#include <string>

namespace kigl
{
  // Primitive manager type
  class material_manager : public resourses_manager<material, std::string>
  {
  public:
    /* Material creation function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &Name;
     *   - material data template:
     *       material::material_data DataTemplate;
     *   - shader programm name:
     *       std::string ShaderName;
     * RETURNS:
     *   (BOOL) succsess flag.
     */
    material *MaterialCreateNoTexture( const std::string &Name,
                                       material::material_data DataTemplate = material::material_data(vec3(0.1), vec3(0.8), vec3(0), 30, 1),
                                       const std::string &ShaderName = "default" )
    {
      // Check if material with passed name already exist
      material *SuitabelMtl;
      if ((SuitabelMtl = Find(Name)) != nullptr)
        return SuitabelMtl;

      // Create new otherwise
      material Mtl;
      Mtl.Create(Name, DataTemplate, ShaderName, "");
      if (Mtl.Buf != nullptr && Mtl.Shd != nullptr)
        return Add(Mtl);
      return nullptr;
    } // End of 'MaterialCreate' function

    /* Material creation function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &Name;
     *   - material data template:
     *       material::material_data DataTemplate;
     *   - shader programm name:
     *       std::string ShaderName;
     *   - tetxure file name:
     *       std::string TextureFileName;
     * RETURNS: None.
     */
    material *MaterialCreate( const std::string &Name,
                              material::material_data DataTemplate = material::material_data(vec3(0.1), vec3(0.8), vec3(0), 30, 1),
                              const std::string &ShaderName = "default",
                              const std::string &TextureFileName = "" )
    {
      // Check if material with passed name already exist
      material *SuitabelMtl;
      if ((SuitabelMtl = Find(Name)) != nullptr)
        return SuitabelMtl;

      // Create new otherwise
      material Mtl;
      Mtl.Create(Name, DataTemplate, ShaderName, TextureFileName);
      if (Mtl.Buf != nullptr && Mtl.Shd != nullptr)
        return Add(Mtl);
      return nullptr;
    } // End of 'MaterialCreate' function

    /* Material creation function.
     * ARGUMENTS:
      *   - material name:
     *       const std::string &Name;
     *   - material data template:
     *       material::material_data DataTemplate;
     *   - shader programm name:
     *       std::string ShaderName;
     *   - texture name:
     *       const std::string &TextureName;
     *   - image to create texture from:
     *       const image &Img;
     * RETURNS: None.
     */
    material *MaterialCreateFromImage( const std::string &Name,
                                       material::material_data DataTemplate = material::material_data(vec3(0.1), vec3(0.8), vec3(0), 30, 1),
                                       const std::string &ShaderName = "default",
                                       const std::string &TextureName = "", const image &Img = {} )
    {
      // Check if material with passed name already exist
      material *SuitabelMtl;
      if ((SuitabelMtl = Find(Name)) != nullptr)
        return SuitabelMtl;

      // Create new otherwise
      material Mtl;
      Mtl.Create(Name, DataTemplate, ShaderName, TextureName, Img);
      if (Mtl.Buf != nullptr && Mtl.Shd != nullptr)
        return Add(Mtl);
      return nullptr;
    } // End of 'MaterialCreateFromImage' function

    /* Shader delition storage.
     * ARGUMENTS:
     *   - material:
     *       material *Mtl;
     * RETURNS: None.
     */
    VOID MaterialFree( material *Mtl )
    {
      if (Mtl != nullptr)
        Delete(Mtl);
    } // End of 'MaterialFree' function
  };
}

#endif // !__material_manager_h_

// END OF 'material_manager.h' FILE