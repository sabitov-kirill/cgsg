#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "WARM.h"

/* Size of each char of font in pixels */
#define FONT_H 19
#define FONT_W 8

/* Massive of chars in font */
unsigned char Font[256][FONT_H];

/* Loading bin font from file to massive */
void LoadFont( void )
{
  FILE* FntF;

  FntF = fopen("LVSCYR-VerySoft-8x19.fnt", "rb");
  if (FntF == NULL)
    return;

  fread(Font, 1, FONT_H * 256, FntF);
  fclose(FntF);
}


/* Drawing chars on screen */
void DrawChar( char ch, int x0, int y0, int r, int g, int b )
{
  int x, y;

  for (y = 0; y < FONT_H; y++)
    for (x = 0; x < FONT_W; x++)
      if ((Font[ch][y] & (0x80 >> x)))
        PutPixel(x0 + x + 1, y0 + y + 1, r / 3, g / 3, b / 3);

  for (y = 0; y < FONT_H; y++)
    for (x = 0; x < FONT_W; x++)
      if ((Font[ch][y] & (0x80 >> x)))
        PutPixel(x0 + x, y0 + y, r, g, b);
}

/* Drawing string on screen*/
void DrawStr( char* str, int x0, int y0, int r, int g, int b )
{
  int i;
  for (i = 0; str[i] != 0; i++)
    DrawChar(str[i], x0 + i * 8, y0, r, g, b);
}


/* Drawing numbers on screen */
void DrawNum( int num, int num_len, int x0, int y0, int r, int g, int b )
{
  int i, carry;
  unsigned char drawing_num[100];
	
  for (i = 0; i < 100; i++)
    drawing_num[i] = 0;

  for (i = 0; num != 0; i++)
  {
    drawing_num[i] = num % 10;
    num /= 10;
  }

  for (carry = 0, i = --num_len; i >= 0; i--, carry++)
  {
    DrawChar(drawing_num[i] + 48, x0 + carry * FONT_W, y0, r, g, b);	
  }
}

/* Clearing chars from screen */
void ClearChars( int x0, int y0, int Amount )
{
  int x, y;

  for (y = 0; y < FONT_H; y++)
    for (x = 0; x < Amount * FONT_W; x++)
      PutPixel(x0 + x, y0 + y, 0, 0, 0);
}