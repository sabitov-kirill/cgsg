/* Kirill Sabitov, 10-6, 21.10.2020 */

#include "SORT.h"

void BubbleSortAdv( float *in_m, int N )
{
  int i, last = N - 2, changed;

  do
  {
    for (changed = 0, i = 0; i <= last; i++)
      if(in_m[i] > in_m[i + 1])
        Swap(&in_m[i], &in_m[i + 1]), changed = i;

    last = changed - 1;
  } while (last >= 0);
}

void BubbleSortShaker( float *in_m, int N )
{
  int i, last = N - 2, first = 0, changed;

  do
  {
    for (changed = 0, i = first; i <= last; i++)
      if(in_m[i] > in_m[i + 1])
        Swap(&in_m[i], &in_m[i + 1]), changed = i;
    last = changed - 1;

    for (changed = 0, i = last; i >= first; i--)
      if(in_m[i] > in_m[i + 1])
        Swap(&in_m[i], &in_m[i + 1]), changed = i;
    first = changed + 1;
    
  } while (last >= first);
}

void InsertionSort( float *in_m, int N )
{
  int i, j;
  float x;

  for (i = 1; i < N; i++)
  {
    if (in_m[i] < in_m[i - 1])
    {
      x = in_m[i];
      j = i - 1;
      while (j >= 0 && x < in_m[j])
        in_m[j + 1] = in_m[j], j--;
      in_m[j + 1] = x;
    }
  }
}

void SelectionSort( float *in_m, int N )
{
  int i, j, min;

  for (j = 0; j <= N - 2; j++)
  {
    for (i = j + 1, min = j; i < N; i++)
      if (in_m[i] < in_m[min])
        min = i;
    Swap(&in_m[j], &in_m[min]);
  }
}