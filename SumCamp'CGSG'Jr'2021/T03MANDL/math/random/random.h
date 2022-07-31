/* FILE NAME  : random.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Randomizer definition module.
 */

/* Randomizer structure definition */
struct random
{
  int MaxValue;

  random( int MaxValue );
  operator float( void );
};

/* END OF 'random.h' FILE */