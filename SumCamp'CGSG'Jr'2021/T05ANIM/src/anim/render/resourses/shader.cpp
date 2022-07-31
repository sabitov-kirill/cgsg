/* FILE NAME  : shader.h
 * PROGRAMMER : AL6
 * LAST UPDATE: 26.07.2021
 * PURPOSE    : shadder realise module.
 */

#include "../../anim.h"

/* Load text from file function.
 * ARGUMENTS:
 *   - file name to be load from:
 *       const std::string &FileName;
 * RETURNS:
 *   (std::string) load text.
 */
std::string kigl::shader::LoadTextFile( const std::string &FileName )
{
  std::ifstream f(FileName);

 return std::string((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
} /* End of 'LoadTextFile' function */

/* Store log to file function.
 * ARGUMENTS:
 *   - text 1 to save:
 *       const std::string &Stage;
 *   - text 2 to save:
 *       const std::string &Text;
 * RETURNS: None.
 */
VOID kigl::shader::Log( const std::string &Stage, const std::string &Text )
{
  std::ofstream("bin/shaders/shaders.log", std::ios_base::app) <<
    Name << ":" << Stage << ":\n" << Text << "\n";
} /* End of 'Log' function */

/* Load shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID kigl::shader::Load( VOID )
{
  Free();
  struct
  {
    INT Type;          /* Shader OpenFL type (e.g. GL_VERTEX_SHADER) */
    std::string Stuff; /* Shader file prefix name (e.g. "VERT") */
    INT Id;            /* Obtained shader Id from OpenGL */
  } shdr[] =
  {
    {GL_VERTEX_SHADER, "vert", 0},
    {GL_TESS_CONTROL_SHADER, "ctrl", 0},
    {GL_TESS_EVALUATION_SHADER, "eval", 0},
    {GL_GEOMETRY_SHADER, "geom", 0},
    {GL_FRAGMENT_SHADER, "frag", 0},
  };
  INT res;
  CHAR Buf[1000];
  BOOL is_ok = TRUE;

  for (auto &s : shdr)
  {
    /* Create shader */
    if ((s.Id = glCreateShader(s.Type)) == 0)
    {
      Log(s.Stuff, "Error create shader");
      is_ok = FALSE;
      break;
    }
    /* Load shader text from file */
    sprintf_s(Buf, "bin/shaders/%s/%s.glsl", const_cast<CHAR *>(Name.c_str()), const_cast<CHAR *>(s.Stuff.c_str()));
    std::string txt = LoadTextFile(Buf);
    if (txt.empty())
    {
      if (s.Stuff != "VERT" && s.Stuff != "FRAG")
      {
        glDeleteShader(s.Id);
        s.Id = 0;
        continue;
      }
      else
      {
        Log(s.Stuff, "Error create shader");
        is_ok = FALSE;
        break;
      }
    }

    /* Attach shader text to shader */
    const CHAR *Src = txt.c_str();
    glShaderSource(s.Id, 1, &Src, NULL);

    /* Compile shader */
    glCompileShader(s.Id);
    glGetShaderiv(s.Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(s.Id, sizeof(Buf), &res, Buf);
      Log(s.Stuff, Buf);
      is_ok = FALSE;
      break;
    }
  }

  /* Create shader program */
  if (is_ok)
  {
    if ((ProgId = glCreateProgram()) == 0)
      is_ok = FALSE;
    else
    {
      /* Attach shaders to program */
      for (auto s : shdr)
        if (s.Id != 0)
          glAttachShader(ProgId, s.Id);
      /* Link shader program */
      glLinkProgram(ProgId);
      glGetProgramiv(ProgId, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(ProgId, sizeof(Buf), &res, Buf);
        Log("LINK", Buf);
        is_ok = FALSE;
      }
    }
  }

  if (!is_ok)
  {
    /* Delete all created shaders */
    for (auto s : shdr)
      if (s.Id != 0)
      {
        if (ProgId != 0)
          glDetachShader(ProgId, s.Id);
        glDeleteShader(s.Id);
      }
    /* Delete program */
    if (ProgId != 0)
      glDeleteProgram(ProgId);
    ProgId = 0;
  }
} /* End of 'Load' function */

/* Shader create function.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       const std::string &FileNamePrefix;
 * RETURNS: None.
 */
VOID kigl::shader::Create( const std::string &FileNamePrefix )
{
  Name = FileNamePrefix;
  Load();
} // End of 'shader' function

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID kigl::shader::Free( VOID )
{
  INT n;
  UINT shds[5];

  if (ProgId == 0)
    return;

  glGetAttachedShaders(ProgId, 5, &n, shds);

  for (INT i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shds[i]);
    glDeleteShader(shds[i]);
  }
  glDeleteProgram(ProgId);
  ProgId = 0;
} /* End of 'Free' function */

/* Get programm id function 
 * ARGUMENTS: None.
 * RETURNS: None.
 */
INT kigl::shader::GetId( VOID )
{
  return ProgId;
} /* End of 'GetId" function */

/* Update shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID kigl::shader::Update( VOID )
{
  Free();
  Load();
} /* End of 'Update' function */

/* Apply shader function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UINT) SHader program id.
 */
UINT kigl::shader::Apply( VOID )
{
  if (glIsProgram(ProgId))
    glUseProgram(ProgId);
  return ProgId;
} /* End of 'Apply' function */

/* Shader uniform value set function.
 * ARGUMENTS:
 *   - uniform name:
 *       const std::string &Name;
 *   - uniform value:
 *       const value_type &Value;
 *   - shader name:
 *       const  CHAR *Shd;
 * RETURNS: None.
 */
template<typename value_type>
VOID kigl::shader::VariableSend( const std::string &Name, const value_type &Value )
{
  INT loc;
  
  if ((loc = glGetUniformLocation(ProgId, Name.c_str())) != -1)
    if constexpr (std::is_convertible_v<FLT, value_type>)
      glUniform1f(loc, Value);
    else if constexpr (std::is_convertible_v<INT, value_type>)
      glUniform1i(loc, Value);
    else if constexpr (std::is_convertible_v<vec3, value_type>)
      glUniform3fv(loc, 1, Value);
    else if constexpr (std::is_convertible_v<matr, value_type>)
      glUniformMatrix4fv(loc, 1, FALSE, Value);
} /* End of 'UniSet' function */

/* END OF 'shader.cpp' FILE */  