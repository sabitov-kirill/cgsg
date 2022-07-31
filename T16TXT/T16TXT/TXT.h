/* Kirill Sabitov, 10-6, 27.10.2020 */

char *LoadText( char *FileName );
void PrintLettersCount( char *Text );
int GetWordsStat( char *Txt, int (*WordStat)(int b, int e, char *Word) );
int WordCount( int b, int e, char *Word );
int PoliWordCount( int b, int e, char *Word );
int WordDigitNum( int b, int e, char *Word );