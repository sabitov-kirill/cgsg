/* Kirill Sabitov, 10-6, 30.10.2020 */

#define SECURE_NO_WARNINGS

typedef double DBL;
typedef struct 
{
  DBL Re, Im;
} COMPL;

COMPL CompleSetCompl( DBL Re, DBL Im );
COMPL CompleAddCompl( COMPL Z1, COMPL Z2);
COMPL CompleMulCompl( COMPL Z1, COMPL Z2);
DBL CompleNorm( COMPL Z1 );

int Mandel( COMPL Z, COMPL C );
int Julia( COMPL Z, COMPL C );
