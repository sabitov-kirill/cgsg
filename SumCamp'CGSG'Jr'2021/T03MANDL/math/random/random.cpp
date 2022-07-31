/* FILE NAME  : random.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Randomizer handle module.
 */

#include <random>

#include "random.h"

random::random( int MaxValue = 1 ) : MaxValue(MaxValue)
{
}

random::operator float( void )
{
  return static_cast<float>(MaxValue) * std::rand() / RAND_MAX;
}

/* END OF 'random.cpp' FILE */