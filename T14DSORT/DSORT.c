/*Kirill Sabitov, 10-6, 19.10.2020*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DSORT.h"

void RandFill( UINT64 *in_mas, int N )
{
  int i;

  for (i = 0; i < N; i++)
    in_mas[i] = rand() % RAND_MAX;
}

void DSort( UINT64 *in_m, int N )
{
  static UINT64 out_m[MAX], pow10;
  int offset[10], counts[10];
  int i, dig;

  for (dig = 0, pow10 = 1; dig < 18; ++dig, pow10 *= 10)
  {
    memset(counts, 0, sizeof(counts));
    for (i = 0; i < N; ++i)
      counts[in_m[i] / pow10 % 10]++;

    for (offset[0] = 0, i = 1; i < 10; i++)
      offset[i] = offset[i - 1] + counts[i - 1];

    for (i = 0; i < N; ++i)
      out_m[offset[in_m[i] / pow10 % 10]++] = in_m[i];

    for (i = 0; i < N; i++)
      in_m[i] = out_m[i];
  }
}

void PrintMas( UINT64 *in_m, int N )
{
  int i;

  for (i = 0; i < N; i++)
    printf("%d ", in_m[i]);

  printf("\n", in_m[i]);
}