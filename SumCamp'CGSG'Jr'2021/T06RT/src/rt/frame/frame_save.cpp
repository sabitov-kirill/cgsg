/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win_callbacks.cpp
 * PURPOSE     : Ray tracing project.
 *               Window virtual callbacks handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "frame.h"

#include <format>
#include <filesystem>
#include <fstream>
#include <cstdio>

// #pragma pack(push, 1)
// #include <tgahead.h>
// #pragma pack(pop)

using namespace kirt;

/* Frame shots saving dirictory creation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID frame::SaveDirCreate( VOID )
{
  SYSTEMTIME st;
  GetLocalTime(&st);
  SavePath = std::format("bin/shots/{}.{:0>2}.{:0>2}_{:0>2}.{:0>2}.{:0>2}",
    st.wYear  ,
    st.wMonth ,
    st.wDay   ,
    st.wHour  ,
    st.wMinute,
    st.wSecond);

  std::filesystem::create_directories(SavePath);

  SaveDirCreated = TRUE;
} // End of 'SaveDirCreate' 
/* Save frame to *.tga file.
 * ARGUMENTS:
 *   - file to write image in name:
 *       const std::string &FileName;
 *   - frame render time:
 *       DBL RenderTime;
 * RETURNS:
 *   (BOOL) succsess flag.
 */
VOID frame::SaveTGA( DBL RenderTime )
{
  // if (!SaveDirCreated)
  //   SaveDirCreate();
  // 
  // SYSTEMTIME st;
  // GetLocalTime(&st);
  // std::string FileName = std::format("{}/RT_FRAME_{:0>2}.{:0>2}.{:0>2}.{:0>2}.tga",
  //   SavePath  ,
  //   st.wHour  ,
  //   st.wMinute,
  //   st.wSecond,
  //   st.wMilliseconds);
  // 
  // tgaFILEHEADER fh;
  // fh.X = fh.Y = 0;
  // fh.Width = W;
  // fh.Height = H;
  // fh.ImageType = 2;
  // fh.BitsPerPixel = 32;
  // fh.PaletteEntrySize = 0;
  // fh.PaletteSize = 0;
  // fh.PaletteStart = 0;
  // fh.IDLength = static_cast<BYTE>(strlen("(c) Computer Graphics Support Group of 30 Phys-Math Lyceum"));
  // fh.ColorMapType = 0;
  // fh.ImageDescr = 32;
  // 
  // tgaEXTHEADER eh;
  // memcpy(eh.AuthorName, "Sabitov Kirill. CGSG Jr'2020.\0", 30);
  // memcpy(eh.AuthorComment, "Ray Tracing algorithm visualisation render.\nCreated on CGSG'SummerCamp'2021\nCGGS FOREVER!!!\0", 83);
  // memcpy(eh.SoftwareID, "School 30 PC.\nCPU only render - Intel Core i5-10600.", 53);
  // eh.JobHour = floor(RenderTime / 3600);
  // eh.JobMinute = floor(RenderTime / 60 - eh.JobHour * 60);
  // eh.JobSecond = floor(RenderTime - eh.JobMinute * 60 - eh.JobHour * 3600);
  // 
  // tgaFILEFOOTER ff;
  // ff.DeveloperOffset = 0;
  // ff.ExtensionOffset = 0;
  // CopyMemory(ff.Signature, TGA_EXT_SIGNATURE, 18);
  // 
  // std::fstream f(FileName, std::fstream::out | std::fstream::binary);
  // if (!f.is_open())
  //   return;
  // f.write((CHAR *)&fh, sizeof(fh));
  // f.write("(c) Computer Graphics Support Group of 30 Phys-Math Lyceum", fh.IDLength);
  // for (INT y = 0; y < H; y++)
  //   for (INT x = 0; x < W; x++)
  //     f.write((CHAR *)&Pixels[y * W + x], 4);
  // f.write((CHAR *)&ff, sizeof(ff));
  // f.write((CHAR *)&eh, sizeof(eh));
} // End of 'SaveTGA' function

// END OF 'win_callb.cpp' FILE