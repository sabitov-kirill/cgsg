/*Kirill Sabitov, 10-6, 19.10.2020*/

#include <stdio.h>
#include <conio.h>
#include "DSORT.h"


void main( void )
{
  static UINT64 m[MAX];

  RandFill(m, MAX);

  DSort(m, MAX);
  
  PrintMas(m, MAX);
    
  _getch();
}
