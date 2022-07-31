/* Sabitov Kirill, 10-6, 29.10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <PCXHEAD.H>

#include "pcx.h"

typedef unsigned char byte;

struct 
{
  byte Pali[256][3];
  int ColCount;
  int PaliMode;
} Palitra;

pcxFILEHEAD Head;


int ReadHead( char *FileName )
{
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  
  fread(&Head, 128, 1, F);

  printf("File: %s\n", FileName);
  printf("BitsPerPixel: %d\n", Head.BitsPerPixel);
  printf("BytesPerLine: %d\n", Head.BytesPerLine);
  printf("Encode: %d\n", Head.Encode);
  printf("PlanesAmount: %d\n", Head.PlanesAmount);
  printf("PaletteInfo: %d\n", Head.PaletteInfo);
  printf("Width: %d\n", Head.X2 - Head.X1 + 1);
  printf("Height: %d\n", Head.Y2 - Head.Y1 + 1);
  
  fclose(F);

  return 1;
}

int CreatePali( char *FileName )
{
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  Palitra.ColCount = pow(2, Head.BitsPerPixel) * Head.PlanesAmount;

  if (Palitra.ColCount > 16)
  {
    fseek(F, -769, SEEK_END);
    Palitra.PaliMode = fgetc(F);
    fread(Palitra.Pali, 1, 768, F);

    fclose(F);

    printf("PaliMode: %02x\n", Palitra.PaliMode);  
  }
                                   
  printf("ColCount: %d\n", Palitra.ColCount);
  printf("\n");

  return 1;
}

int DrawPCX( char *FileName )
{
  byte by, *Planes[4], col, r, g, b;
  int x, y, p, i, j, rep;
  FILE *F;
  
  ReadHead(FileName);
  CreatePali(FileName);

  Planes[0] = malloc(Head.BytesPerLine * Head.PlanesAmount);
  for (i = 1; i < Head.PlanesAmount; i++)
    Planes[i] = Planes[i - 1] + Head.BytesPerLine;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  fseek(F, 128, SEEK_SET);
  p = 0;
  x = 0;
  y = 0;
  while (y < Head.Y2 - Head.Y1 + 1)
  {
    by = fgetc(F);

    if((by & 0xC0) == 0xC0)
    {
      rep = by & 0x3F;
      by = fgetc(F);
    }
    else
      rep = 1;

    while (rep-- > 0)
    {
      Planes[p][x++] = by;
      if (x >= Head.BytesPerLine)
      {
        x = 0;

        if (++p >= Head.PlanesAmount)
        {
          p = 0;
          for (i = 0; i < Head.X2 - Head.X1 + 1; i++)
          {
            if (Head.BitsPerPixel == 8 && Head.PlanesAmount == 1)
            {
              col = Planes[0][i];
              r = Palitra.Pali[col][0];
              g = Palitra.Pali[col][1];
              b = Palitra.Pali[col][2];
            }

            else if (Head.BitsPerPixel == 8 && Head.PlanesAmount == 3)
            {
              r = Planes[0][i];
              g = Planes[1][i];
              b = Planes[2][i];
            }

            else if (Head.BitsPerPixel == 1 && Head.PlanesAmount == 1)
            {
              col = (Planes[0][i >> 3] >> (7 - (x & 7))) & 1;
              r = Head.Pal[col * 3 + 0];
              g = Head.Pal[col * 3 + 1];
              b = Head.Pal[col * 3 + 2];
            }

            else if (Head.BitsPerPixel == 1 && Head.PlanesAmount == 4)
            {
              col = 0;
              for (j = 0; j < 4; j++)
                col |= ((Planes[j][i >> 3] >> (7 - (x & 7))) & 1) << j;
              r = Head.Pal[col * 3];
              g = Head.Pal[col * 3 + 1];
              b = Head.Pal[col * 3 + 2];
            }

            PutPixel(i, y, r, g, b);
          }
          y++;
        }
      }
    }
  }

  fclose(F);
  return 1;
}