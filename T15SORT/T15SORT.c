/* Kirill Sabitov, 10-6, 21.10.2020 */

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "SORT.h"

#define MAX_AMOUNT 1000000

void ( *Fill[] )( float *in_m, int N ) = { FillRand, FillIncr, FillDecr, FillEq, FillMostly };

void ( *Sort[] )( float *in_m, int N ) = { BubbleSortAdv, BubbleSortShaker, InsertionSort, SelectionSort, MergeSort, QSort, HeapSort };
char *SortName[] = { "Bubble Advanced", "Bubble Shaker", "Insertion", "Selection", "Merge", "Quick", "Heap" };

static float mas[MAX_AMOUNT];

void PrintSort( int SortNum )
{
  int j, t;
  
  printf("Sort: %s\n", SortName[SortNum - 1]);
  for (j = 0; j < sizeof(Fill) / sizeof(Fill[0]); j++)
  {
    Fill[j](mas, MAX_AMOUNT);

    t = clock();
    Sort[SortNum - 1](mas, MAX_AMOUNT);
    t = clock() - t;

    if (CheckSort(mas, MAX_AMOUNT))
      printf(" %10.5f \n", t / (double)CLOCKS_PER_SEC);
    else 
      printf("    FAIL    \n");
  }
  printf("\n");
}

void main( void )
{
  int sort_method, i;

  printf("Amount of elements in sorting massive: %d\n", MAX_AMOUNT);
  printf("\n");

  printf("To select BubbleAdvanced sort - 1\n");
  printf("To select Shaker sort - 2\n");
  printf("To select Insertion sort - 3\n");
  printf("To select Selection sort - 4\n");
  printf("To select Merge sort - 5\n");
  printf("To select Quick sort sort - 6\n");
  printf("To select Heap sort sort - 7\n");
  printf("To select every sort - 8\n");
  printf("To exit - 9\n");
  printf("\n");

  do
  {
    printf("Select sorting method: ");
    scanf("%d", &sort_method);
    printf("\n");

    if (sort_method != 8 && sort_method != 9)
      PrintSort(sort_method);
    else if (sort_method != 9)
      for (i = 1; i < sizeof(Sort) / sizeof(Sort[0]) + 1; i++)
        PrintSort(i);
  } while (sort_method != 9);
}
