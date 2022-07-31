/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : frame.h
 * PURPOSE     : Ray tracing project.
 *               Ray tracing rendering frame class handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __frame_h_
#define __frame_h_

#include "../../def.h"

#include <string>

/* Project namespace */
namespace kirt
{
  /* Rendering frame class */
  class frame
  {
  private:
    INT PrivateW, PrivateH; // Frame size. Only for use in frame module
    DWORD *Pixels;          // Frame pixels buffer

  public:
    // Public frame size
    const INT &W, &H;

    // Frame saving data
    std::string SavePath;        // Frame saving path
    BOOL SaveDirCreated = FALSE; // Frame saving dir creation flag

    /* Class default contructor */
    frame( VOID ) :
      PrivateW(0), PrivateH(0), Pixels(nullptr),
      W(PrivateW), H(PrivateH)
    {
    } // End of 'frame' function

    /* Class constructor size.
     * ARGUMENTS:
     *   - frame size:
     *       INT W, H;
     */
    frame( INT W, INT H ) :
      PrivateW(W), PrivateH(H), Pixels(new DWORD[W * H]),
      W(PrivateW), H(PrivateH)
    {
    } // End of 'frame' function

    /* Class destructor */
    ~frame( VOID )
    {
      if (Pixels != nullptr)
        delete[] Pixels;

      PrivateW = 0;
      PrivateH = 0;
    } // End of '~frame' function

    /* Frmae resize function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      if (Pixels != nullptr)
        delete[] Pixels;

      PrivateW = NewW;
      PrivateH = NewH;

      Pixels = new DWORD[PrivateW * PrivateH];
    } // End of 'Resize' function

    /* Changing frame pixels buffer. 
     * ARGUMENTS:
     *   - frame pixel to change possintion:
     *       INT X, Y;
     *   - new pixel color:
     *       DWORD Color;
     * RETURNS: None
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      if (X < 0 || X > PrivateW || Y < 0 || Y > PrivateH)
        return;

      Pixels[Y * PrivateW + X] = Color;
    } // End of 'PutPixel' function

    /* Changing frame pixels buffer. 
     * ARGUMENTS:
     *   - frame pixel to change possintion:
     *       INT X, Y;
     *   - new pixel color:
     *       DWORD Color;
     * RETURNS: None
     */
    VOID PutPixel( INT X, INT Y, vec3 Color )
    {
      if (X < 0 || X > PrivateW || Y < 0 || Y > PrivateH)
        return;

      Pixels[Y * PrivateW + X] = ToRGB(Color);
    } // End of 'PutPixel' function

    /* Getting frame pixel operator.
     * ARGUMENTS:
     *   - frame pixel row:
     *       INT Y;
     * RETURNS:
     *   (DWORD) pixel by possition.
     */
    DWORD * operator[]( INT Y )
    {
      Y = mth::Clamp(Y, 0, PrivateH);
      return &Pixels[Y * PrivateW];
    } // End of 'operator[]' function

    /* Frame draw to drawing context function.
     * ARGUMENTS:
     *   - on screen drawing frame start coords:
     *       INT StartX, INT StartY;
     *   - drawing image size:
     *       INT ImgW, INT Img H;
     */
    VOID Draw( HDC hDC, INT StartX, INT StartY, INT ImgW = 0, INT ImgH = 0 )
    {
      BITMAPINFOHEADER bih;

      bih.biSize = sizeof(BITMAPINFOHEADER);
      bih.biBitCount = 32;
      bih.biPlanes = 1;
      bih.biWidth = PrivateW;
      bih.biHeight = -PrivateH;
      bih.biSizeImage = PrivateW * PrivateH * 4;
      bih.biCompression = BI_RGB;
      bih.biClrUsed = 0;
      bih.biClrImportant = 0;
      bih.biXPelsPerMeter = 30;
      bih.biYPelsPerMeter = 30;

      SetStretchBltMode(hDC, COLORONCOLOR);
      StretchDIBits(hDC, StartX, StartY, ImgW ? ImgW : W, ImgH ? ImgH : H,
                    0, 0, PrivateW, PrivateH, Pixels, (BITMAPINFO *)&bih, DIB_RGB_COLORS, SRCCOPY);
    } // End of 'Draw' function

    /* Frame shots saving dirictory creation function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID SaveDirCreate( VOID );

    /* Save frame to *.tga file.
     * ARGUMENTS:
     *   - file to write image in name:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) succsess flag.
     */
    VOID SaveTGA( DBL RenderTime = 0 );

    /* Color conversation from double to dword function. 
     * ARGUMENTS:
     *   - color (0 - 1):
     *       DBL R, G, B;
     * RETURNS:
     *   (DWORD) converted color.
     */
    static DWORD ToRGB( DBL R, DBL G, DBL B );

    /* Color conversation from double to dword function. 
     * ARGUMENTS:
     *   - color (0 - 1):
     *       DBL R, G, B;
     * RETURNS:
     *   (DWORD) converted color.
     */
    static DWORD ToRGB( vec3 RGB );

    /* Color conversation from double to dword function. 
     * ARGUMENTS:
     *   - color (0 - 1):
     *       DBL R, G, B;
     * RETURNS:
     *   (DWORD) converted color.
     */
    static DWORD ToRGB( BYTE R, BYTE G, BYTE B );

  }; // End of 'frame' class
}

#endif // !__frame_h_

// END OF 'frame.h' FILE