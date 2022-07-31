/* FILE NAME  : texture_manager.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 26.07.2021
 * PURPOSE    : Texture manager type declaration module.
 */

#ifndef __texture_manager_h_
#define __texture_manager_h_

#include "../resourses/texture.h"
#include "resourses_manager.h"

#include <string>

namespace kigl
{
  // Texture manager type
  class texture_manager : public resourses_manager<texture, std::string>
  {
  public:
    /* Texture creation and addition it to storage.
     * ARGUMENTS:
     *   - image to create texture from path:
     *       const std::string &FileName;
     * RETURNS:
     *   (texture) create texture.
     */
    texture * TextureCreate( const std::string &FileName )
    {
      // Check if shader with passed name already exist
      texture *SuitabelTex;
      if ((SuitabelTex = Find(FileName)) != nullptr)
        return SuitabelTex;

      // Create texture
      texture Tex;
      if (Tex.Create(FileName))
        return Add(Tex);
      return nullptr;
    } // End of 'TextureCreate' function

    /* Texture creation and addition it to storage.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &Name;
     *   - image to create texture from:
     *       const image &Img;
     * RETURNS:
     *   (texture) create texture.
     */
    texture * TextureCreate( const std::string &Name, const image &Img )
    {
      // Check if shader with passed name already exist
      texture *SuitabelTex;
      if ((SuitabelTex = Find(Name)) != nullptr)
        return SuitabelTex;

      // Create texture
      texture Tex;
      if (Tex.Create(Name, Img))
        return Add(Tex);
      return nullptr;
    } // End of 'TextureCreate' function

    /* Texture delition function.
     * ARGUMENTS:
     *   - topology:
     *       texture *Tex;
     * RETURNS: None.
     */
    VOID TextureFree( texture *Tex )
    {
      if (Tex != nullptr)
      Delete(Tex);
    } // End of 'TextureCreate' function
  };
}

#endif // !__texture_manager_h_

// END OF 'texture_manager.h' FILE