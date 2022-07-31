/* Kirill Sabitov, 10-6, 21.10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include "SORT.h"

void Swap( float *el1, float *el2 )
{
  float tmp = *el1;

  *el1 = *el2;
  *el2 = tmp;
}

void PrintMas( float *in_m, int N )
{
  int i;

  for (i = 0; i < N; i++)
    printf("%f ", in_m[i]);
}

void FillRand( float *in_m, int N )
{
  int i;
  
  for (i = 0; i < N; i++)
    in_m[i] = (float)((rand() - RAND_MAX / 2) / 102.0);
}

void FillIncr( float *in_m, int N )
{
  int i;

  for (in_m[0] = -30.47, i = 1; i < N; ++i)
    in_m[i] = (float)(in_m[i - 1] + rand() % 10 / 0.8);
}

void FillDecr( float *in_m, int N )
{
  int i;

  for (in_m[0] = 30.47, i = 1; i < N; ++i)
    in_m[i] = (float)(in_m[i - 1] - rand() % 10 / 0.8);
}

void FillEq( float *in_m, int N )
{
  int i;

  for (in_m[0] = (float)(rand() % RAND_MAX), i = 0; i < N; i++)
    in_m[i] = in_m[0];  
}

void FillMostly( float *in_m, int N )
{
  int i;

  FillIncr(in_m, N);
  for (i = 0; i < N / 20; ++i)
    Swap(&in_m[rand() % N], &in_m[rand() % N]);
}

int CheckSort( float *in_m, int N )
{
  int i;

  for (i = 1; i < N; ++i)
    if (in_m[i] < in_m[i - 1])
      return 0;
  return 1;
}