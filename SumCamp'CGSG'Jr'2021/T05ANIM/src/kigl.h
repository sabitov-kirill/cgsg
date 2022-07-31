/* FILE NAME  : basedef.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Common definitions modules.
 */

#ifndef __kigl_h_
#define __kigl_h_

#pragma warning(disable : 4200 4244 4013 4018 4115 4761 4127 4305 26451 4312 4267)
#pragma warning(error : 4016 4027 4701)

#define GLEW_STATIC
#include <glew.h>
#include <windows.h>

#include "mth/mth.h"
#include "utilities/stock.h"

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
  __Dummy(VOID)
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

// Math types definition for OpenGL
typedef mth::vec2<FLT>                  vec2;
typedef mth::vec3<FLT>                  vec3;
typedef mth::vec4<FLT>                  vec4;
typedef mth::matr<FLT>                  matr;
typedef mth::camera<FLT>                camera;
typedef mth::intersections::sphere<FLT> sphere;
typedef mth::intersections::ray<FLT>    ray;

#endif // !__kigl_h_

// END OF 'basedef.h' FILE