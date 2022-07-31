/* FILE NAME  : shader.h
 * PROGRAMMER : AL6
 * LAST UPDATE: 26.07.2021
 * PURPOSE    : shadder realise module.
 */

#ifndef __shader_h_
#define __shader_h_

#include "../../../kigl.h"

namespace kigl
{
  // Shader class
  class shader 
  {
  private:
    UINT ProgId; // Shader programm id
  
    /* Load text from file function.
     * ARGUMENTS:
     *   - file name to be load from:
     *       const std::string &FileName;
     * RETURNS:
     *   (std::string) load text.
     */
    std::string LoadTextFile( const std::string &FileName );

    /* Store log to file function.
     * ARGUMENTS:
     *   - text 1 to save:
     *       const std::string &Stage;
     *   - text 2 to save:
     *       const std::string &Text;
     * RETURNS: None.
     */
    VOID Log( const std::string &Stage, const std::string &Text );

    /* Load shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Load( VOID );

  public:
    /* Shader name */
    std::string Name;

    /* Default constructor */
    shader( VOID ) : Name(), ProgId(0)
    {
    } /* End of default constructor */

    /* Default destructor */
    ~shader( VOID )
    {
    } // End of '~shader' function

    /* Shader create function.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     * RETURNS: None.
     */
    VOID Create( const std::string &FileNamePrefix );

    /* Free shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Get programm id function 
     * ARGUMENTS: None.
     * RETURNS: 
     *   (INT) prg.
     */
    INT GetId( VOID );

    /* Update shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID );

    /* Apply shader function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (UINT) SHader program id.
     */
    UINT Apply( VOID );

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
    VOID VariableSend( const std::string &Name, const value_type &Value );
  }; // End of 'shader' class
} // End of 'kigl' namespace

#endif /* __shader__h_ */

/* END OF 'shader.h' FILE */      
