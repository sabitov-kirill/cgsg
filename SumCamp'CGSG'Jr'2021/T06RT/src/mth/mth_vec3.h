/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Ray tracing project.
 *               Mathematics library.
 *               Math 3 dimmensional vector handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'mth'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mthdef.h"

/* Math library namespace */
namespace mth
{
  /* 3D vector representation class */
  template<class type>
    class vec3
    {
    private:

    template<class Type1>
      friend class matr;

    public:
      // Vector components
      type X, Y, Z;

      //
      // Constructors
      //
      /* Vector constructor. 
       * ARGUMENTS: None.
       */
      vec3( VOID ) : X(0), Y(0), Z(0)
      {
      } // End of 'vec3' function
      /* Vector constructor.
       * ARGUMENTS:
       *   - vector value:
       *       type A;
       */
      explicit vec3( type A ) : X(A), Y(A), Z(A)
      {
      } // End of 'vec' function
      
      /* Vector constructor.
       * ARGUMENTS:
       *   - 2 dim vector:
       *       const vec2<type> &V;
       *   - number:
       *       type A;
       */
      vec3( const vec2<type> &V, type C ) : X(V[0]), Y(V[1]), Z(C)
      {
      } // End of 'vec3' function
      /* Vector constructor.
       * ARGUMENTS:
       *   - number:
       *       type A;
       *   - 2 dim vector:
       *       const vec2<type> &V;
       */
      vec3( type A, const vec2<type> &V ) : X(A), Y(V[0]), Z(V[0])
      {
      } // End of 'vec3' function
      /* Vector constructor.
       * ARGUMENTS:
       *   - vector values:
       *       type A, B, C;
       */
      vec3( type A, type B, type C ) : X(A), Y(B), Z(C)
      {
      } // End of 'vec3' function
      /* Vector constructor.
       * ARGUMENTS:
       *   - 3 dim vector:
       *       const vec3 &V;
       */
      vec3( const vec3 &V )
      {
        X = V.X;
        Y = V.Y;
        Z = V.Z;
      } // End of 'vec3' function

      //
      // Static vector creators
      //
      /* Return zero vector. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) zero vector.
       */
      static vec3 Zero( VOID )
      {
        return vec3(0);
      } // End of 'Zero' function
      /* Return random vector in range 0 to 1.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Rnd0( VOID )
      {
        return vec3(static_cast<type>(rand()) / RAND_MAX, static_cast<type>(rand()) / RAND_MAX, static_cast<type>(rand()) / RAND_MAX);
      } // End of 'Rnd0' function
      /* Return random vector in range -1 to 1. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Rnd1( VOID )
      {
        return vec3(static_cast<type>(rand()) / RAND_MAX * 2 - 1, static_cast<type>(rand()) / RAND_MAX * 2 - 1, static_cast<type>(rand()) / RAND_MAX * 2 - 1);
      } // End of 'Rnd1' function

      //
      // Vector methods
      //
      /* Vector normalizing. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) normalized vector.
       */
      vec3 Normalizing( VOID ) const
      {
        return *this / !(*this);
      } // End of 'Normalizing' function
      /* Normalize vector and change value.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) Normalized vector.
       */
      vec3 & Normalize( VOID )
      {
        return *this = *this / !(*this);
      } // End of 'Normalize' function

      /* Get vector length. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector length.
       */
      type Length( VOID ) const
      {
        return sqrt(*this & *this);
      } // End of 'Length' function
      /* Return square length.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector length in square.
       */
      type Length2( VOID ) const
      {
         return *this & *this;
      } // End of 'Length2' function

      /* Distance between two points.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   (type) result distance.
       */
      type Distance( const vec3 &V ) const
      {
        return !(*this - V);
      } // End of 'Distance' function

      /* Getting vector reflection function.
       * ARGUMENTS:
       *   - vector to get its reflection by surface:
       *       const vec3 &N;
       * RETURNS:
       *   (vec3) reflection vector.
       */
      vec3 Reflecting( const vec3 &V ) const
      {
        vec3 N = this->Normalizing();
        return V - N * 2 * (V & N);
      } // End of 'Reflecting' function

