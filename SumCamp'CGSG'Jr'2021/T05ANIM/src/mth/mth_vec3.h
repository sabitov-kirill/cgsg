/* FILE NAME  : mth_vec3.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Math vector module.
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include <cstdlib>
#include <cmath>

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<class Type>
    class vec3
    {
    private:
      Type X, Y, Z; /* Vector components */

    template<class Type1>
      friend class matr;
    public:

      //
      // Constructors
      //
      /* Vector constructor. 
       * ARGUMENTS: None.
       */
      vec3( VOID ) : X(0), Y(0), Z(0)
      {
      } /* End of 'vec3' function */
      /* Vector constructor.
       * ARGUMENTS:
       *   - vector value:
       *       Type A;
       */
      explicit vec3( Type A ) : X(A), Y(A), Z(A)
      {
      } /* End of 'vec' function */
      
      /* Vector constructor.
       * ARGUMENTS:
       *   - 2 dim vector:
       *       const vec2<Type> &V;
       *   - number:
       *       Type A;
       */
      vec3( const vec2<Type> &V, Type C ) : X(V[0]), Y(V[1]), Z(C)
      {
      } /* End of 'vec3' function */
      /* Vector constructor.
       * ARGUMENTS:
       *   - number:
       *       Type A;
       *   - 2 dim vector:
       *       const vec2<Type> &V;
       */
      vec3( Type A, const vec2<Type> &V ) : X(A), Y(V[0]), Z(V[0])
      {
      } /* End of 'vec3' function */
      /* Vector constructor.
       * ARGUMENTS:
       *   - vector values:
       *       Type A, B, C;
       */
      vec3( Type A, Type B, Type C ) : X(A), Y(B), Z(C)
      {
      } /* End of 'vec3' function */

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
      } /* End of 'Zero' function */
      /* Return random vector in range 0 to 1.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Rnd0( VOID )
      {
        return vec3(static_cast<Type>(rand()) / RAND_MAX, static_cast<Type>(rand()) / RAND_MAX, static_cast<Type>(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */
      /* Return random vector in range -1 to 1. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Rnd1( VOID )
      {
        return vec3(static_cast<Type>(rand()) / RAND_MAX * 2 - 1, static_cast<Type>(rand()) / RAND_MAX * 2 - 1, static_cast<Type>(rand()) / RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      //
      // Vector methods
      //
      /* Vector normalizing. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) normalized vector.
       */
      vec3 & Normalizing( VOID ) const
      {
        return *this / !(*this);
      } /* End of 'Normalizing' function */
      /* Normalize vector and change value.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) Normalized vector.
       */
      vec3 & Normalize( VOID )
      {
        return *this = *this / !(*this);
      } /* End of 'Normalize' function */

      /* Get vector length. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length.
       */
      Type Length( VOID ) const
      {
        return sqrt(*this & *this);
      } // End of '' function
      /* Return square length.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length in square.
       */
      Type Length2( VOID ) const
      {
         return *this & *this;
      } /* End of 'Length2' function */

      /* Distance between two points.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) result distance.
       */
      Type Distance( const vec3 &V ) const
      {
        return !(*this - V);
      } /* End of 'Distance' function */

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

      /* Vector linear interpolation function. 
       * ARGUMENTS:
       *   - start and end vectors:
       *       const vec3 &Start, &End;
       *   - current state (0-1):
       *       Type Current;
       * RETURNS:
       *   (vec3) interpolated vector.
       */
      static vec3 Lerp( const vec3 &Start, const vec3 &End, FLT Current )
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
      } /* End of 'operator+' function */
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
      } /* End of 'operator+=' function */

      /* Unar minus operation. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( VOID ) const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator~' function */
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
      } /* End of 'operator-' function */
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
      } /* End of 'operator-=' function */

      /* Multiply vector with number. 
       * ARGUMENTS:
       *   - number to be multiplied:
       *       Type N;
       * RETURNS: None.
       *   (vec3) result vector.
       */
      vec3 operator*( Type N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */
      /* Multiply vector with number and change value. 
       * ARGUMENTS:
       *   - number to be multiplyed:
       *       Type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator*=( Type N )
      {
        return *this = vec3(X * N, Y * N, Z * N);
      } /* End of 'operator*=' function */
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
      } /* End of 'operator*' function */
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
      } /* End of 'operator*=' function */

      /* Divide vector with number.
       * ARGUMENTS:
       *   - number to be divided:
       *       Type N;
       * RESULT:
       *   (vec3) result vector.
       */
      vec3 operator/( Type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */
      /* Divide vector with number and change value.
       * ARGUMENTS:
       *   - number to be divided:
       *       Type N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 & operator/=( Type N )
      {
        return *this = vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/=' function */

      /* Vector(cross) multiplying.
       * ARGUMENTS:
       *   - vector to be multiplyied:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) result value.
       */
      vec3 operator%( const vec3 &V )
      {
        return vec3(Y * V.Z - V.Y * Z,
                    Z * V.X - V.Z * X,
                    X * V.Y - V.X * Y);
      } /* End of 'operator%' function */

      /* Scalar(dot) multiplying. 
       * ARGUMENTS:
       *   - vector to be multyplied:
       *       const vec3 &V;
       * RETURNS: 
       *   (Type) result value.
       */
      Type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Vector length. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length.
       */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'operator!' function */

      /* Vector normalizing function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) normalized vector.
       */
      vec3 operator~( VOID ) const
      {
        return *this / !(*this);
      } /* End of 'operator~' function */

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
       *   (Type) component of vector.
       */
      Type operator[]( INT I ) const
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
      } /* End of 'operator[]' function */
      /* Get vector component reference. 
       * ARGUMENTS:
       *   - index of component:
       *       INT I;
       * RETURNS:
       *  (Type &) component reference.
       */
      Type & operator[]( INT I )
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
      } /* End of 'operator[]' function */
      /* Return vector pointer.
       * ARGUMENTS: None.
       * RETURNS:
       *  (Type *) vector pointer.
       */
      operator Type *( VOID )
      {
        return &X;
      } /* End of 'operator' function */


    }; /* End of 'vec3' class */

} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */
