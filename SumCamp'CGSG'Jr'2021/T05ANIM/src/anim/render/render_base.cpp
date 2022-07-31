/* FILE NAME  : render_base.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 23.07.2021
 * PURPOSE    : Render system handle module.
 */

#include "../anim.h"

#include <cstdio>
#include <ctime>
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")

using namespace kigl;

// OpenGL debug function
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message, const VOID *UserParam );

/* Render system type constructor.
 * ARGUMENTS:
 *   - window handle ref:
 *       HWND &hWnd;
 *   - window size ref:
 *       INT &W, &H;
 */
render::render( HWND &hWnd, INT &W, INT &H ) :
  hRndWnd(hWnd), hRndDC(GetDC(hWnd)), FrameW(W), FrameH(H)
{
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };
 
  // OpenGL init: pixel format setup
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;

  INT i = ChoosePixelFormat(hRndDC, &pfd);
  DescribePixelFormat(hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(hRndDC, i, &pfd);
 
  // OpenGL init: setup rendering context
  hRndGLRC = wglCreateContext(hRndDC);
  wglMakeCurrent(hRndDC, hRndGLRC);
 
  // Initializing GLEW library
  if (glewInit() != GLEW_OK)
  {
    MessageBox(hRndWnd, "Error extensions initializing", "Error",
      MB_ICONERROR | MB_OK);
    exit(0);
  }
 
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(hRndWnd, "Error: no shaders support", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }
 
  // Enable a new OpenGL profile support
  UINT nums;
  wglChoosePixelFormatARB(hRndDC, PixelAttribs, nullptr, 1, &i, &nums);
  HGLRC hRC = wglCreateContextAttribsARB(hRndDC, nullptr, ContextAttribs);
 
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(hRndGLRC);
 
  hRndGLRC = hRC;
  wglMakeCurrent(hRndDC, hRndGLRC);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
  glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

  // Set default OpenGL parameters
  glClearColor(0.30, 0.5, 0.7, 1);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
} // End of 'render' constructor

/* Render system type destructor.
 * ARGUMENTS: None.
 */
render::~render( VOID )
{
} // End of 'render' destructor

/* Render init function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID render::Init( VOID )
{
  anim *Ani = anim::GetPtr();

  // Creating and applying buffers
  RenderDataBuf    = Ani->BufferCreate(2, sizeof(render_data));
  PrimitiveDataBuf = Ani->BufferCreate(3, sizeof(primitive_data));
  RenderDataBuf->Apply();
  PrimitiveDataBuf->Apply();
} // End of 'render::Init' function

/* Render closer function to use instead of destructor.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID render::Close( VOID )
{
  // Calling close methods of parents classes
  primitive_manager::Close();
  shader_manager::Close();
  material_manager::Close();
  texture_manager::Close();
  buffer_manager::Close();

  // Destroyng OpenGL context
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(hRndGLRC);
  ReleaseDC(hRndWnd, hRndDC);
} // End of '' function

/* Rendring resizing function.
 * ARGUMENTS: None
 * RETURNS: None.
 */
VOID render::Resize( VOID )
{
  glViewport(0, 0, FrameW, FrameH);
  Camera.Resize(FrameW, FrameH);
} // End of 'render::Resize' function

/* Rendring copy frame function.
  * ARGUMENTS:
      - WINDOW HANDLE:
          HWND hWnd;
  * RETURNS: None.
  */
VOID render::CopyFrame( VOID )
{
  wglSwapLayerBuffers(hRndDC, WGL_SWAP_MAIN_PLANE); 
} // End of 'render::CopyFrame' function

/* Rendring start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID render::Start( VOID )
{
  anim *Ani = anim::GetPtr();

#if _DEBUG
  // Updating shders each 3 sec
  static DBL ReloadTime = 0;
  if ((ReloadTime += Ani->DeltaTime) > 3)
  {
    ShadersUpdate();
    ReloadTime = 0;
  }
#endif // !_DEBUG

  // Clear frame
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Apply render data buffer
  render_data data(Camera.Dir, Camera.Loc, Camera.Right, Camera.Up, FrameW, FrameH, Ani->Time);
  RenderDataBuf->Update(&data);

  // Draw sky sphere
  if (ActiveSky.Prim != nullptr)
    Ani->SkyDraw(ActiveSky);
} // End of 'render::Start' function

/* Rendring end function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */ 
VOID render::End( VOID )
{
  glFinish();
} // End of 'render::End' function

/* Sky activation function.
 * ARGUMENTS:
 *   - sky sphere:
 *       const skysphere &Sky;
 * RETURNS: None.
 */
VOID render::SkyActivate( const skysphere &Sky )
{
  ActiveSky = Sky;
} // End of 'render::SkyActivate' function

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id, 
 *   - message severity:
 *      UINT severity, 
 *   - message text length:
 *      INT Length, 
 *   - message text:
 *      CHAR *Message, 
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message, const VOID *UserParam )
{
  INT len = 0;
  static CHAR Buf[10000];
 
  /* Ignore non-significant error/warning codes */
  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;

  len += sprintf_s(Buf + len, 10000, "Debug message (%i) %s\n", Id, Message);
  switch (Source)
  {
  case GL_DEBUG_SOURCE_API:
    len += sprintf_s(Buf + len, 10000, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf_s(Buf + len, 10000, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf_s(Buf + len, 10000, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf_s(Buf + len, 10000, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf_s(Buf + len, 10000, "Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf_s(Buf + len, 10000, "Source: Other");
    break;
  }
  len += sprintf_s(Buf + len, 10000, "\n");
 
  switch (Type)
  {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf_s(Buf + len, 10000, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf_s(Buf + len, 10000, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf_s(Buf + len, 10000, "Type: Undefined Behaviour");
    break; 
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf_s(Buf + len, 10000, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf_s(Buf + len, 10000, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf_s(Buf + len, 10000, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf_s(Buf + len, 10000, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf_s(Buf + len, 10000, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf_s(Buf + len, 10000, "Type: Other");
    break;
  }
  len += sprintf_s(Buf + len, 10000, "\n");
 
  switch (Severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf_s(Buf + len, 10000, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf_s(Buf + len, 10000, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf_s(Buf + len, 10000, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf_s(Buf + len, 10000, "Severity: notification");
    break;
  }
  len += sprintf_s(Buf + len, 10000, "\n\n");
 
  OutputDebugString(Buf);
} /* End of 'glDebugOutput' function */

// END OF 'render_base.cpp' FILE