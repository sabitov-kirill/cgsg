/* FILE NAME  : render_primitives.cpp
 * PROGRAMMER : KS6
 * LAST UPDATE: 23.07.2021
 * PURPOSE    : Render system handle module.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "../anim.h"

using namespace kigl;

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
VOID render::PrimitiveDraw( const primitive *Prim, const matr &World, INT InstanceCount ) const
{
  // Check for exist
  if (Prim == nullptr)
    return;

  // Apply primitive material shader if exist
  if (Prim->Mtl != nullptr && Prim->Mtl->Shd != nullptr)
  {
    // Load material params to shader
    Prim->Mtl->Apply();

    // Load primitive matrices to shader
    anim *Ani = anim::GetPtr();
    matr w = Prim->IsTransMatrixSet ? Prim->Trans * World : World;
    matr wvp = w * Camera.VP;
    primitive_data data(w, wvp);
    PrimitiveDataBuf->Update(&data);
  }

  // Drawing primitive depending on type and index array existance
  INT PrimitiveGLType =
    Prim->Type == topology::primitive_type::TRIMESH  ? GL_TRIANGLES      :
    Prim->Type == topology::primitive_type::TRISTRIP ? GL_TRIANGLE_STRIP :
    Prim->Type == topology::primitive_type::LINES    ? GL_LINES          :
    Prim->Type == topology::primitive_type::POINTS   ? GL_POINTS         :
                                                       GL_PATCHES;

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  glBindVertexArray(Prim->VA);
  if (InstanceCount < 2)
    if (Prim->IBuf != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Prim->IBuf);
      glDrawElements(PrimitiveGLType, Prim->NumOfEllements, GL_UNSIGNED_INT, nullptr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
    else
    {
      glDrawArrays(PrimitiveGLType, 0, Prim->NumOfEllements);
      glBindVertexArray(0);
    }
  else
    if (Prim->IBuf != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Prim->IBuf);
      glDrawElementsInstanced(PrimitiveGLType, Prim->NumOfEllements, GL_UNSIGNED_INT, nullptr, InstanceCount);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
    else
    {
      glDrawArraysInstanced(PrimitiveGLType, 0, Prim->NumOfEllements, InstanceCount);
      glBindVertexArray(0);
    }
  glBindVertexArray(0);
} // End of 'PrimitiveDraw' function

/* Primitive draw function withou world matrix.
 * ARGUMENTS:
 *   - primitive to draw:
 *       const primitive &Prim;
 *   - instance count:
 *       INT InstanceCount;
 * RETURNS: None.
 */
VOID render::PrimitiveDraw( const primitive *Prim, INT InstanceCount ) const
{
  // Check for exist
  if (Prim == nullptr)
    return;

  INT PrimitiveGLType =
    Prim->Type == topology::primitive_type::TRIMESH  ? GL_TRIANGLES      :
    Prim->Type == topology::primitive_type::TRISTRIP ? GL_TRIANGLE_STRIP :
    Prim->Type == topology::primitive_type::LINES    ? GL_LINES          :
    Prim->Type == topology::primitive_type::POINTS   ? GL_POINTS         :
                                                       GL_PATCHES;
  
  // Apply primitive material shader if exist
  if (Prim->Mtl != nullptr && Prim->Mtl->Shd != nullptr)
  {
    // Load material data to shader
    Prim->Mtl->Apply();

    // Load primitive matrices to shader
    anim *Ani = anim::GetPtr();
    matr wvp = Prim->IsTransMatrixSet ? Prim->Trans * Camera.VP : Camera.VP;
    primitive_data data(matr::Identity(), wvp);
    PrimitiveDataBuf->Update(&data);
    PrimitiveDataBuf->Apply();
  }

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  glBindVertexArray(Prim->VA);
  if (InstanceCount < 2)
    if (Prim->IBuf != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Prim->IBuf);
      glDrawElements(PrimitiveGLType, Prim->NumOfEllements, GL_UNSIGNED_INT, nullptr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
      glDrawArrays(PrimitiveGLType, 0, Prim->NumOfEllements);
  else
    if (Prim->IBuf != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Prim->IBuf);
      glDrawElementsInstanced(PrimitiveGLType, Prim->NumOfEllements, GL_UNSIGNED_INT, nullptr, InstanceCount);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
      glDrawArraysInstanced(PrimitiveGLType, 0, Prim->NumOfEllements, InstanceCount);
  glBindVertexArray(0);
} // End of 'PrimitiveDraw' function

/* Model draw function.
 * ARGUMENTS:
 *   - model:
 *       const model &Mdl;
 *   - world matrix:
 *       const matr &World
 *   - instance count:
 *       INT InstanceCount;
 * RETURNS: None.
 */
VOID render::ModelDraw( const model &Mdl, const matr &World, INT InstanceCount ) const
{
  // Check for exist
  if (Mdl.PrimitivesCollection.empty())
    return;

  // Draw all model primitives
  matr w = Mdl.IsTransMatrixSet ? Mdl.Trans * World : World;
  for (auto prim: Mdl.PrimitivesCollection)
    PrimitiveDraw(prim, w, InstanceCount);
} // End of 'ModelDraw' function

/* Model draw function.
 * ARGUMENTS:
 *   - model:
 *       const model *Mdl;
 *   - instance count:
 *       INT InstanceCount;
 * RETURNS: None.
 */
VOID render::ModelDraw( const model &Mdl, INT InstanceCount ) const
{
  // Check for exist
  if (Mdl.PrimitivesCollection.empty())
    return;

  // Draw all model primitives
  if (Mdl.IsTransMatrixSet)
    for (auto prim: Mdl.PrimitivesCollection)
      PrimitiveDraw(prim, Mdl.Trans, InstanceCount);
  else
    for (auto prim: Mdl.PrimitivesCollection)
      PrimitiveDraw(prim, InstanceCount);
} // End of 'ModelDraw' function

/* Sky sphere draw function.
 * ARGUMENTS:
 *   - sky sphere:
 *       const skysphere *Sky;
 * RETURNS: None.
 */
VOID render::SkyDraw( const skysphere &Sky )
{
  glDisable(GL_DEPTH_TEST);
  glDepthMask(FALSE);
  PrimitiveDraw(Sky.Prim);
  glDepthMask(TRUE);
  glEnable(GL_DEPTH_TEST);
} // End of 'render::SkyDraw' function

// END OF 'render_primitives.cpp' FILE