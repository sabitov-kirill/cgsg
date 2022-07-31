/* Kirill Sabitov, 10-6, 21.10.2020 */

#include <stdlib.h>
#include <string.h>
#include "SORT.h"

static float *tmp_m;
static void MergeSortRec( float *in_m, int N )
{
  int M, i, j, k;

  if (N < 2)
    return;

  M = N / 2;

  MergeSortRec(in_m, M);
  MergeSortRec(in_m + M, N - M);
  for (k = 0, i = 0, j = M; k < N; ++k)
  {
    if (j >= N || i < M && in_m[i] < in_m[j])
      tmp_m[k] = in_m[i++];
    else
      tmp_m[k] = in_m[j++];
  }

  memcpy(in_m, tmp_m, sizeof(float) * N);
}

void MergeSort( float *in_m, int N )
{
  tmp_m = malloc(sizeof(float) * N);
  
  if (tmp_m != NULL)
  {
    MergeSortRec(in_m, N);
    free(tmp_m);
  }
}

void QSort( float *in_m, int N )
{
  int b = 0, e = N - 1; 
  float x = in_m[N / 2];

  if (N < 2)
    return;

  while (b <= e)
  {
    while (in_m[b] < x)
      b++;
    
    while (in_m[e] > x)
      e--;

    if (b <= e)
    {
      if (b != e)
        Swap(&in_m[e], &in_m[b]);
      b++;
      e--;
    }
  }

  QSort(in_m, e + 1);
  QSort(in_m + b, N - b);
}

void HeapCorrection( float *in_m, int N, int i )
{
  while(1)
  {
    int left = 2 * i + 1, right = 2 * i + 2, big = i;

    if (left < N && in_m[i] < in_m[left])
      big = left;

    if (right < N && in_m[big] < in_m[right])
      big = right;

    if (big == i)
      return; 
    
    Swap(&in_m[i], &in_m[big]);
    i = big;
  }
}

void HeapSort( float *in_m, int N )
{
  int i, j;

  for (j = N / 2 - 1; j >= 0; j--)
    HeapCorrection(in_m, N, j);

  for (i = 0; i < N - 1; i++)
  {
    Swap(&in_m[0], &in_m[N - i - 1]);
    HeapCorrection(in_m, N - i - 1, 0);
  }
}