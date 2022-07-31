/* FILE NAME  : texture.h
 * PROGRAMMER : AL6
 * LAST UPDATE: 26.07.2021
 * PURPOSE    : texture realise module.
 */

#ifndef __texture_h_
#define __texture_h_

#include "../resourses/image.h"

// namespace for texture
namespace kigl
{
  // Rendering texture type
  class texture
  {
  private:
    friend class render;
    INT W, H;   // Texture size

  public:
    // Texture name
    std::string Name;     
    UINT TexId; // Texture OpenGL Id

    /* Texture default constructor */
    texture( VOID ) : TexId(0), W(0), H(0)
    {
    } // End of 'texture' function

    /* Texture default destructor */
    ~texture( VOID )
    {
    } // End of 'texture' function

    /* Texture creation function.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &Name;
     *   - image to create texture from:
     *       const image &Img;
     * RETURNS:
     *   (BOOL) succsess flag.
     */
    BOOL Create( const std::string &Name, const image &Img )
    {
      if (Img.Bits == nullptr)
        return FALSE;

      // Calulate textire mips
      FLT mips;
      mips = Img.W > Img.H ? Img.H : Img.W;
      mips = log(mips) / log(2);
      if (mips < 1)
        mips = 1;

      // Generating texture
      glGenTextures(1, &TexId);
      glBindTexture(GL_TEXTURE_2D, TexId);

      // Add pixels storage to texture
      glTexStorage2D(GL_TEXTURE_2D, mips, Img.C == 3 ? GL_RGB8 : Img.C == 4 ? GL_RGBA8 : GL_R8, Img.W, Img.H);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Img.W, Img.H, GL_BGRA, GL_UNSIGNED_BYTE, Img.Bits);
      glGenerateMipmap(GL_TEXTURE_2D);

      // Set texture parametrs
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      // Unbind created texture
      glBindTexture(GL_TEXTURE_2D, 0);

      // Set texture data
      this->Name = Name;
      W = Img.W;
      H = Img.H;
      return TRUE;
    } // End of 'Create' function

    /* Texture creation function.
     * ARGUMENTS:
     *   - image to create texture from path:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) succsess flag.
     */
    BOOL Create( const std::string &FileName )
    {
      image img(FileName);
      if (img.Bits == nullptr)
        return FALSE;

      return Create(FileName, img);
    } // End of 'Create' function

    /* Texture delete function.
     * ARGUMENTS:
     *   - texture:
     *       texture *Tex;
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      if (TexId == 0)
        return;

      glDeleteTextures(0, &TexId);
      TexId = 0;
      W = 0;
      H = 0;
    } // End of 'Free' function

    /* Texture activation function.
     * ARGUMENTS:
     *   - texture number:
     *       INT Num;
     * RETURNS: None.
     */
    VOID Activate( INT Num )
    {
      glActiveTexture(GL_TEXTURE0 + Num);
      glBindTexture(GL_TEXTURE_2D, TexId);
    } // End of 'Activate' function
  }; // End of 'texture' class
} // End of namespace

#endif /* __texture__h_ */

/* END OF 'texture.h' FILE */
