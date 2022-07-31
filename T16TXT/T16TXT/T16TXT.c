/* Kirill Sabitov, 10-6, 27.10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TXT.h"


void main( void )
{
  char FName[200];
  char *InTxt;
 
  printf("Enter file name: ");
  gets(FName);

  InTxt = LoadText(FName);

  PrintLettersCount(InTxt);

  printf("Amount of words: %d\n", GetWordsStat(InTxt, WordCount));
  printf("Amount of polindom words: %d\n", GetWordsStat(InTxt, PoliWordCount));
  printf("Sum of digital nums in words: %d\n", GetWordsStat(InTxt, WordDigitNum));
}