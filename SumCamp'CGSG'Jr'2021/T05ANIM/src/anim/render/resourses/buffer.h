/* FILE NAME  : buffers.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 29.07.2021
 * PURPOSE    : uniform buffers realise module.
 */

#ifndef __buffers_h_
#define __buffers_h_

#include "../../../kigl.h"

// namespace for buffers manager
namespace kigl
{
  // class buffers
  class buffer
  {
  protected:
    UINT Id;        // PpenGL id
    UINT BindPoint; // Binding point for shader
    INT NumOfQuads; // Number of vec4

  public:
    /* Default constructor */
    buffer( VOID ) : Id(0), BindPoint(0), NumOfQuads(0)
    {
    } // End of 'buffer' function

    /* Class destructor */
    ~buffer( VOID )
    {
    } // End of '~buffer' function

    /* Create buffer function
     * ARGUMENTS: 
     *   - binding point:
     *       UINT BindingPoint;
     *   - pointer to structure:
     *       VOID *Ptr;
     * RETURNS: None.
     */
    template<typename type>
     VOID Create( UINT BindingPoint, const type *Ptr )
     {
       Free();
       BindPoint = BindingPoint;
       NumOfQuads = sizeof(*Ptr) / 16;
    
       glGenBuffers(1, &Id);
       glBindBuffer(GL_UNIFORM_BUFFER, Id);
       if (Ptr != nullptr)
         glBufferData(GL_UNIFORM_BUFFER, sizeof(*Ptr), Ptr, GL_STATIC_DRAW);
       glBindBuffer(GL_UNIFORM_BUFFER, 0);
     } // End of 'Create' function

     /* Create buffer function
     * ARGUMENTS: 
     *   - binding point:
     *       UINT BindingPoint;
     *   - buffer data type size:
     *       size_t TypeSize;
     * RETURNS: None.
     */
     VOID Create( UINT BindingPoint, size_t TypeSize )
     {
       Free();
       BindPoint = BindingPoint;
       NumOfQuads = TypeSize / 16;
    
       glGenBuffers(1, &Id);
       glBindBuffer(GL_UNIFORM_BUFFER, Id);
       glBufferData(GL_UNIFORM_BUFFER, TypeSize, nullptr, GL_STATIC_DRAW);
       glBindBuffer(GL_UNIFORM_BUFFER, 0);
     } // End of 'Create' function

    /* Get buffer id function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    UINT GetId( VOID )
    {
      return Id;
    } // End of 'GetId' function

    /* Apply buffers 
     * ARGUMENTS: None.
     * RETURNS: None.
     */ 
    VOID Apply( VOID )
    {
      if (BindPoint != 0 && Id != 0)
        glBindBufferBase(GL_UNIFORM_BUFFER, BindPoint, Id);
    } // End of 'Apply' function

    /* Update buffers 
     * ARGUMENTS:
     *   - data to update:
     *       VOID *Ptr;
     * RETURNS: None.
     */ 
    template<typename type>
    VOID Update( const type *Ptr )
    {
      if (BindPoint != 0 && Id != 0)
      {
        glBindBuffer(GL_UNIFORM_BUFFER, Id);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(*Ptr), Ptr);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
      }
    } // end of 'Update' function

    /* Free buffers 
     * ARGUMENTS: None.
     * RETURNS: None.
     */ 
    VOID Free( VOID )
    {
      if (Id != 0)
      {
        glDeleteBuffers(1, &Id);
        Id = 0;
        BindPoint = 0;
        NumOfQuads = 0;
      }
    } // End of 'Free' function
  }; // End of 'buffer' class
} // End of 'kigl' namespace

#endif /* __buffers__h_ */

/* END OF 'buffers.h' FILE */
