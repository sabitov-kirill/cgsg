/* FILE NAME  : mtl.cpp
 * PROGRAMMER : AL6
 * LAST UPDATE: 26.07.2021
 * PURPOSE    : material realise module.
 */

#include "../../anim.h"

/* Create material function.
 * ARGUMENTS:
 *   - material name:
 *       const std::string &Name;
 *   - structure with illumination coefficents:
 *       const kigl::material::material_data &Coefs;
 *   - shader name:
 *       const std::string &ShdName;
 *   - texture file name:
 *       const std::string &TexName;
 * RETURNS: None.
 */
VOID kigl::material::Create( const std::string &Name, 
                             kigl::material::material_data &Coefs,
                             const std::string &ShdName,
                             const std::string &TexName )
{
  kigl::anim *Ani = kigl::anim::GetPtr();

  this->Name = Name;
  Shd = Ani->ShaderCreate(ShdName);
  Tex = Ani->TextureCreate(TexName);
  Coefs.KaIsTexture = vec4(Coefs.KaIsTexture[0], Coefs.KaIsTexture[1], Coefs.KaIsTexture[2], Tex != nullptr);
  Buf = Ani->BufferCreate<material_data>(1, &Coefs);
} /* End of 'Create' function */

/* Create material function.
 * ARGUMENTS:
 *   - structure with coefficents:
 *       material_data *Coef;
 *   - name of shader:
 *       std::string ShdName;
 *   - texture name and image:
 *       std::string TexName, image Img;
 *   - image for texture:
 *       image Img;
 * RETURNS: None.
 */
VOID kigl::material::Create( const std::string &Name, 
                             kigl::material::material_data &Coefs,
                             const std::string &ShdName,
                             const std::string &TexName, image Img )
{
  kigl::anim *Ani = kigl::anim::GetPtr();

  this->Name = Name;
  Shd = Ani->ShaderCreate(ShdName);
  Tex = Ani->TextureCreate(TexName, Img);
  Coefs.KaIsTexture = vec4(Coefs.KaIsTexture[0], Coefs.KaIsTexture[1], Coefs.KaIsTexture[2], Tex != nullptr);
  Buf = Ani->BufferCreate<material_data>(1, &Coefs);
} /* End of 'Create' function */

/* Add shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID kigl::material::Free( VOID )
{
  kigl::anim *Ani = kigl::anim::GetPtr();

  Ani->BufferFree(Buf);
} /* End of 'Free' function */

/* Material storage initializate function.
* ARGUMENTS:
*   - Material number:
*       INT MtlNo;
* RETURNS:
*   (INT) shader program id.
*/
INT kigl::material::Apply( VOID )
{
  Shd->Apply();
  if (Tex != nullptr)
    Tex->Activate(0);

  Buf->Apply();
  return Shd->GetId();
} /* End of 'Apply' function */

/* END OF 'material.cpp' FILE */ 
