/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_matr.h
 * PURPOSE     : Ray tracing project.
 *               Mathematics library.
 *               Math matrix handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'mth'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

/* Math library namespace */
namespace mth
{
  /* Matrix data class handle */
  template<class type>
    class matr_data
    {
    public:
      // Matrix data
      type A[4][4] =
      {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
      };

      /* Matrix constructor. 
       * ARGUMENTS: None.
       */
      matr_data( void )
      {
      } // End of 'matr' function

    }; // End of 'matr_data' class

  /* Matrix class handle */
  template<class type>
    class matr : public matr_data<type>
    {
    private:
      // Inversed matrix
      mutable type InvA[4][4] =
      {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
      };
      mutable bool IsInverseEvaluated; // Inverse matrix evaluated flag

      /* Evaluate inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void EvaluateInverseMatrix( void ) const
      {
        if (IsInverseEvaluated)
          return;
        IsInverseEvaluated = TRUE;

        type det = !*this;
 
        /* build adjoint matrix */
        InvA[0][0] =
          MatrDeterm3x3(matr_data<type>::A[1][1], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                        matr_data<type>::A[2][1], matr_data<type>::A[2][2], matr_data<type>::A[2][3],
                        matr_data<type>::A[3][1], matr_data<type>::A[3][2], matr_data<type>::A[3][3]);
        InvA[1][0] =
          -MatrDeterm3x3(matr_data<type>::A[1][0], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                          matr_data<type>::A[2][0], matr_data<type>::A[2][2], matr_data<type>::A[2][3],
                          matr_data<type>::A[3][0], matr_data<type>::A[3][2], matr_data<type>::A[3][3]);
        InvA[2][0] =
          MatrDeterm3x3(matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][3],
                        matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][3],
                        matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][3]);
        InvA[3][0] =
          -MatrDeterm3x3(matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][2],
                          matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][2],
                          matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][2]);
 
        InvA[0][1] =
          -MatrDeterm3x3(matr_data<type>::A[0][1], matr_data<type>::A[0][2], matr_data<type>::A[0][3],
                          matr_data<type>::A[2][1], matr_data<type>::A[2][2], matr_data<type>::A[2][3],
                          matr_data<type>::A[3][1], matr_data<type>::A[3][2], matr_data<type>::A[3][3]);
        InvA[1][1] =
          MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][2], matr_data<type>::A[0][3],
                        matr_data<type>::A[2][0], matr_data<type>::A[2][2], matr_data<type>::A[2][3],
                        matr_data<type>::A[3][0], matr_data<type>::A[3][2], matr_data<type>::A[3][3]);
        InvA[2][1] =
          -MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][1], matr_data<type>::A[0][3],
                          matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][3],
                          matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][3]);
        InvA[3][1] =
          MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][1], matr_data<type>::A[0][2],
                        matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][2],
                        matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][2]);
 
        InvA[0][2] =
          MatrDeterm3x3(matr_data<type>::A[0][1], matr_data<type>::A[0][2], matr_data<type>::A[0][3],
                        matr_data<type>::A[1][1], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                        matr_data<type>::A[3][1], matr_data<type>::A[3][2], matr_data<type>::A[3][3]);
        InvA[1][2] =
          -MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][2], matr_data<type>::A[0][3],
                          matr_data<type>::A[1][0], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                          matr_data<type>::A[3][0], matr_data<type>::A[3][2], matr_data<type>::A[3][3]);
        InvA[2][2] =
          MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][1], matr_data<type>::A[0][3],
                        matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][3],
                        matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][3]);
        InvA[3][2] =
          -MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][1], matr_data<type>::A[0][2],
                          matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][2],
                          matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][2]);
 
        InvA[0][3] =
          -MatrDeterm3x3(matr_data<type>::A[0][1], matr_data<type>::A[0][2], matr_data<type>::A[0][3],
                          matr_data<type>::A[1][1], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                          matr_data<type>::A[2][1], matr_data<type>::A[2][2], matr_data<type>::A[2][3]);
        InvA[1][3] =
          MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][2], matr_data<type>::A[0][3],
                        matr_data<type>::A[1][0], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                        matr_data<type>::A[2][0], matr_data<type>::A[2][2], matr_data<type>::A[2][3]);
        InvA[2][3] =
          -MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][1], matr_data<type>::A[0][3],
                          matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][3],
                          matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][3]);
        InvA[3][3] =
          MatrDeterm3x3(matr_data<type>::A[0][0], matr_data<type>::A[0][1], matr_data<type>::A[0][2],
                        matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][2],
                        matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][2]);

        // Divide by determinant
        InvA[0][0] /= det;
        InvA[0][1] /= det;
        InvA[0][2] /= det;
        InvA[0][3] /= det;

        InvA[1][0] /= det;
        InvA[1][1] /= det;
        InvA[1][2] /= det;
        InvA[1][3] /= det;

        InvA[2][0] /= det;
        InvA[2][1] /= det;
        InvA[2][2] /= det;
        InvA[2][3] /= det;

        InvA[3][0] /= det;
        InvA[3][1] /= det;
        InvA[3][2] /= det;
        InvA[3][3] /= det;
      } // End of 'EvaluateInverseMatrix' function

    public:
      /* Matrix constructor. 
       * ARGUMENTS: None.
       */
      matr( void ) : IsInverseEvaluated(false)
      {
      } /* End of 'matr' function */

      /* Matrix constructor.
       * ARGUMENTS: 
       *   - Matrix values:
       *       type a00, type a01, type a02, type a03,
       *       type a10, type a11, type a12, type a13,
       *       type a20, type a21, type a22, type a23,
       *       type a30, type a31, type a32, type a33;
       */
      matr( type a00, type a01, type a02, type a03,
            type a10, type a11, type a12, type a13,
            type a20, type a21, type a22, type a23,
            type a30, type a31, type a32, type a33) : IsInverseEvaluated(false)
      {
        matr_data<type>::A[0][0] = a00, matr_data<type>::A[0][1] = a01, matr_data<type>::A[0][2] = a02, matr_data<type>::A[0][3] = a03;
        matr_data<type>::A[1][0] = a10, matr_data<type>::A[1][1] = a11, matr_data<type>::A[1][2] = a12, matr_data<type>::A[1][3] = a13;
        matr_data<type>::A[2][0] = a20, matr_data<type>::A[2][1] = a21, matr_data<type>::A[2][2] = a22, matr_data<type>::A[2][3] = a23;
        matr_data<type>::A[3][0] = a30, matr_data<type>::A[3][1] = a31, matr_data<type>::A[3][2] = a32, matr_data<type>::A[3][3] = a33;
      } /* End of matr constructor */

      /* Transorm normal function. 
       * ARGUMENTS:
       *   - vector to be transoformed:
       *       const vec3<type> &N;
       * RETURNS:
       *   (vec3<type>) result vector.
       */
      vec3<type> TransformNormal( const vec3<type> &N ) const
      {
        EvaluateInverseMatrix();
        return vec3<type>(N.X * InvA[0][0] + N.Y * InvA[0][1] + N.Z * InvA[0][2],
                          N.X * InvA[1][0] + N.Y * InvA[1][1] + N.Z * InvA[1][2],
                          N.X * InvA[2][0] + N.Y * InvA[2][1] + N.Z * InvA[2][2]);
      } /* End of 'TransformNormal' function */

      /* Get matr identity function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) identity matrix.
       */
      static matr<type> Identity( void )
      {
        return matr<type>(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
      } /* End of 'MatrIdentity' function */

      /* Translate matrix function.
       * ARGUMENTS:
       *   - vector to be translated:
       *       const vec3<type> &T;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr<type> Translate( const vec3<type> &T )
      {
        return matr<type>(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          T.X, T.Y, T.Z, 1);
      } /* End of 'Translate' function */

      /* Normalized device coordinates function.
       * ARGUMENTS:
       *   - Screen factors:
       *      Left and Right:
       *        type L, R;
       *      Bottom and Top:
       *        type B, T;
       *      Near and Far:
       *        type N, F;
       * RETURNS:
       *   (MATR) result matrix.
       */
      static matr<type> Frustum( type L, type R, type B, type T, type N, type F )
      {
          return matr<type>(2 * N / (R - L), 0, 0, 0,
                            0, 2 * N / (T - B), 0, 0,
                            (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
                            0, 0, -2 * N * F / (F - N), 0);
      } /* End of 'Frustum' function */

      /* Ortho projection matrix function.
       * ARGUMENTS:
       *   - Screen factors:
       *      Left and Right:
       *        type L, R;
       *      Bottom and Top:
       *        type B, T;
       *      Near and Far:
       *        type N, F;
       * RETURNS:
       *   (MATR) viewer matrix.
       */
      static matr<type> Ortho( type L, type R, type B, type T, type N, type F )
      {
        return matr<type>(2 / (R - L),           0,                           0,                  0,
                    0,                           2 / (T - B),                 0,                  0,
                    0,                           0,                           -2 / (F - N),       0,
                    -(R + L) / (R - L),          -(T + B) / (T - B),          -(N + F) / (F - N), 1);
      } /* End of 'Ortho' function */

      /* Matrix look at viwer setup function.
       * ARGUMENTS:
       *   - Positoin:
       *      VEC Loc;
       *   - Where we looking for:
       *      VEC At;
       *   - Direction to up:
       *      VEC Up1;
       * RETURNS:
       *   (MATR) result matrix.
       */
      static matr<type> View( vec3<type> Loc, vec3<type> At, vec3<type> Up1 )
      {
        vec3<type>
          D, /* Dir */
          U, /* Up */
          R; /* Right */

        D = ~(At - Loc);
        R = ~(D % Up1);
        U = R % D;

        return matr<type>(R.X, U.X, -D.X, 0,
                          R.Y, U.Y, -D.Y, 0,
                          R.Z, U.Z, -D.Z, 0,
                          -(Loc & R), -(Loc & U), Loc & D, 1);
      } /* End of 'View' function */

      /* Matrix lerp function. 
       * ARGMUENTS:
       *   - matrices to interpolate:
       *       const matr &Start, &End;
       *   - current state:
       *       type Current.
       * RETURNS:
       *   (matr) interpolated matrix.
       */
      static matr<type> Lerp( matr<type> &Start, matr<type> &End, type Current )
      {
        matr<type> M;

        for (INT i = 0; i < 4; i++)
          for (INT j = 0; j < 4; j++)
            M.A[i][j] = mth::Lerp(Start.A[i][j], End.A[i][j], Current);

        return M;
      } // End of 'Lerp' function 

      /* Transpose matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      matr<type> Transpose( void ) const
      {
        return matr<type>(matr_data<type>::A[0][0], matr_data<type>::A[1][0], matr_data<type>::A[2][0], matr_data<type>::A[3][0],
                    matr_data<type>::A[0][1], matr_data<type>::A[1][1], matr_data<type>::A[2][1], matr_data<type>::A[3][1],
                    matr_data<type>::A[0][2], matr_data<type>::A[1][2], matr_data<type>::A[2][2], matr_data<type>::A[3][2],
                    matr_data<type>::A[0][3], matr_data<type>::A[1][3], matr_data<type>::A[2][3], matr_data<type>::A[3][3]);
      } /* End of 'Transpose' function */

      /* Mulpiply matrixes function.
       * ARGUMENTS:
       *   - matrix to be multyplied:
       *       const matr &M;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr<type> operator*( const matr<type> &M ) const
      {
        matr<type> r;
        INT k;
 
        for (INT i = 0; i < 4; i++)
          for (INT j = 0; j < 4; j++)
            for (k = 0, r.matr_data<type>::A[i][j] = 0; k < 4; k++)
               r.matr_data<type>::A[i][j] += matr_data<type>::A[i][k] * M.matr_data<type>::A[k][j];
        return r;
      } /* End of 'operator*' function */

      /* Calculate matrix 3x3 determinant 
       * ARGUMENTS: 
       *   - matrix:
       *       type A11, type A12, type A13,
       *       type A21, type A22, type A23,
       *       type A31, type A32, type A33 
       * RETURNS:
       *   (type) matrix determinant.
       */
      static type MatrDeterm3x3( type A11, type A12, type A13,
                                 type A21, type A22, type A23,
                                 type A31, type A32, type A33 )
      {
        return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
               A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
      } /* End of 'MatrDeterm3x3' function */

      /* Calculate matrix determinant.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) matrix determinant.
       */
      type operator!( void ) const
      {
        return
          matr_data<type>::A[0][0] * MatrDeterm3x3(matr_data<type>::A[1][1], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                                                   matr_data<type>::A[2][1], matr_data<type>::A[2][2], matr_data<type>::A[2][3],
                                                   matr_data<type>::A[3][1], matr_data<type>::A[3][2], matr_data<type>::A[3][3]) +
          -matr_data<type>::A[0][1] * MatrDeterm3x3(matr_data<type>::A[1][0], matr_data<type>::A[1][2], matr_data<type>::A[1][3],
                                                    matr_data<type>::A[2][0], matr_data<type>::A[2][2], matr_data<type>::A[2][3],
                                                    matr_data<type>::A[3][0], matr_data<type>::A[3][2], matr_data<type>::A[3][3]) +
          matr_data<type>::A[0][2] * MatrDeterm3x3(matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][3],
                                                   matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][3],
                                                   matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][3]) +
          -matr_data<type>::A[0][3] * MatrDeterm3x3(matr_data<type>::A[1][0], matr_data<type>::A[1][1], matr_data<type>::A[1][2],
                                                    matr_data<type>::A[2][0], matr_data<type>::A[2][1], matr_data<type>::A[2][2],
                                                    matr_data<type>::A[3][0], matr_data<type>::A[3][1], matr_data<type>::A[3][2]);
      } /* End of 'operator!' function */

      /* Evaluate inverse matrix.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void Inverse( void ) const
      {
        EvaluateInverseMatrix();
      } /* End of 'MatrInverse' function */

      /* Return matr scale.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<type> &S;
       * RETURNS:
       *   (matr) scale matrix.
       */
      static matr<type> Scale( const vec3<type> &S )
      {
        return matr<type>(S.X, 0, 0, 0,
                          0, S.Y, 0, 0,
                          0, 0, S.Y, 0,
                          0, 0, 0, 1);
      } /* End of 'MatrScale' function */

      /* Rotate matrix function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       type AngleInDegree;
       *   - vector to matrix:
       *       vec3 T;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr<type> Rotate( vec3<type> V, type AngleInDegree )
      {
        type a = Deg2Rad(AngleInDegree), c = cos(a), s = sin(a);
        V.Normalize();

        return matr<type>(c + V.X * V.X * (1 - c), V.X * V.Y * (1 - c) + V.Z * s, V.X * V.Z * (1 - c) - V.Y * s, 0,
                          V.Y * V.X * (1 - c) - V.Z * s, c + V.Y * V.Y * (1 - c), V.Y * V.Z * (1 - c) + V.X * s, 0,
                          V.Z * V.X * (1 - c) + V.Y * s, V.Z * V.Y * (1 - c) - V.X * s, c + V.Z * V.Z * (1 - c), 0,
                          0, 0, 0, 1);
      } /* End of 'MatrRotate' function */

      /* Rotate matrix by X axis function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       type AngleInDegree;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr<type> RotateX( type AngleInDegree )
      {
        type a = Deg2Rad(AngleInDegree), c = cos(a), s = sin(a);

        return matr<type>(1, 0, 0, 0,
                       0, c, s, 0,
                       0, -s, c, 0,
                       0, 0, 0, 1);
      } /* End of 'MatrRotateX' function */

      /* Rotate matrix by Y axis function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       type AngleInDegree;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr<type> RotateY( type AngleInDegree )
      {
        type a = Deg2Rad(AngleInDegree), c = cos(a), s = sin(a);

        return matr<type>(c, 0, -s, 0,
                          0, 1, 0, 0,
                          s, 0, c, 0,
                          0, 0, 0, 1);
      } /* End of 'MatrRotateY' function */

      /* Rotate matrix by Z axis function.
       * ARGUMENTS:
       *   - angle in degrees:
       *       type AngleInDegree;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr<type> RotateZ( type AngleInDegree )
      {
        type a = Deg2Rad(AngleInDegree), c = cos(a), s = sin(a);

        return matr<type>(c, s, 0, 0,
                          -s, c, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
      } /* End of 'MatrRotateZ' function */

      /* Transform point position.
       * ARGUMENTS:
       *   - vectors to be dot multiplied:
       *       vec3 V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3<type> TransformPoint( const vec3<type> &V ) const
      {
        return vec3<type>(V.X * matr_data<type>::A[0][0] + V.Y * matr_data<type>::A[1][0] + V.Z * matr_data<type>::A[2][0] + matr_data<type>::A[3][0],
                          V.X * matr_data<type>::A[0][1] + V.Y * matr_data<type>::A[1][1] + V.Z * matr_data<type>::A[2][1] + matr_data<type>::A[3][1],
                          V.X * matr_data<type>::A[0][2] + V.Y * matr_data<type>::A[1][2] + V.Z * matr_data<type>::A[2][2] + matr_data<type>::A[3][2]);
      } /* End of 'TransformPoint' function */

      /* Transform point position.
       * ARGUMENTS:
       *   - vectors to be dot multiplied:
       *       vec3 V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3<type> TransformVector( const vec3<type> &V ) const
      {
        return vec3<type>(V.X * matr_data<type>::A[0][0] + V.Y * matr_data<type>::A[1][0] + V.Z * matr_data<type>::A[2][0],
                          V.X * matr_data<type>::A[0][1] + V.Y * matr_data<type>::A[1][1] + V.Z * matr_data<type>::A[2][1],
                          V.X * matr_data<type>::A[0][2] + V.Y * matr_data<type>::A[1][2] + V.Z * matr_data<type>::A[2][2]);
      } /* End of 'TransformPoint' function */

      /* Multiply matrix and vector.
       * ARGUMENTS:
       *   - multiplyong vector:
       *       vec3 V;
       * RETURNS:
       *   (matr) result matrix.
       */
      vec3<type> Transform4x4( const vec3<type> &V ) const
      {
        type w = V.X * matr_data<type>::A[0][3] + V.Y * matr_data<type>::A[1][3] + V.Z * matr_data<type>::A[2][3] + matr_data<type>::A[3][3];

        return vec3<type>((V.X * matr_data<type>::A[0][0] + V.Y * matr_data<type>::A[1][0] + V.Z * matr_data<type>::A[2][0] + matr_data<type>::A[3][0]) / w,
                          (V.X * matr_data<type>::A[0][1] + V.Y * matr_data<type>::A[1][1] + V.Z * matr_data<type>::A[2][1] + matr_data<type>::A[3][1]) / w,
                          (V.X * matr_data<type>::A[0][2] + V.Y * matr_data<type>::A[1][2] + V.Z * matr_data<type>::A[2][2] + matr_data<type>::A[3][2]) / w);
      } /* End of 'VecMulMatr' function */

            /* Return vector pointer.
       * ARGUMENTS: None.
       * RETURNS:
       *  (type *) vector pointer.
       */
      operator type *( void )
      {
        return matr_data<type>::A[0];
      } /* End of 'operator' function */

      /* Return vector pointer. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (type *) vector pointer.
       */
      operator const type *( void ) const
      {
        return matr_data<type>::A[0];
      } /* End of 'operator' function */
    }; /* End of 'matr' class */

} /* end of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */
