/* Kirill Sabitov, 10-6, 27.10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "life.h"

/* Field Size*/
#define FIELD_H 128
#define FIELD_W 128

/* Usable byte type */
typedef unsigned char byte;

/* Current and generating field */
byte *CurField, *GenField;

/* Pause boolean variable */
int Pause = 0;

/* Delay creating function */
void Wait( double delay )
{
  double goal;
  goal = delay * CLOCKS_PER_SEC + clock();
  while (goal > clock())
    ;
}

/* Swaping field function */
void FSwap ( void )
{
  byte *tmp;

  tmp = CurField;
  CurField = GenField;
  GenField = tmp;
}

/* Setting new value of cell in field function */
void SetCell( byte *F, int x, int y, int value )
{
  x = (x + FIELD_W) % FIELD_W;
  y = (y + FIELD_H) % FIELD_H;

  F[FIELD_H * y + x] = value;
}

/* Getting current value function */
int GetCell( byte *F, int x, int y)
{
  x = (x + FIELD_W) % FIELD_W;
  y = (y + FIELD_H) % FIELD_H;
  
  return F[FIELD_H * y + x];
}

/* Getting count of near neighbours */
int GetNeigh( int x, int y )
{
  int NeighCount = 0, i, j;
  
  for (i = y - 1; i <= y + 1; i++)
    for (j = x - 1; j <= x + 1; j++)
      if ((i != y || j != x) && GetCell(CurField, j, i))
        NeighCount++; 

  return NeighCount;
}

/* New field generating function */
void GenerateField( void )
{
  int x, y;

  /* Setting memory for field masives */
  CurField = malloc(FIELD_H * FIELD_W);
  GenField = malloc(FIELD_H * FIELD_W);

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
      SetCell(CurField, x, y, rand() % 2);
}

/* Genering new generation of field function */
void NewGen( void )
{
  int x, y, ncount, value;

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
    {
      ncount = GetNeigh(x, y);

      if (GetCell(CurField, x, y))
      {
        if (ncount < 2 || ncount > 3)
          value = 0;
        else
          value = 1;
      }
      else
      {
        if (ncount == 3)
          value = 1;

        else 
          value = 0;
      }

      SetCell(GenField, x, y, value);
    }
}

/* Field drawing function */
void FieldInit( void )
{
  int x, y, RandColor = rand() % 30;

  Wait(0.1);

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
      switch (GetCell(CurField, x, y))
      {
      case 0:
        PutPixel(x, y , floor(x), (pow(floor(y), 2)), (pow(floor(x + y), sin(x))));
        break;
      case 1:
        PutPixel(x, y, 255, 255, 255);
        break;
      }
  
  if (Pause == 1)
    return;

  NewGen();
  FSwap();
}

/* Keyboard processing function */
void LifeKeyboard( unsigned char Key, int x, int y )
{
  if (Key == 'p')
    Pause = !Pause, printf("Pause %d\n", Pause);

  if (Key == 'q')
  {
    for (y = 0; y < FIELD_H; y++)
      for (x = 0; x < FIELD_W; x++)
        SetCell(CurField, x, y, 0);

    printf("Cleared\n");
  }
  
  if (Key == ' ')
    SetCell(CurField, x, y, 1);
  
  if (Key == 'c')
    SetCell(CurField, x, y, 0);;
}      