/* FILE NAME  : buffer_manager.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Buffer manager type declaration module.
 */

#ifndef __buffer_manager_h_
#define __buffer_manager_h_

#include "../resourses/buffer.h"
#include "resourses_manager.h"

namespace kigl
{
  // Buffer manager class
  class buffer_manager : public resourses_manager<buffer, INT>
  {
  public:
    /* Create buffer function
     * ARGUMENTS: 
     *   - binding point:
     *       UINT BindingPoint;
     *   - pointer to structure:
     *       VOID *Ptr;
     * RETURNS:
     *   (buf &) pointer to buffer
     */
    template<typename type>
    buffer * BufferCreate( UINT BindingPoint, const type *Ptr )
    {
      buffer Buf;
      Buf.Create(BindingPoint, Ptr);

      return Add(Buf);
    } /* End of 'CreateBuffers' function */

    /* Create buffer function
     * ARGUMENTS: 
     *   - binding point:
     *       UINT BindingPoint;
     *   - buffer data type size:
     *       size_t TypeSize;
     * RETURNS:
     *   (buf &) pointer to buffer
     */
    buffer * BufferCreate( UINT BindingPoint, size_t TypeSize )
    {
      buffer Buf;
      Buf.Create(BindingPoint, TypeSize);

      return Add(Buf);
    } /* End of 'CreateBuffers' function */

    /* Buffer delition function.
     * ARGUMENTS:
     *   - buffer:
     *       buffer *Buf;
     * RETURNS: None.
     */
    VOID BufferFree( buffer *Buf )
    {
      if (Buf != nullptr)
        Delete(Buf);
    } // End of 'BufferCreate' function
  }; // End of 'buffer_manager' class
}

#endif // !__buffer_manager_h_

// END OF 'buffer_manager.h' FILE