      /* Vector orienting function.
       * ARGUMENTS:
       *   - vector to orient:
       *       const vec3 &V;
       *   - incident vector:
       *       const vec3 &I;
       * RETURNS:
       *   (vec3) oriented vector.
       */
      vec3 Faceforward( const vec3 &V ) const
      {
        vec3 I = *this;
        if ((V & I) > 0)
          return V;
        return -V;
      } // End of 'Faceforward' function

      /* Faceforward for normal implementation function.
       * ARGUMENTS:
       *   - peturbed normal vector:
       *       const vec3 &N;
       *   - incidence vector:
       *       const vec3 &I;
       *   - geometric normal vector:
       *       const vec3 &N;
       * RETURNS:
       *   (vec3) faceforwarded nornal vector.
       */
      static vec3 Faceforward( const vec3 &N, const vec3 &I, const vec3 &Ng )
      {
        return (I & Ng) < 0 ? N : -N;
      } /* End of 'Faceforward' function */

      /* Evaluating minimum vector.
       * ARGUMENTS:
       *   - vectors:
       *       const vec3 &V1, const vec3 &V2;
       * RETURNS:
       *   (vec3) minimum vector.
       */
      static vec3 Min( vec3 &V1, vec3 &V2 )
      {
        return vec3(::mth::Min(V1.X, V2.X), ::mth::Min(V1.Y, V2.Y), ::mth::Min(V1.Z, V2.Z));
      } // End of 'Min' function

      /* Evaluating maximum vector.
       * ARGUMENTS:
       *   - vectors:
       *       const vec3 &V1, const vec3 &V2;
       * RETURNS:
       *   (vec3) maximum vector.
       */
      static vec3 Max( vec3 &V1, vec3 &V2 )
      {
        return vec3(::mth::Max(V1.X, V2.X), ::mth::Max(V1.Y, V2.Y), ::mth::Max(V1.Z, V2.Z));
      } // End of 'Max' function

      /* Vector clamp function. 
       * ARGUMENTS:
       *   - vector to clamp:
       *       const vec3 &V;
       *   - minimum and maximum values:
       *       type Min, Max;
       * RETURNS:
       *   (vec3) clamped vector.
       */
      static vec3 Clamp( const vec3 &V, type Min = 0, type Max = 1 )
      {
        return vec3
          (
            mth::Clamp(V.X, Min, Max),
            mth::Clamp(V.Y, Min, Max),
            mth::Clamp(V.Z, Min, Max)
          );
      } // End of 'Clamp' function

      /* Vector linear interpolation function. 
       * ARGUMENTS:
       *   - start and end vectors:
       *       const vec3 &Start, &End;
       *   - current state (0-1):
       *       type Current;
       * RETURNS:
       *   (vec3) interpolated vector.
       */
      static vec3 Lerp( const vec3 &Start, const vec3 &End, type Current )
      {
        return vec3
          (
            Lerp(Start.X, End.X, Current),
            Lerp(Start.Y, End.Y, Current),
            Lerp(Start.Z, End.Z, Current)
          );
      } // End of 'Lerp' function

