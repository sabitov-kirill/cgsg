/* FILE NAME  : topology.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Topology type declaration module.
 */

#ifndef __topology_h_
#define __topology_h_

#include "image.h"
#include "vertex.h"
#include <fstream>
#include <vector>

namespace kigl
{
  // Forward declaration
  class primitive;

  namespace topology
  {
    /* Primitive type */
    enum class primitive_type
    {
      TRIMESH, // Triangle mesh - array of triangles
      TRISTRIP, // Triangle strip - array of stripped triangles
      LINES, // Line segments (by 2 points)
      POINTS, // Array of points
      PATCHES, // Tesselation patches
    };

    // Base topology class
    template<typename vertex_type>
    class base
    {
    private:
      friend class ::kigl::primitive;

    public:
      std::vector<vertex_type> Vert{}; // Vertecies storage
      std::vector<INT> Ind{};          // Vertecies indexes to connect storage
      topology::primitive_type Type{};      // Primitive type

      vec3 Min, Max; // Bound Box

      /* Class default constructor */
      base(VOID)
      {
      } /* End of 'base' function */

      /* Class constructor.
        * ARGUMENTS:
        *   - primitive type:
        *       topology::prim_type PrimitiveType;
        *   - vertex array:
        *       const std::vector<vertex_type> &NewV;
        *   - index array:
        *       const std::vector<INT> &NewI;
        */
      base(topology::primitive_type PrimitiveType, const std::vector<vertex_type>& NewV = {}, const std::vector<INT>& NewI = {}) :
        Type(PrimitiveType), Vert(NewV), Ind(NewI)
      {
      } /* End of 'base' function */

      /* Bounf box evaluation method.
        * ARGUMENTS: None.
        * RETURNS: None.
        */
      virtual VOID EvaluateBoundBox(VOID)
      {
        for (auto v : Vert) Min = vec3::Min(Min, v.P), Max = vec3::Max(Max, v.P);
      } // End of 'EvaluateBoundBox' function

      /* Evaluate trimesh vertex normals function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      virtual VOID EvaluateNormals(VOID)
      {
      } // End of 'EvaluateNormals' function
    };

    // Trimesh topology type
    class trimesh : public base<vertex::std>
    {
    public:
      /* Class default constructor */
      trimesh(VOID)
      {
      } /* End of 'trimesh' function */

      /* Trimesh constructor.
       * ARGUMENTS:
       *   - vertex array:
       *       const std::vector<vertex> &NewV;
       *   - index array:
       *       const std::vector<INT> &NewI;
       */
      trimesh(const std::vector<vertex::std>& NewV, const std::vector<INT>& NewI = {}) :
        base<vertex::std>(primitive_type::TRIMESH, NewV, NewI)
      {
        // Calcualting normals and bound box
        EvaluateBoundBox();
        EvaluateNormals();
      } /* End of 'trimesh' function */

