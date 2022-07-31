/* Kirill Sabitov, 10-6, 28,10.2020 */

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "wrk.h"

void GetStr( char *str, int MaxLen )
{
  int i = 0;
  char ch;
  
  while (( ch = getchar()) != '\n')
    if ( str != NULL && i < MaxLen - 1)
      str[i++] = ch;

  if (str != NULL && i < MaxLen)
    str[i] = 0;
}

void EditLine( char *S, int MaxLen )
{
  int run_flag = 1, len = strlen(S), pos = len, i;
  char ch;

  printf("%s", S);
  while (run_flag)
  {
    switch ((unsigned char)(ch = _getch()))
    {
    case '\r':
      run_flag = 0;
      break;
    case '\b':
      /* back-space */
      if (pos > 0)
      {
        memmove(S + pos - 1, S + pos, len - pos + 1);
        len--;
        pos--;
        printf("\b");
        for (i = pos; i < len; i++)
          printf("%c", S[i]);
        printf(" \b");
        for (i = len - 1; i >= pos; i--)
          printf("\b");
      }
      break;
    case 224:
      switch (_getch())
      {
      case 75:
        /* left */
        if (pos > 0)
          pos--, printf("\b");
        break;
      case 77:
        /* right */
        if (pos < len)
          printf("%c", S[pos++]);
        break;
      case 83:
        /* delete */
        if (pos < len)
        {
          memmove(S + pos, S + pos + 1, len - pos + 1);
          len--;
          for (i = pos; i < len; i++)
            printf("%c", S[i]);
          printf(" \b");
          for (i = len - 1; i >= pos; i--)
            printf("\b");
        }
        break;
      case 71:
        /* home */
        for (i = pos; i > 0; i--)
          printf("\b");
        pos = 0;
        break;
      case 79:
        /* end */
        for (i = pos; i < len; i++)
          printf("%c", S[i]);
        pos = len;
        break;
      }
      break;
    default:
      if ((unsigned char)ch >= ' ' && pos < MaxLen - 1)
      {
        /* insert a new symbol */
        memmove(S + pos + 1, S + pos, len - pos + 1);
        S[pos] = ch;
        len++;
        for (i = pos; i < len; i++)
          printf("%c", S[i]);
        for (i = len - 1; i > pos; i--)
          printf("\b");
        pos++;
      }
    }
  }
  printf("\n");
}

void ReadWorker( WORKER *W )
{
  int i;
  
  printf("Enter name: ");
  GetStr(W->Name, sizeof W->Name);

  printf("Enter surname: ");
  GetStr(W->Surname, sizeof W->Surname);

  printf("Enter year of birth: ");
  scanf("%d", &W->Birthday.Year);
  GetStr(NULL, 0);

  printf("Enter month of birth: ");
  scanf("%d", &W->Birthday.Month);
  GetStr(NULL, 0);

  printf("Enter day of birth: ");
  scanf("%d", &W->Birthday.Day);
  GetStr(NULL, 0);

  printf("Enter sex (M or F): ");
  scanf("%c", &W->Sex);
  GetStr(NULL, 0);

  for (i = 0; i < 7; i++)
  {
    printf("Enter amount of work hours in day #%d: ", i + 1);
    scanf("%d", &W->Hours[i]);
    GetStr(NULL, 0);
  }
  printf("\n");
}

void DisplayWorkers( WORKER *W, int DBSize )
{
  int i, j;

  for (i = 0; i < DBSize; i++)
  {
    printf("Worker No #%d\n", i + 1);
    printf("Worker name: %s\n", W[i].Name);
    printf("Worker surname: %s\n", W[i].Surname);
    printf("Worker birthday: %02d.%02d.%d\n", W[i].Birthday.Day, W[i].Birthday.Month, W[i].Birthday.Year);
    printf("Worker sex: %c\n", W[i].Sex);
    for (j = 0; j < 7; j++)
      printf("Worker amount of work hours in day #%d: %d\n", j + 1, W[i].Hours[j]);
    printf("\n");
  }
}


