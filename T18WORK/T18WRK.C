/* Kirill Sabitov, 10-6, 28,10.2020 */

#include <stdio.h>
#include <stdlib.h>
#include "wrk.h"

void main( void )
{ 
  int DBSize = 0, task, worker_num, run = 1;
  static WORKER Workers[MAX];

  while (run) 
  {
    printf(
      "********************************\n"
      "0 - exit\n"
      "1 - create new worker\n"
      "2 - display all workers\n"
      "3 - delete 1 worker\n"
      ///"4 - sort all workers by alphabet\n"
      ///"5 - sort all workers by birthday\n"
      "6 - reverse database\n"
      "7 - save database\n"
      "8 - load database\n"
      "9 - edit worker\n"
      "10 - create workers money report\n"
      "********************************\n");
    printf("\n");

    printf("Select task: ");
    scanf("%d", &task);
    GetStr(NULL, 0);
    printf("\n");
    
    switch (task)
    {
    case 0:
      run = 0;
      break;
    case 1:
      if (DBSize < MAX)
        ReadWorker(&Workers[DBSize++]);
      else 
        printf("Cant create new worker. Max amount of workers\n");
      break;
    case 2:
      DisplayWorkers(Workers, DBSize);
      break;
    case 3:
      printf("Enter number of deliting worker(1 - %d): ", DBSize);
      scanf("%d", &worker_num);
      GetStr(NULL, 0);
      WorkerDelete(Workers, worker_num, DBSize--);
      printf("Worker #%d deleted\n", worker_num);
      break;
    case 6:
      DBReverse(Workers, DBSize);
      printf("Reversing database...\n");
      printf("Sucsess.\n");
      break;
    case 7:
      printf("Saving database to file \"ALL.DB\"...\n");
      if (SaveDB("ALL.DB", Workers, DBSize) == 1)
        printf("Sucsess.\n");
      else
        printf("Error.\n");
      break;
    case 8:
      printf("Loading database from file \"ALL.DB\"...\n");
      DBSize = LoadDB("ALL.DB", Workers, MAX);
      if (DBSize == 0)
        printf("Error.\n");
      else 
        printf("Sucsess.\n");
      break;
    case 9:
      printf("Enter editing worker number (1 - %d): ", DBSize);
      scanf("%d", &worker_num);
      GetStr(NULL, 0);
      EditWorker(&Workers[worker_num - 1]);
      break;
    case 10:
      if (WorkersReport(Workers, DBSize))
        printf("Sucsess.\n");
      else 
        printf("Error.\n");
      break;
    default:
      printf("Error. No such task.\n");
      break;
    }
    
    printf("\n");
    printf("Press any key to continue...");
    _getch();
    system("cls");
  }
}