/* FILE NAME  : image.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 31.07.2021
 * PURPOSE    : image realization functions module .
 */
 
#ifndef __image_h_
#define __image_h_

#include "../../../utilities/binary_reader.h"

// namespace for image
namespace kigl
{
   // Image class handle
  class image
  {
  private:
    INT PrivW, PrivH; // Image size

  public:
    INT &W, &H; // Image size public ref
    BYTE *Bits;       // Image pixels array
    INT C;            // Pixel components per pixel count

    /* Load *.bmp image function.
     *   - image to load in ref:
     *       image &Img;
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) succsess flag.
     */
    static BOOL LoadBMP( image &Img, const std::string &FileName )
    {
      HANDLE hBmFile;
      BITMAP bitmap;

      if ((hBmFile = LoadImage(NULL, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) == nullptr)
        return FALSE;

      GetObject(hBmFile, sizeof(bitmap), &bitmap);

      Img.PrivW = bitmap.bmWidth;
      Img.PrivH = bitmap.bmHeight;
      Img.C = 3;
      if (Img.Bits != nullptr)
        delete[] Img.Bits;
      Img.Bits = new BYTE[Img.PrivW * Img.PrivH * 3];
      memcpy(Img.Bits, bitmap.bmBits, Img.PrivW * Img.PrivH);

      DeleteObject(hBmFile);
      return TRUE;
    } // End of 'LoadBMP' function

    /* Loading G32 image function.
     * ARGUMENTS:
     *   - image to load in ref:
     *       image &Img;
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) succsess flag.
     */
    static BOOL LoadG32( image &Img, const std::string &FileName )
    {
      // Create binary reader, check its state
      binary_reader rd(FileName);
      if (!rd.IsOk())
        return FALSE;

      short W, H;
      rd(&W);
      rd(&H);
      if (rd.FileLength != W * H * 4 + 4)
        return FALSE;

      // Setup data
      Img.PrivW = W;
      Img.PrivH = H;
      Img.C = 4;
      if (Img.Bits != nullptr)
        delete[] Img.Bits;
      Img.Bits = new BYTE[W * H * 4];

      // Load buffer
      rd(Img.Bits, W * H * 4);
      return TRUE;
    } // End of 'LoadG32' function

    /* Image default constructor */
    image( VOID ) : PrivW(0), PrivH(0), W(PrivW), H(PrivH), C(0), Bits(nullptr)
    {
    } // End of 'image' function

    /* Image copy constructor. */
    image( const image &Img ) : 
      PrivW(Img.PrivW), PrivH(Img.PrivH), W(PrivW), H(PrivH), C(Img.C),
      Bits(new BYTE[Img.PrivW * Img.PrivH * Img.C])
    {
      for (INT i = 0; i < PrivH * PrivW * C; i++)
        Bits[i] = Img.Bits[i];
    } // End of 'image' function

    /* Image constructor by size.
     * ARGUMENTS:
     *   - image to create size:
     *       INT W, H;
     *   - components count:
     *       INT C;
     */
    image( INT W, INT H, INT C ) :
      PrivW(W), PrivH(H), W(PrivW), H(PrivH), C(C),
      Bits(new BYTE[PrivW * PrivH * C])
    {
    } // End of 'image' function

    /* Image constructor loading from file.
     * ARGUMENTS:
     *   - image path:
     *       const std::string &FileName;
     */
    image( const std::string &FileName ) : PrivW(0), PrivH(0), W(PrivW), H(PrivH), C(0), Bits(nullptr)
    {
      image img;

      if (LoadBMP(*this, FileName))
        return;
      if (LoadG32(*this, FileName))
        return;
    } // End of 'image' function

    /* Image destructor. */
    ~image( VOID )
    {
      PrivW = 0;
      PrivH = 0;
      if (Bits != nullptr)
        delete[] Bits;
    } // End of '~image' function
  };

} // end of namespace
 
#endif /* __image_h_ */
 
/* END OF 'image.h' FILE */


