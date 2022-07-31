/* FILE NAME  : material.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 26.07.2021
 * PURPOSE    : material realise module.
 */

#ifndef __mtl_h_
#define __mtl_h_

#include "buffer.h"
#include <string>

// namespace for material
namespace kigl
{
  // Forward declaration
  class shader;
  class texture;
  class image;

  /* Material class */
  class material
  {
  public:
    /* Material template. */
    struct material_data
    {
      vec4 KaIsTexture, KdTrans, KsPh;

      /* Structure constructor.
       * ARGUMENTS:
       *   - material illumination coefficients:
       *       vec3 Ka, vec3 Kd, vec3 Ks, FLT Trans, FLT Ph;
       */
      material_data( vec3 Ka = vec3(0.1), vec3 Kd = vec3(0.8), vec3 Ks = vec3(0.2), FLT Ph = 30, FLT Trans = 1, BOOL IsTexture = FALSE ) :
        KaIsTexture(Ka, 0), KdTrans(Kd, Trans), KsPh(Ks, Ph) 
      {
      } /* End of 'buf_mtl' constructor */
    }; /* End of 'material_data' structure */

    static material_data Default; // Default material template

    std::string Name; // Name of material
    shader *Shd;      // Pointer to shader
    texture *Tex;     // Pointer to texture
    buffer *Buf;      // Buffer for materials

    /* Default contructor. */
    material( VOID ) : Shd(nullptr), Tex(nullptr), Buf(nullptr)
    {
    } /* End of default consructor */

    /* Create material function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &Name;
     *   - structure with coefficents:
     *       const kigl::material::material_data &Coefs;
     *   - name of shader:
     *       const std::string &ShdName;
     *   - texture file name:
     *       const std::string &TexName;
     * RETURNS: None.
     */
    VOID Create( const std::string &Name, material_data &Coefs,
                 const std::string &ShdName,
                 const std::string &TexName );

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
    VOID Create( const std::string &Name, material_data &Coefs,
                 const std::string &ShdName,
                 const std::string &TexName, image Img );

    /* Add shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Material storage initializate function.
     * ARGUMENTS:
     *   - Material number:
     *       INT MtlNo;
     * RETURNS:
     *   (INT) shader program id.
     */
    INT Apply( VOID );
  }; // End of 'material' class
} // End of 'kigl' namespace

#endif /* __material_h_ */

/* END OF 'material.h' FILE */ 
