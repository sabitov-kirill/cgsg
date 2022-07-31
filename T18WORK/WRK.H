/* Kirill Sabitov, 10-6, 28,10.2020 */

#define MAX 30

typedef struct
{
  int Day, Month, Year;
} DATE;

typedef struct 
{
  char Name[30];
  char Surname[47];
  DATE Birthday;
  char Sex;
  int Hours[7];
} WORKER;

void GetStr( char *str, int MaxLen );
void ReadWorker( WORKER *W );
void DisplayWorkers( WORKER *W, int DBSize );
int SaveDB( char *FileName, WORKER *Base, int N );
int LoadDB( char *FileName, WORKER *Base, int MaxSize );
void EditWorker( WORKER *W );
void DBReverse ( WORKER *W, int DBSize );
void WorkerDelete( WORKER *W, int num, int DBSize );
int WorkersReport( WORKER *W, int DBSize );
