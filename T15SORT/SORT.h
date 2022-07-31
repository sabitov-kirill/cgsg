/* Kirill Sabitov, 10-6, 21.10.2020 */

/* Util Funcs */
void Swap( float *el1, float *el2 );
void PrintMas( float *in_m, int N );
void FillRand( float *in_m, int N );
void FillIncr( float *in_m, int N );
void FillDecr( float *in_m, int N );
void FillEq( float *in_m, int N );
void FillMostly( float *in_m, int N );
int CheckSort( float *in_m, int N );

/* Sorting Funcs */
void BubbleSortAdv( float *in_m, int N );
void BubbleSortShaker( float *in_m, int N );
void InsertionSort( float *in_m, int N );
void SelectionSort( float *in_m, int N );
void MergeSort( float *in_m, int N );
void QSort( float *in_m, int N );
void HeapSort( float *in_m, int N );