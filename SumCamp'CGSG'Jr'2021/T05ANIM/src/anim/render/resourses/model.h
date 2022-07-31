/* FILE NAME  : models.h
 * PROGRAMMER : AL6
 * LAST UPDATE: 28.07.2021
 * PURPOSE    : prims collection functions realization
 */

#ifndef __models_h_
#define __models_h_

#include "../../../kigl.h"
#include <vector>
#include <string>

// kigl namespace
namespace kigl 
{
  // Forward declaration
  class primitive;

  /* Models class */
  class model
  {
  private:
    friend class render;

    std::vector<primitive *> PrimitivesCollection; // Primitives that make up the model
    matr Trans = matr::Identity();                 // Model translate matrix
    BOOL IsTransMatrixSet;                         // Translate matrix set flag

  public:
    /* Model constructor, which load if from *.g3dm file.
     * ARGUMENTS:
     *   - file to laod from name:
     *       const std::string &FileName;
     *   - shadre for primitives name:
     *       const std::string &ShaderName;
     */
    model( const std::string &FileName, const std::string &ShaderName = "default" );

    /* Model destructor */
    ~model( VOID );

    /* Set primitive translate matrix function.
     * ARGUMENTS:
     *   - new translate matrix:
     *       const matr &Trans;
     * RETURNS: None.
     */
    VOID SetTrans( const matr &Trans );
  };
} // end of kigl namespace

#endif /* __models__h_ */

/* END OF 'models.h' FILE */
