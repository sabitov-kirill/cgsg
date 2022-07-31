/* FILE NAME  : render.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Render system declaration module.
 */

#ifndef __render_h_
#define __render_h_

#include <string>

#include "storage/primitive_manager.h"
#include "storage/shader_manager.h"
#include "storage/material_manager.h"
#include "storage/texture_manager.h"
#include "storage/buffer_manager.h"

#include "resourses/model.h"
#include "resourses/skysphere.h"

namespace kigl
{
  // Render system type
  class render : 
    public primitive_manager, public shader_manager,
    public material_manager, public texture_manager,
    public buffer_manager
  {
  private:
    const HWND &hRndWnd;        // Window to dender descriptor
    const HDC hRndDC;           // Window to dender device context handle
    const INT &FrameW, &FrameH; // Window to render frame size

    HGLRC hRndGLRC;             // OpenGL rendering context

    // Render data structure to pass to shader
    struct render_data
    {
      vec4 CamDir;
      vec4 CamLocW;
      vec4 CamRightH;
      vec4 CamUpTime;

      /* Structre constructor.
       * ARGUMENTS:
       *   - camera data:
       *       vec3 CamDir, vec3 CamLoc, vec3 CamRight, vec3 CamUp;
       *   - frame size:
       *       INT FrameW, INT FrameH;
       *   - time:
       *       FLT Time;
       */
      render_data( vec3 CamDir, vec3 CamLoc, vec3 CamRight, vec3 CamUp, INT FrameW, INT FrameH, FLT Time ) :
        CamLocW(CamLoc, FrameW), CamRightH(CamRight, FrameH), CamUpTime(CamUp, Time), CamDir(CamDir, 1)
      {
      } // end of 'render_data' function 
    }; // End of 'render_data' structure
    // Primitive data structure to pass to shader
    struct primitive_data
    {
      mth::matr_data<FLT> MatrW;
      mth::matr_data<FLT> MatrWVP;

      /* Structure construtor.
       * ARGUMENTS:
       *   - primitive world matrix:
       *       const matr *MatrW;
       *   - primitive world view matrix:
       *       const matr *MatrWVP;
       */
      primitive_data( const mth::matr_data<FLT> &MatrW, const mth::matr_data<FLT> &MatrWVP ) :
        MatrW(MatrW), MatrWVP(MatrWVP)
      {
      } // End of 'primitive_data' function
    }; // End of 'primitive_data' structure

    // Render data buffer
    buffer *RenderDataBuf;
    // Primitive data buffer
    buffer *PrimitiveDataBuf;
  public:
    // Projection user camera
    camera Camera;

    /* Render system type constructor.
     * ARGUMENTS:
     *   - window handle ref:
     *       HWND &hWnd;
     *   - window size ref:
     *       INT &W, &H;
     */
    render( HWND &hWnd, INT &W, INT &H );

    /* Render system type destructor.
     * ARGUMENTS: None.
     */
    ~render( VOID );

    /* Render init function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Render closer function to use instead of destructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );

    /* Rendring resizing function.
     * ARGUMENTS: None
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* Rendring copy frame function.
     * ARGUMENTS:
         - WINDOW HANDLE:
             HWND hWnd;
     * RETURNS: None.
     */
    VOID CopyFrame( VOID );

    /* Rendring start function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Start( VOID );

    /* Rendring end function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */ 
    VOID End( VOID );

    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive to draw:
     *       const primitive &Prim;
     *   - world matrix:
     *       const matr &World;
     *   - instance count:
     *       INT InstanceCount;
     * RETURNS: None.
     */
    VOID PrimitiveDraw( const primitive *Prim, const matr &World, INT InstanceCount = 1 ) const;

    /* Primitive draw function withou world matrix.
     * ARGUMENTS:
     *   - primitive to draw:
     *       const primitive &Prim;
     *   - world matrix:
     *       const matr &World;
     *   - instance count:
     *       INT InstanceCount;
     * RETURNS: None.
     */
    VOID PrimitiveDraw( const primitive *Prim, INT InstanceCount = 1 ) const;

    /* Model draw function.
     * ARGUMENTS:
     *   - model:
     *       const model &Mdl;
     *   - world matrix:
     *       const matr &World;
     *   - instance count:
     *       INT InstanceCount;
     * RETURNS: None.
     */
    VOID ModelDraw( const model &Mdl, const matr &World, INT InstanceCount = 1 ) const;

    /* Model draw function.
     * ARGUMENTS:
     *   - model:
     *       const model &Mdl;
     *   - instance count:
     *       INT InstanceCount;
     * RETURNS: None.
     */
    VOID ModelDraw( const model &Mdl, INT InstanceCount = 1 ) const;

    /* Sky activation function.
     * ARGUMENTS:
     *   - sky sphere:
     *       const skysphere &Sky;
     * RETURNS: None.
     */
    VOID SkyActivate( const skysphere &Sky );

  private:
    skysphere ActiveSky;

    /* Sky sphere draw function.
     * ARGUMENTS:
     *   - sky sphere:
     *       const skysphere *Sky;
     * RETURNS: None.
     */
    VOID SkyDraw( const skysphere &Sky );
  };
}

#endif // !__render_h_

// END OF 'render.h' FILE