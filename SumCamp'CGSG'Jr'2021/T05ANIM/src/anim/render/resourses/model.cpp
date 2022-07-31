/* FILE NAME  : models.cpp
 * PROGRAMMER : AL6
 * LAST UPDATE: 28.07.2021
 * PURPOSE    : prims collection functions realization
 */

#include "../../../utilities/binary_reader.h"
#include "../../anim.h"

using namespace kigl;

/* Model constructor, which load if from *.g3dm file.
 * ARGUMENTS:
 *   - file to laod from name:
 *       const std::string FileName;
 *   - shadre for primitives name:
 *       const std::string &ShaderName;
 */
model::model( const std::string &FileName, const std::string &ShaderName ) : IsTransMatrixSet(FALSE)
{
  // Create binary file reader
  binary_reader rd(FileName);
  if (!rd.IsOk())
    return;

  // Model data loading
  DWORD sign, prim_count, materials_count, textures_count;
  rd(&sign), rd(&prim_count), rd(&materials_count), rd(&textures_count);

  // Check file sign
  if (sign != *(DWORD *)"G3DM")
    return;

#pragma region Primitives_Load
  // Primitive type for loading
  struct prim_template
  {
    std::vector<topology::vertex::std> V;
    std::vector<INT> I;
    INT VertexCount, IndexCount, MaterialNo;
  } *loaded_prims = new prim_template[prim_count];
  // Load primitives
  for (INT pr_no = 0; pr_no < prim_count; pr_no++)
  {
    // Loading primitive data
    rd(&loaded_prims[pr_no].VertexCount);
    rd(&loaded_prims[pr_no].IndexCount);
    rd(&loaded_prims[pr_no].MaterialNo);

    // Memory reserving
    loaded_prims[pr_no].V.reserve(loaded_prims[pr_no].VertexCount);
    loaded_prims[pr_no].I.reserve(loaded_prims[pr_no].IndexCount);

    // Loading vertices in primitive
    for (INT vert_no = 0; vert_no < loaded_prims[pr_no].VertexCount; vert_no++)
    {
      // Vertex data loading
      topology::vertex::std vert;
      rd(&vert.P), rd(&vert.T), rd(&vert.N), rd(&vert.C);

      // Adding vertex to primitive
      loaded_prims[pr_no].V.push_back(vert);
    }

    // Loafing indexes to primitive
    for (INT ind_no = 0; ind_no < loaded_prims[pr_no].IndexCount; ind_no++)
    {
      // Load index
      UINT ind;
      rd(&ind);

      // Add index to primitive
      loaded_prims[pr_no].I.push_back(ind);
    }
  }
#pragma endregion

#pragma region Materials_Load
  // Loaded material structure
  struct mtl_template
  {
    CHAR Name[300];
    material::material_data Data;
    INT TextureNo[8];
    CHAR ShaderName[300];
    INT ShaderNo;
  } *loaded_mtls = new mtl_template[materials_count];
  // Loading materials
  for (INT mtl_no = 0; mtl_no < materials_count; mtl_no++)
  {
    rd(loaded_mtls[mtl_no].Name, 300);

    vec3 Ka, Kd, Ks;
    FLT Ph, Tr;
    rd(&Ka);
    rd(&Kd);
    rd(&Ks);
    rd(&Ph);
    rd(&Tr);
    loaded_mtls[mtl_no].Data = material::material_data(Ka, Kd, Ks, Ph, Tr);

    rd(&loaded_mtls[mtl_no].TextureNo[0]);
    rd(&loaded_mtls[mtl_no].TextureNo[1]);
    rd(&loaded_mtls[mtl_no].TextureNo[2]);
    rd(&loaded_mtls[mtl_no].TextureNo[3]);
    rd(&loaded_mtls[mtl_no].TextureNo[4]);
    rd(&loaded_mtls[mtl_no].TextureNo[5]);
    rd(&loaded_mtls[mtl_no].TextureNo[6]);
    rd(&loaded_mtls[mtl_no].TextureNo[7]);

    rd(loaded_mtls[mtl_no].ShaderName, 300);
    rd(&loaded_mtls[mtl_no].ShaderNo);
  }
#pragma endregion

#pragma region Textures_Load
  // Loaded texture structure
  struct tex_template
  {
    CHAR Name[300];
    image Img;
  } *loaded_texs = new tex_template[textures_count];
  // Loading materials
  for (INT tex_no = 0; tex_no < textures_count; tex_no ++)
  {
    rd(loaded_texs[tex_no].Name, 300);
    rd(&loaded_texs[tex_no].Img.W);
    rd(&loaded_texs[tex_no].Img.H);
    rd(&loaded_texs[tex_no].Img.C);

    INT size = loaded_texs[tex_no].Img.W * loaded_texs[tex_no].Img.H * loaded_texs[tex_no].Img.C;
    loaded_texs[tex_no].Img.Bits = new BYTE[size];
    rd(loaded_texs[tex_no].Img.Bits, size);
  }
#pragma endregion

#pragma region Primitives_Creation

  for (INT pr_no = 0; pr_no < prim_count; pr_no++)
  {
    anim *Ani = anim::GetPtr();
    topology::trimesh Topo(loaded_prims[pr_no].V, loaded_prims[pr_no].I);

    mtl_template MtlTempl = loaded_mtls[loaded_prims[pr_no].MaterialNo];

    material *Mtl;
    if (MtlTempl.TextureNo[0] != -1)
    {
      tex_template TexTempl = loaded_texs[MtlTempl.TextureNo[0]];
      Mtl = Ani->MaterialCreateFromImage(MtlTempl.Name, MtlTempl.Data, ShaderName, TexTempl.Name, TexTempl.Img);
    }
    else
      Mtl = Ani->MaterialCreateNoTexture(MtlTempl.Name, MtlTempl.Data, ShaderName);

    PrimitivesCollection.push_back(Ani->PrimitiveCreate(Topo, Mtl));
  }
#pragma endregion

  delete[] loaded_prims;
  delete[] loaded_mtls;
  delete[] loaded_texs;
} // End of 'model::model' function

/* Model destructor */
model::~model( VOID )
{
  anim *Ani = anim::GetPtr();
  for (auto prim: PrimitivesCollection)
    Ani->PrimitiveFree(prim);
} // End of 'model::~model' function

/* Set primitive translate matrix function.
 * ARGUMENTS:
 *   - new translate matrix:
 *       const matr &Trans;
 * RETURNS: None.
 */
VOID model::SetTrans( const matr &Trans )
{
  this->Trans = Trans;
  IsTransMatrixSet = TRUE;
} // End of 'SetTrans' function

/* END OF 'models.cpp' FILE */
