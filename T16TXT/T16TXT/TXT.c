/* Kirill Sabitov, 10-6, 27.10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *LoadText( char *FileName )
{
  FILE *Text;
  int TextLen = 0, i = 0;
  char *Txt;

  if ((Text = fopen(FileName, "r")) != NULL)
  {
    while (fgetc(Text) != EOF)
      TextLen++;
    rewind(Text);

    if ((Txt = malloc(TextLen + 1)) != NULL)
    {
      while ((Txt[i] = fgetc(Text)) != EOF)
        i++;
      Txt[i] = 0;

      return Txt;
    }
  }
}

void PrintLettersCount( char *Txt )
{
  int c, LettersCounts[26];

  for (c = 0; c < 26; c++)
  {
    LettersCounts[c] = 0;  
  }

  for (c = 0; Txt[c] != 0; c++)
  {
    if (Txt[c] >= 'A' && Txt[c] <= 'Z')
      LettersCounts[Txt[c] - 'A']++;
    
    if (Txt[c] >= 'a' && Txt[c] <= 'z')
      LettersCounts[Txt[c] - 'a']++;
  }

  for (c = 0; c < 26; c++)
    printf("%c occured %d time(s).\n", c + 'A', LettersCounts[c]);
}

int GetWordsStat( char *Txt, int (*WordStat)(int b, int e, char *Word) )
{
  int WordsAmount = 0, c = 0, res = 0, b, e;

  while (Txt[c] != 0)
  {
    while (isspace((unsigned char)Txt[c]))
      c++;
    
    if (Txt[c] != 0)
    {
      b = c;
      
      while (!isspace((unsigned char)Txt[c]) && Txt[c] != 0)
        c++;

      e = c - 1;

      res += WordStat(b, e, Txt);
    }
  } 
  return res;
}

int WordCount( int b, int e, char *Word )
{
  return 1;
}

int PoliWordCount( int b, int e, char *Word )
{
  while (b < e)
    if (Word[b++] != Word[e--])
      return 0;
  return 1;
}

int WordDigitNum( int b, int e, char *Word )
{
  int c, sum;

  for (c = b, sum = 0; c <= e; c++)
    if (isdigit((unsigned char)Word[c]))
      sum += sum * 10 + Word[c] - '0';

  return sum;
}