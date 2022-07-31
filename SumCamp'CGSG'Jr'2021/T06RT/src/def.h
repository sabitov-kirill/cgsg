/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Ray tracing project.
 *               Common definitions modules.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __def_h_
#define __def_h_

#pragma warning(disable : 4200 4244 4013 4018 4115 4761 4127 4305 26451 4312 4267)
#pragma warning(error : 4016 4027 4701)

#include <windows.h>

#include "mth/mth.h"

#pragma region Memory_Allocation_Control

/* Debug memory allocation support */
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include  <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#pragma endregion

#pragma region Math_Types_Definition

typedef double DBL;
typedef float FLT;

/* Project namespace */
namespace kirt
{
  // Math types definition for OpenGL
  typedef mth::vec2<DBL>   vec2;
  typedef mth::vec3<DBL>   vec3;
  typedef mth::vec4<DBL>   vec4;
                           
  typedef mth::matr<DBL>   matr;

  typedef mth::camera<DBL> camera;

  typedef mth::ray<DBL>    ray;
} // End of 'kirt' namespace

#pragma endregion

#endif // !__def_h_

// END OF 'def.h' FILE