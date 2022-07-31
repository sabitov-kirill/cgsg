/* FILE NAME  : main.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Main programm function.
 */

#include <cstdio>
#include <cstring>
#include <iostream>

#include "anim/anim.h"
#include "units/units.h"

 /* Main programm function.
  * ARGMUNETS:
  *   - programm instance handler:
  *       HINSTANCE hInstance;
  *   - programm previous instance handler:
  *       HINSTANCE hPrevInstance;
  *   - command line pointer:
  *       CHAR *CmdLine;
  *   - window hide flag:
  *       INT ShouldShow;
  * RETURNS:
  *   (INT) System return code.
  */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR* CmdLine, INT ShouldShow)
{
  kigl::anim* AnimationSystem = kigl::anim::GetPtr();

  *AnimationSystem << new kigl::units::clouds(AnimationSystem);
  *AnimationSystem << new kigl::units::game(AnimationSystem);

  return AnimationSystem->Run();
}

/* END OF 'main.cpp' FILE */