      //
      // Vector operators
      //
      /* Add number to vector. 
       * ARGUMENTS:
       *   - number to be added:
       *       type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator+( type N ) const
      {
        return vec3(X + N, Y + N, Z + N);
      } // End of 'operator+' function
      /* Adding number and change value.
       * ARGUMENTS:
       *   - number to be added:
       *       type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator+=( type N )
      {
        return *this = vec3(X + N, Y + N, Z + N);
      } // End of 'operator+=' function
      /* Add two vectors. 
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator+( const vec3 &V ) const
      {
        return vec3(V.X + X, V.Y + Y, V.Z + Z);
      } // End of 'operator+' function
      /* Adding vector and change value.
       * ARGUMENTS:
       *   - vector to be added:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator+=( const vec3 &V )
      {
        return *this = vec3(V.X + X, V.Y + Y, V.Z + Z);
      } // End of 'operator+=' function

      /* Unar minus operation. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( VOID ) const
      {
        return vec3(-X, -Y, -Z);
      } // End of 'operator~' function
      /* Sub two vectors.
       * ARGUMENTS:
       *   - vector to be substructed:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } // End of 'operator-' function
      /* Sub vector and change value. 
       * ARGUMENTS:
       *   - vector to be substructed:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator-=( const vec3 &V )
      {
        return *this = vec3(V.X - X, V.Y - Y, V.Z - Z);
      } // End of 'operator-=' function

      /* Multiply vector with number. 
       * ARGUMENTS:
       *   - number to be multiplied:
       *       type N;
       * RETURNS: None.
       *   (vec3) result vector.
       */
      vec3 operator*( type N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      } // End of 'operator*' function
      /* Multiply vector with number and change value. 
       * ARGUMENTS:
       *   - number to be multiplyed:
       *       type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator*=( type N )
      {
        return *this = vec3(X * N, Y * N, Z * N);
      } // End of 'operator*=' function
      /* Multiply vector with vector. 
       * ARGUMENTS:
       *   - vector to be multiplied:
       *       const vec3 &V;
       * RETURNS: None.
       *   (vec3) result vector.
       */
      vec3 operator*( const vec3 &V ) const
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      } // End of 'operator*' function
      /* Multiply vector with vector and change value. 
       * ARGUMENTS:
       *   - vector to be multiplyed:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator*=( const vec3 &V )
      {
        return *this = vec3(X * V.X, Y * V.Y, Z * V.Z);
      } // End of 'operator*=' function

      /* Divide vector with number.
       * ARGUMENTS:
       *   - number to be divided:
       *       type N;
       * RESULT:
       *   (vec3) result vector.
       */
      vec3 operator/( type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } // End of 'operator/' function
      /* Divide vector with number and change value.
       * ARGUMENTS:
       *   - number to be divided:
       *       type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator/=( type N )
      {
        return *this = vec3(X / N, Y / N, Z / N);
      } // End of 'operator/=' function

      /* Vector(cross) multiplying.
       * ARGUMENTS:
       *   - vector to be multiplyied:
       *       const vec3 &V;
       * RETURNS:
       *   (type) result value.
       */
      vec3 operator%( const vec3 &V ) const
      {
        return vec3(Y * V.Z - V.Y * Z,
                    Z * V.X - V.Z * X,
                    X * V.Y - V.X * Y);
      } // End of 'operator%' function

      /* Vector(cross) multiplying.
       * ARGUMENTS:
       *   - vector to be multiplyied:
       *       const vec3 &V;
       * RETURNS:
       *   (type) result value.
       */
      vec3 Cross( const vec3 &V ) const
      {
        return vec3(Y * V.Z - V.Y * Z,
                    Z * V.X - V.Z * X,
                    X * V.Y - V.X * Y);
      } // End of 'Cross' function

      /* Scalar(dot) multiplying. 
       * ARGUMENTS:
       *   - vector to be multyplied:
       *       const vec3 &V;
       * RETURNS: 
       *   (type) result value.
       */
      type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } // End of 'operator&' function

      /* Vector length. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (type) vector length.
       */
      type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } // End of 'operator!' function

      /* Vector normalizing function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) normalized vector.
       */
      vec3 operator~( VOID ) const
      {
        return *this / !(*this);
      } // End of 'operator~' function

      /* Vector compare function
       * ARGUMENTS:
       *   - vector to compare with:
       *       const vec3 &V;
       * RETURNS:
       *   (BOOL) equal flag.
       */
      BOOL operator==( const vec3 &V )
      {
        if (X == V.X && Y == V.Y && Z == V.Z)
          return TRUE;
        return FALSE;
      } // End of 'operator==' function

      //
      // Getting data
      //
      /* Get vector component. 
       * ARGUMENTS:
       *   - index of component:
       *       INT I;
       * RETURNS:
       *   (type) component of vector.
       */
      type operator[]( INT I ) const
      {
        switch (I)
        {
        case 0:
          return X;
        case 1:
          return Y;
        case 2:
          return Z;
        default:
          return 0;
        }
      } // End of 'operator[]' function
      /* Get vector component reference. 
       * ARGUMENTS:
       *   - index of component:
       *       INT I;
       * RETURNS:
       *  (type &) component reference.
       */
      type & operator[]( INT I )
      {
        switch (I)
        {
        case 0:
          return X;
        case 1:
          return Y;
        case 2:
          return Z;
        default:
          return X;
        }
      } // End of 'operator[]' function
      /* Return vector pointer.
       * ARGUMENTS: None.
       * RETURNS:
       *  (type *) vector pointer.
       */
      operator type *( VOID )
      {
        return &X;
      } // End of 'operator' function

    }; // End of 'vec3' class

} // End of 'mth' namespace

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */
