/* FILE NAME  : skysphere.h
 * PROGRAMMER : AL6
 * LAST UPDATE: 28.07.2021
 * PURPOSE    : prims collection functions realization
 */

#ifndef __skysphere_h_
#define __skysphere_h_

#include "../../../kigl.h"

// kigl namespace
namespace kigl 
{
  // Forward declaration
  class primitive;
  class material;

  /* Models class */
  class skysphere
  {
  private:
    friend class render;

    // Sky sphere rendering objects
    primitive *Prim;
    material *Mtl;

  public:
    /* Class constructor */
    skysphere( VOID );

    /* Class constructor.
     * ARGUMENTS:
     *   - file name to laod from:
     *       const std::string &FileName;
     */
    skysphere( const std::string &FileName );

    /* Model destructor */
    ~skysphere( VOID );
  }; // End of 'skysphere' class
} // End of kigl namespace

#endif /* __skysphere__h_ */

/* END OF 'skysphere.h' FILE */