      /* Trimesh loading from file constructor.
       * ARGUMENTS:
       *   - file name:
       *       const std::string FileName;
       */
      trimesh(const std::string& FileName) : base<vertex::std>()
      {
        std::fstream f(FileName, std::fstream::in);

        if (!f.is_open())
          return;

        // Getting vertecies and indexes from file, pushing to arrays
        CHAR Buf[1000];
        while (!f.eof())
        {
          f.getline(Buf, sizeof(Buf) - 1);

          if (Buf[0] == 'v' && Buf[1] == ' ')
          {
            FLT x, y, z;

            sscanf_s(Buf + 2, "%f%f%f", &x, &y, &z);
            this->Vert.push_back(vertex::std(vec3(x, y, z), vec2(x, y)));
          }
          else if (Buf[0] == 'f' && Buf[1] == ' ')
          {
            INT n1, n2, n3;

            /* Read one of possible facet references */
            sscanf_s(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
              sscanf_s(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
              sscanf_s(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
              sscanf_s(Buf + 2, "%d %d %d", &n1, &n2, &n3);
            n1--;
            n2--;
            n3--;
            this->Ind.push_back(n1);
            this->Ind.push_back(n2);
            this->Ind.push_back(n3);
          }
        }
        f.close();

        // Calcualting normals and bound box
        EvaluateBoundBox();
        EvaluateNormals();
      } /* End of 'trimesh' function */

      /* Evaluate trimesh vertex normals function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID EvaluateNormals(VOID) override
      {
        for (INT i = 3; i < this->Ind.size(); i += 3)
        {
          vec3 N = ~((this->Vert[this->Ind[i + 1]].P - this->Vert[this->Ind[i]].P) % (this->Vert[this->Ind[i + 2]].P - this->Vert[this->Ind[i]].P));

          this->Vert[this->Ind[i + 0]].N = ~(this->Vert[this->Ind[i + 0]].N + N);
          this->Vert[this->Ind[i + 1]].N = ~(this->Vert[this->Ind[i + 1]].N + N);
          this->Vert[this->Ind[i + 2]].N = ~(this->Vert[this->Ind[i + 2]].N + N);
        }
      } // End of 'EvalNormals' function
    };

    // Grid topology type
    class grid : public base<vertex::std>
    {
    protected:
      /* Grid size */
      INT W, H;

    public:
      /* Class default constructor */
      grid(VOID) : W(0), H(0)
      {
      } /* End of 'grid' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - grid size:
       *       INT NewW, NewH;
       *   - griw squares size:
       *       INT Size
       */
      grid(INT NewW, INT NewH, INT Size = 1)
      {
        Create(NewW, NewH, Size);

        // Calcualting normals and bound box
        EvaluateBoundBox();
        EvaluateNormals();
      } // End of 'grid' function

      /* Class constructor.
       * ARGUMENTS:
       *   - vertices:
       *       const std::vector<vertex::std> &V;
       *   - grid size:
       *       INT NewW, NewH;
       */
      grid(const std::vector<vertex::std>& V, INT NewW, INT NewH)
      {
        Create(V, NewW, NewH);

        // Calcualting normals and bound box
        EvaluateBoundBox();
        EvaluateNormals();
      } // End of 'grid' function

      /* Class constructor.
       * ARGUMENTS:
       *   - grid size:
       *       INT NewW, NewH;
       *   - griw squares size:
       *       INT Size
       */
      VOID Create(INT NewW, INT NewH, INT Size = 1)
      {
        // Set Data
        W = NewW, H = NewH;
        Type = primitive_type::TRISTRIP, Vert = {}, Ind = {};

        // Generating vertives
        for (INT i = 0; i < NewH; i += Size)
          for (INT j = 0; j < NewW; j += Size)
            Vert.push_back(vertex::std(vec3(i, 0, j), vec2(i, j)));

        // Generating indexes
        INT k = 0;
        for (INT i = 0; i < H - 1; i++)
        {
          for (INT j = 0; j < W; j++)
          {
            Ind.push_back((i + 1) * W + j);
            Ind.push_back((i + 0) * W + j);
          }
          if (i != H - 2)
            Ind.push_back(-1);
        }
      } // End of 'grid' function

      /* Class constructor.
       * ARGUMENTS:
       *   - vertices:
       *       const std::vector<vertex::std> &V;
       *   - grid size:
       *       INT NewW, NewH;
       */
      VOID Create(const std::vector<vertex::std>& V, INT NewW, INT NewH)
      {
        // Set data
        W = NewW, H = NewH;
        Type = primitive_type::TRISTRIP, Vert = V, Ind = {};

        // Generating indexes
        INT k = 0;
        for (INT i = 0; i < H - 1; i++)
        {
          for (INT j = 0; j < W - 1; j++)
          {
            Ind.push_back((i + 1) * W + j);
            Ind.push_back((i + 0) * W + j);
          }
          if (i != H - 2)
            Ind.push_back(-1);
        }
      } // End of 'grid' function

      /* Obtain grid width function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (INT) grid width.
        */
      INT GetW(VOID) const
      {
        return W;
      } /* End of 'GetW' function */
      /* Obtain grid height function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (INT) grid height.
        */
      INT GetH(VOID) const
      {
        return H;
      } /* End of 'GetH' function */
      /* Grid 2D array vertex access function.
        * ARGUMENTS:
        *   - row index:
        *       INT Row;
        * RETURNS:
        *   (vertex *) vertex row pointer.
        */
      vertex::std* operator[](INT Row)
      {
        return &this->Vert[mth::Clamp(Row, 0, H) * W];
      } /* End of 'operator[]' function */

      /* Evaluate grid vertex normals function.
        * ARGUMENTS: None.
        * RETURNS: None.
        */
      VOID EvaluateNormals(VOID) override
      {
        INT i, j;

        for (i = 0; i < H - 1; i++)
          for (j = 0; j < W - 1; j++)
          {
            vertex::std
              * P00 = &Vert[(i + 0) * W + j + 0],
              * P01 = &Vert[(i + 0) * W + j + 1],
              * P10 = &Vert[(i + 1) * W + j + 0],
              * P11 = &Vert[(i + 1) * W + j + 1];
            vec3 N;

            N = ~((P00->P - P10->P) % (P11->P - P10->P));
            P00->N = ~(P00->N + N);
            P10->N = ~(P10->N + N);
            P11->N = ~(P11->N + N);

            N = ~((P11->P - P01->P) % (P00->P - P01->P));
            P00->N = ~(P00->N + N);
            P01->N = ~(P01->N + N);
            P11->N = ~(P11->N + N);
          }
      }
    };

    // Mobius strip topology type
    class mobius_strip : public grid
    {
    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - centr and raius of strip:
       *       FLT Rad;
       *   - splices count:
       *       INT Splices;
       *   - strip height:
       *       FLT Height;
       *   - rotations iterations:
       *       INT Iteratins;
       */
      mobius_strip(FLT Rad, INT Splices, FLT Height, FLT Iteratins = 0.5)
      {
        std::vector<vertex::std> V;
        FLT angle_addition = 2 * mth::PI / Splices;
        FLT width_addition = Splices / (2 * mth::PI / angle_addition);
        FLT u;

        u = 0;
        for (INT i = 0; i <= Splices; i++, u += angle_addition)
        {
          vec3 up((Rad + Height * 0.5 * cos(u * Iteratins)) * cos(u),
            Height * 0.5 * sin(u * Iteratins),
            (Rad + Height * 0.5 * cos(u * Iteratins)) * sin(u));

          V.push_back(vertex::std(up, vec2(up[0], up[1])));
        }
        V.push_back(V[0]);
        INT sz = V.size();
        u = 0;
        for (INT i = 0; i <= Splices; i++, u += angle_addition)
        {
          vec3 dn((Rad - 0.5 * cos(u * Iteratins)) * cos(u),
            -0.5 * sin(u * Iteratins),
            (Rad - 0.5 * cos(u * Iteratins)) * sin(u));
          V.push_back(vertex::std(dn, vec2(dn[0], dn[1])));
        }
        V.push_back(V[sz - 1]);

        grid::Create(V, Splices + 2, 2);
        EvaluateBoundBox();
        EvaluateNormals();
      } // End of 'mobius_strip' function
    };

    // Cube topology type
    class cube : public base<vertex::std>
    {
    public:
      /* Class contructor.
       * ARGUMENTS:
       *   - points, setting cube:
       *       const vec3 &A, const vec3 &B
       */
      cube(const vec3& A, const vec3& B) : base(primitive_type::TRISTRIP)
      {
        // Front
        Vert.push_back(vertex::std(vec3(A), vec2(A[0], A[1]), vec3(0, 0, -1)));
        Vert.push_back(vertex::std(vec3(A[0], B[1], A[2]), vec2(A[0], B[1]), vec3(0, 0, -1)));
        Vert.push_back(vertex::std(vec3(B[0], A[1], A[2]), vec2(B[0], A[1]), vec3(0, 0, -1)));
        Vert.push_back(vertex::std(vec3(B[0], B[1], A[2]), vec2(B[0], B[1]), vec3(0, 0, -1)));

        Ind.push_back(0);
        Ind.push_back(1);
        Ind.push_back(2);
        Ind.push_back(3);
        Ind.push_back(-1);

        // Right
        Vert.push_back(vertex::std(vec3(B[0], A[1], A[2]), vec2(A[1], A[2]), vec3(1, 0, 0)));
        Vert.push_back(vertex::std(vec3(B[0], B[1], A[2]), vec2(B[1], A[2]), vec3(1, 0, 0)));
        Vert.push_back(vertex::std(vec3(B[0], A[1], B[2]), vec2(A[1], B[2]), vec3(1, 0, 0)));
        Vert.push_back(vertex::std(vec3(B), vec2(B[1], B[2]), vec3(1, 0, 0)));

        Ind.push_back(4);
        Ind.push_back(5);
        Ind.push_back(6);
        Ind.push_back(7);
        Ind.push_back(-1);

        // Back
        Vert.push_back(vertex::std(vec3(B[0], A[1], B[2]), vec2(B[0], A[1]), vec3(0, 0, 1)));
        Vert.push_back(vertex::std(vec3(B), vec2(B[0], B[1]), vec3(0, 0, 1)));
        Vert.push_back(vertex::std(vec3(A[0], A[1], B[2]), vec2(A[0], A[1]), vec3(0, 0, 1)));
        Vert.push_back(vertex::std(vec3(A[0], B[1], B[2]), vec2(A[0], B[1]), vec3(0, 0, 1)));

        Ind.push_back(8);
        Ind.push_back(9);
        Ind.push_back(10);
        Ind.push_back(11);
        Ind.push_back(-1);

        // Left
        Vert.push_back(vertex::std(vec3(A[0], A[1], B[2]), vec2(A[1], B[2]), vec3(-1, 0, 0)));
        Vert.push_back(vertex::std(vec3(A[0], B[1], B[2]), vec2(B[1], B[2]), vec3(-1, 0, 0)));
        Vert.push_back(vertex::std(vec3(A), vec2(A[1], A[2]), vec3(-1, 0, 0)));
        Vert.push_back(vertex::std(vec3(A[0], B[1], A[2]), vec2(B[1], A[2]), vec3(-1, 0, 0)));

        Ind.push_back(12);
        Ind.push_back(13);
        Ind.push_back(14);
        Ind.push_back(15);
        Ind.push_back(-1);

        // Top
        Vert.push_back(vertex::std(vec3(A[0], B[1], A[2]), vec2(A[0], A[2]), vec3(0, 1, 0)));
        Vert.push_back(vertex::std(vec3(A[0], B[1], B[2]), vec2(A[0], B[2]), vec3(0, 1, 0)));
        Vert.push_back(vertex::std(vec3(B[0], B[1], A[2]), vec2(B[0], A[2]), vec3(0, 1, 0)));
        Vert.push_back(vertex::std(vec3(B), vec2(B[0], B[2]), vec3(0, 1, 0)));

        Ind.push_back(16);
        Ind.push_back(17);
        Ind.push_back(18);
        Ind.push_back(19);
        Ind.push_back(-1);

        // Bottom
        Vert.push_back(vertex::std(vec3(A), vec2(A[0], A[2]), vec3(0, -1, 0)));
        Vert.push_back(vertex::std(vec3(A[0], A[1], B[2]), vec2(A[0], B[2]), vec3(0, -1, 0)));
        Vert.push_back(vertex::std(vec3(B[0], A[1], A[2]), vec2(B[0], A[2]), vec3(0, -1, 0)));
        Vert.push_back(vertex::std(vec3(B[0], A[1], B[2]), vec2(B[0], B[2]), vec3(0, -1, 0)));

        Ind.push_back(20);
        Ind.push_back(21);
        Ind.push_back(22);
        Ind.push_back(23);
        Ind.push_back(-1);
      } // End of 'cube' function
    };

    // Sphere topology type
    class sphere : public grid
    {
    public:
      /* Class contructor.
       * ARGUMENTS:
       *   - sphere centr:
       *       const vec3 &C;
       *   - sphere radius:
       *       DBL R;
       *   - sphere slices count:
       *       INT Splices;
       */
      sphere(const vec3& C = vec3(0), DBL R = 1, INT Splices = 30)
      {
        std::vector<vertex::std> V;

        for (INT i = 0; i < Splices + 2; i++)
        {
          DBL theta = static_cast<DBL>(i) / Splices * mth::PI;
          for (INT j = 0; j < Splices + 2; j++)
          {
            DBL phi = static_cast<DBL>(j) / Splices * 2 * mth::PI;

            vertex::std v;
            v.C = vec4(0);
            v.T = vec2(static_cast<FLT>(j) / Splices, static_cast<FLT>(i) / Splices);
            v.N = vec3(sin(theta) * sin(phi),
              cos(theta),
              sin(theta) * cos(phi));
            v.P = v.N * R + C;
            V.emplace_back(v);
          }
        }

        grid::Create(V, Splices + 2, Splices + 2);
        EvaluateBoundBox();
      } // End of 'sphere' function
    };

    // Height map topology type
    class height_map : public grid
    {
    public:
      /* Class contructor.
       * ARGUMENTS:
       *   - file name:
       *       const std::string &FileName;
       *   - size params:
       *       FLT Spacing = 1, FLT HeightMultiplyer = 1;
       */
      height_map(const std::string& FileName, FLT Spacing = 1, FLT HeightMultiplyer = 1)
      {
        image Img(FileName);
        std::vector<vertex::std> V;

        for (INT i = 0; i < Img.H; i++)
          for (INT j = 0; j < Img.W; j++)
          {
            vec3 Pos(i * Spacing, Img.Bits[(i * Img.W + j) * Img.C] * HeightMultiplyer, j * Spacing);
            vec2 TexCoords = vec2(Pos[0], Pos[2]);

            V.push_back(vertex::std(Pos, TexCoords));
          }

        grid::Create(V, Img.W, Img.H);
        EvaluateBoundBox();
        EvaluateNormals();
      } // End of 'sphere' function
    };
  }
}

#endif // !__topology_h_

// END OF 'topology.h' FILE