int SaveDB( char *FileName, WORKER *Base, int N )
{
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;

  fwrite(Base, sizeof(WORKER), N, F);
  fclose(F);
  return 1;
}

int LoadDB( char *FileName, WORKER *Base, int MaxSize )
{
  int N;
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  N = fread(Base, sizeof(WORKER), MaxSize, F);
  fclose(F);
  return N;
}

void EditWorker( WORKER *W )
{
  char choise, editing_str[10], editing_sex[2] = { W->Sex, 0 };
  
  printf("Do you want to edit name (Y): ");
  choise = getchar();
  GetStr(NULL, 0);
  if (choise == 'Y' || choise == 'y')
  {
    printf("Edit worker name: ");
    EditLine(W->Name, sizeof W->Name);
  }

  printf("Do you want to edit surname (Y): ");
  choise = getchar();
  GetStr(NULL, 0);
  if (choise == 'Y' || choise == 'y')
  {
    printf("Edit worker surname: ");
    EditLine(W->Surname, sizeof W->Surname);
  }

  printf("Do you want to edit year of birth (Y): ");
  choise = getchar();
  GetStr(NULL, 0);
  if (choise == 'Y' || choise == 'y')
  {
    printf("Edit worker year of birth: ");
    sprintf(editing_str, "%d", W->Birthday.Year);
    EditLine(editing_str, sizeof(editing_str));
    sscanf(editing_str, "%d", &W->Birthday.Year);
  }

  printf("Do you want to edit month of birth (Y): ");
  choise = getchar();
  GetStr(NULL, 0);
  if (choise == 'Y' || choise == 'y')
  {
    printf("Edit worker month of birth: ");
    sprintf(editing_str, "%d", W->Birthday.Month);
    EditLine(editing_str, sizeof(editing_str));
    sscanf(editing_str, "%d", &W->Birthday.Month);
  }

  printf("Do you want to edit worker day of birth (Y): ");
  choise = getchar();
  GetStr(NULL, 0);
  if (choise == 'Y' || choise == 'y')
  {
    printf("Edit worker day of birth: ");
    sprintf(editing_str, "%d", W->Birthday.Day);
    EditLine(editing_str, sizeof(editing_str));
    sscanf(editing_str, "%d", &W->Birthday.Day);
  }

  printf("Do you want to edit worker sex (Y): ");
  choise = getchar();
  GetStr(NULL, 0);
  if (choise == 'Y' || choise == 'y')
  {
    printf("Edit worker sex: ");
    EditLine(editing_sex, sizeof(editing_sex));
    W->Sex = editing_sex[0];
  }
}

void DBReverse( WORKER *W, int DBSize )
{
  int i, j;
  WORKER tmp[MAX];

  for (i = 0; i < DBSize; i++)
    tmp[i] = W[i];

  for (i = 0, j = DBSize - 1; i < DBSize; i++, j--)
    W[i] = tmp[j];    
}

void WorkerDelete( WORKER *W, int num, int DBSize )
{
  int i;

  for (i = num; i < DBSize; i++)
    W[i - 1] = W[i];
}

int WorkersReport( WORKER *W, int DBSize )
{
  int i, j, cost, work_days, got;
  FILE *F;

  if ((F = fopen("KS6.txt", "w")) == NULL)
    return 0;

  printf("Cost of 1 work hour: ");
  scanf("%d", &cost);

  printf("Count of work days: ");
  scanf("%d", &work_days);

  fprintf(F, "Cost of 1 work hour: %d\n", cost);
  for (i = 0, got = 0; i < DBSize; i++, got = 0)
  {
    for (j = 0; j < work_days; j++)
      got += cost * W[i].Hours[j % 7];

    fprintf(F, "Worker #%d (%s) got %d rubles by %d days.\n", i + 1, W[i].Name, got, work_days );
  }

  fclose(F);

  return 1;
}