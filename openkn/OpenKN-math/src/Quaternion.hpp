/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Quaternion.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the openKraken-math.
 *
 * The openKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The openKraken-math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__QUATERNION_HPP__
#define __OPENKN_MATH__QUATERNION_HPP__

/* Removing some warnings on Microsoft Visual C++ */
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4290)
#endif

/*
 * Internal Includes
 */
#include "MathException.hpp"
#include "Matrix4x4.hpp"
#include "Matrix3x3.hpp"
#include "MathTools.hpp"

/*
 * External Includes
 */

/*
 * Namespace
 */
namespace kn {
	/**
	 * \brief class to manipulate a quatrenions
	 * cf. Essential for mathematics and interactive applications
	 */
	template < typename T >
	class Quaternion {

		private:

			/**
			 * \brief Scalar part of the quaternion
			 */
			T w ;

			/**
			 * \brief Vector part of the quaternion
			 */
			Vector<T,StaticStorePolicy<T,3> > v ;

		public:

			/********************************
			 * Constructors
			 ********************************/

			/**
			 * \brief Default constructor
			 */
			Quaternion<T> ( void ): w ( 1.0 ) , v ( 0.0 ) {}

			/**
			 * \brief Copy constructor
			 * Create a quaternion based on the input quaternion
			 * \param q the quaternion to copy
			 */
			Quaternion<T> ( const Quaternion<T>& q ) : w ( q.w ) , v ( q.v ) {}

			/**
			 * \brief Copy constructor
			 * Create a quaternion based on the input pointer on a quaternion
			 * \param q the pointer on the quaternion to copy
			 * \throw MathException q is null
			 */
			Quaternion<T> ( const Quaternion<T>* q ) throw (MathException);

			/**
			 * \brief Create a quaternion using 4 double data
			 * Create a quaternion based on double data. The first is the scalar part while others are the vector part.
			 * \param w scalar part
			 * \param x first component of the vector part
			 * \param y second component of the vector part
			 * \param z third component of the vector part
			 */
			Quaternion<T> ( T w , T x , T y , T z ) : w ( w ), v ( x,y,z ) {};

			/**
			 * \brief Create a quaternion using quaternion representation
			 * \param w scalar part
			 * \param v vetor part
			 */
			Quaternion<T> ( T w , const Vector<T,StaticStorePolicy<T,3> >& v ) : w ( w ), v ( v ) {}

			/**
			 * \brief Create a quaternion using quaternion representation
			 * Scalar part is null.
			 * \param v vetor part
			 */
			Quaternion<T> ( const Vector<T,StaticStorePolicy<T,3> >& v ) : w ( 0 ), v ( v ) {};

			/**
			 * \brief Create a quaternion computing rotation between two vectors
			 * \param v1 first vector
			 * \param v2 second vector
			 */
			Quaternion<T> ( const Vector<T,StaticStorePolicy<T,3> >& v1 , const Vector<T,StaticStorePolicy<T,3> >& v2 );

			/**
			 * \brief Create a quaternion using an axis and an angle
			 * This is the representation of rotation quaternion.
			 * \param axis axis of rotation
			 * \param angle angle of rotation in radians
			 */
			Quaternion<T> ( const Vector<T,StaticStorePolicy<T,3> >& axis, const T& angle );

			/**
			 * \brief Create a quaternion using a 3x3 matrix
			 *
			 * \param m the input matrix
			 */
			Quaternion<T> ( const Matrix3x3<T>& m );

			/**
			 * \brief Create a quaternion using a 4x4 matrix
			 *
			 * \param m the input matrix
			 *
			 * \author Frankoi
			 */
			Quaternion<T> ( const Matrix4x4<T>& m );

			/**
			 * \brief Create a quaternion using Euler angles
			 *
			 * \param roll rotation around x axis in degrees
			 * \param pitch rotation around y axis in degrees
			 * \param yaw rotation around z axis in degrees
			 *
			 * \author Frankoi
			 */
			Quaternion<T>(const double& roll, const double& pitch, const double& yaw);

			/**
			 * \brief Destructor
			 *
			 * \author Frankoi
			 */
			~Quaternion<T> ( void ) {}

			/**
			 * \brief Get the scalar part of the quaternion
			 * \return the scalar part
			 *
			 * \author Frankoi
			 */
			const T& getScalar ( void ) const { return this->w; }

			/**
			 * \brief Sets the scalar part of the quaternion
			 *
			 * \author Frankoi
			 */
			void setScalar ( const T& w ) { this->w = w; }

			/**
			 * \brief Get the vector part of the quaternion
			 * \return the vector part
			 */
			const Vector<T,StaticStorePolicy<T,3> >& getVector ( void ) const { return this->v; }

			/**
			 * \brief Sets the vector part of the quaternion
			 *
			 * \author Frankoi
			 */
			void setVector ( const Vector<T,StaticStorePolicy<T,3> >& v ) { this->v = v; }

			/**
			 * \brief Get the angle associated with the quaternion
			 * Get the axis of the rotation associated with the quaternion
			 * \return the angle of the rotation
			 */
			T getAngle ( void ) const ;

			/**
			 * \brief Get the axis of the rotation associated with the quaternion
			 * \return the axis of the rotation
			 */
			Vector<T,StaticStorePolicy<T,3> > getAxis ( void ) const ;

			/**
			 * \brief Compute the 4x4 rotation matrix similar to the quaternion
			 * \return the 4x4 rotation matrix
			 */
			Matrix4x4<T> getMatrix4 ( void ) const ;

			/**
			 * \brief Compute the 3x3 rotation matrix similar to the quaternion
			 * \return the 3x3 rotation matrix
			 */
			Matrix3x3<T> getMatrix3 ( void ) const ;

			/**
			 * \brief Compute the quaternion's inverse
			 * \return the quaternion's inverse
			 *
			 * \author Frankoi
			 */
			Quaternion<T> getInverse ( void ) const ;

			/**
			 * \brief Inverse the quaternion in place
			 *
			 * q^(-1) = q* / Norm(q)
			 *
			 * \author Frankoi
			 */
			void inverse ( void );

			/**
			 * \brief Computes the quaternion's norm
			 *
			 * \return the quaternion's norm
			 *
			 * \author Frankoi
			 */
			T getNorm ( void ) const ;

			/**
			 * \brief Sets quaternion to identity
			 *
			 * w = 1.0 and v = (0.0, 0.0, 0.0)
			 *
			 * \author Frankoi
			 */
			void setIdentity ( void );

			/**
			 * \brief Conjugates the quaternion in place
			 *
			 * q = [w, -v] => q* = [w, -v]
			 *
			 * \author Frankoi
			 */
			void conjugate ( void );

			/**
			 * \brief Returns the quaternion's conjugate
			 * \return the quaternion's conjugate
			 *
			 * \author Frankoi
			 */
			Quaternion<T> getConjugate ( void ) const ;

			/**
			 * \brief Normalizes the quaternion in place
			 *
			 * sets w to 1.0 and normalize v according to w
			 *
			 * \author Frankoi
			 */
			void normalize ( void );

			/**
			 * \brief Returns a copy of the normalized quaternion
			 *
			 * sets w to 1.0 and normalize v according to w
			 *
			 * \return a copy of the normalized quaternion
			 *
			 * \author Frankoi
			 */
			Quaternion<T> getNormalized ( void ) const;

			/**
			 * \brief Returns a vector with pitch roll and yaw information
			 *
			 * \return Euler angles in degrees
			 *
			 * \author Frankoi
			 */
			Vector<T,StaticStorePolicy<T,3> > getEuler(void) const;

			/**
			 * \brief Rotates a vector according to the quaternion
			 *
			 * \return the rotated vector
			 *
			 * \author Frankoi
			 */
			Vector<T,StaticStorePolicy<T,3> > rotate ( const Vector<T,StaticStorePolicy<T,3> >& v ) const;

			/**
			 * \brief Computes the dot product between two quaternions
			 *
			 * \return the dot product
			 *
			 * \author Frankoi
			 */
			T dot ( const Quaternion& q ) const;


			/**
			 * \brief Computes the scalar part of the quaternion, use only with unit quaternions
			 */
			inline void computeScalar ( void ) ;

			/********************************
			 * Operators redefinition
			 ********************************/

			/**
			 * \brief Returns the ith coordinate of the quaternion
			 *
			 * (0 for w, 1 for x, 2 for y and 3 for z)
			 *
			 * \param i the wanted ith coordinate
			 * \return the ith coordinate of the quaternion
			 * \throw MathException i is out of bounds
			 */
			const T& operator [](unsigned int i) const throw (MathException);

			/**
			 * \brief Returns the ith coordinate of the quaternion
			 *
			 * (0 for w, 1 for x, 2 for y and 3 for z)
			 *
			 *\param i the wanted ith coordinate
			 * \return the ith coordinate of the quaternion
			 *\throw MathException i is out of bounds
			 */
			T& operator [](unsigned int i) throw (MathException);

			/**
			 * \brief Tests equality between two quaternions
			 *
			 * \param q a quaternion
			 * \return true if quaternions are equal
			 */
			const bool operator== ( const Quaternion<T>& q ) const ;

			/**
			 * \brief Affects the quaternion using another quaternion
			 *
			 * \param q a quaternion
			 */
			Quaternion<T>& operator= ( const Quaternion<T>& q ) ;

			/**
			 * \brief Negates the quaternion
			 *
			 * \return the negated quaternion
			 */
			Quaternion<T>  operator- (void) const ;

			/**
			 * \brief Conjugates the quaternion
			 *
			 * \return the conjugate
			 */
			Quaternion<T>  operator~ (void);

			/**
			 * \brief Adds the quaternion with another one
			 *
			 * \param q a quaternion
			 * \return the result of the addition
			 */
			Quaternion<T>  operator+  ( const Quaternion<T>& q ) const ;

			/**
			 * \brief subtracts the quaternion with another one
			 *
			 * \param q a quaternion
			 * \return the result of the subtraction
			 */
			Quaternion<T>  operator-  ( const Quaternion<T>& q ) const ;

			/**
			 * \brief Multiplies the quaternion with another one
			 *
			 * \param q a quaternion
			 * \return the result of the Multiplication
			 */
			Quaternion<T>  operator*  ( const Quaternion<T>& q ) const ;

			/**
			 * \brief divides the quaternion with another one
			 *
			 * \param q a quaternion
			 * \return the result of the division
			 */
			Quaternion<T>  operator/  ( const Quaternion<T>& q ) const ;

			/**
			 * \brief Adds a quaternion with the current one
			 *
			 * \param q a quaternion
			 * \return the result of the addition
			 */
			Quaternion<T>& operator+= ( const Quaternion<T>& q ) ;

			/**
			 * \brief subtracts a quaternion with the current one
			 *
			 * \param q a quaternion
			 * \return the result of the subtraction
			 */
			Quaternion<T>& operator-= ( const Quaternion<T>& q ) ;

			/**
			 * \brief Multiplies a quaternion with the current one
			 *
			 * \param q a quaternion
			 * \return the result of the Multiplication
			 */
			Quaternion<T>& operator*= ( const Quaternion<T>& q ) ;

			/**
			 * \brief divides a quaternion with the current one
			 *
			 * \param q a quaternion
			 * \return the result of the division
			 */
			Quaternion<T>& operator/= ( const Quaternion<T>& q ) ;

			/**
			 * \brief Multiplies the quaternion with a constant
			 *
			 * \param d a constant
			 * \return the result of the Multiplication
			 */
			Quaternion<T>  operator*  ( T d ) const ;

			/**
			 * \brief Divides the quaternion with a constant
			 *
			 * \param d a constant
			 * \return the result of the division
			 */
			Quaternion<T>  operator/  ( T d ) const throw (MathException);

			/**
			 * \brief Multiplies the quaternion with a constant
			 *
			 * \param d a constant
			 * \return the result of the Multiplication
			 */
			Quaternion<T>& operator*= ( T d ) ;

			/**
			 * \brief Divides the quaternion with a constant
			 *
			 * \param d a constant
			 * \return the result of the division
			 */
			Quaternion<T>& operator/= ( T d ) throw (MathException);

			/**
			 * \brief Cross product
			 *
			 * \param v a vector
			 * \return result of the cross product
			 */
			Vector<T,StaticStorePolicy<T,3> > operator^ ( const Vector<T,StaticStorePolicy<T,3> >& v ) const ;

			/**
			 * \brief Multiplies a vector with the quaternion
			 *
			 * \param v a vector
			 * \return the new quaternion
			 */
			Quaternion<T> operator* ( const Vector<T,StaticStorePolicy<T,3> >& v ) const ;

	};

	/**
	 * \brief Multiplies a scalar with a quaternion
	 *
	 * \param q a quaternion
	 * \param d a scalar
	 * \return the new quaternion
	 */
	template<typename T>
	Quaternion<T> operator* ( T d , const Quaternion<T>& q );

	/**
	 * \brief Divides a scalar with a quaternion
	 *
	 * \param q a quaternion
	 * \param d a scalar
	 * \return the new quaternion
	 */
	template<typename T>
	Quaternion<T> operator/ ( T d , const Quaternion<T>& q );

	/**
	 * \brief Linear interpolation between two quaternions
	 *
	 * \param p starting quaternion
	 * \param q finishing quaternion
	 * \param t time interval
	 * \return interpolated quaternion
	 */
	template<typename T>
	Quaternion<T>  lerp ( const Quaternion<T>& p , const Quaternion<T>& q , T t ) ;

	/**
	 * \brief Spherical linear interpolation between two quaternions
	 *
	 * \param p starting quaternion
	 * \param q finishing quaternion
	 * \param t time interval
	 * \return sphericaly interpolated quaternion
	 */
	template<typename T>
	Quaternion<T> slerp ( const Quaternion<T>& p , const Quaternion<T>& q , T t ) ;

	template<typename T>
	std::ostream& operator<< ( std::ostream& o, const Quaternion<T>& q );

	template<typename T>
	std::istream& operator>> ( std::istream& o, const Quaternion<T>& q );

	/********************************
	 * Type definitions
	 ********************************/

	typedef Quaternion<float>  Quaternionf;
	typedef Quaternion<double> Quaterniond;

	template<typename T>
	inline Quaternion<T>::Quaternion ( const Quaternion<T>* q ) throw (MathException) {
		if(!q) throw MathException("Quaternion is null");
		this->w = q->w ;
		this->v = q->v ;
	}

	template<typename T>
	inline Quaternion<T>::Quaternion ( const Vector<T,StaticStorePolicy<T,3> >& v1, const Vector<T,StaticStorePolicy<T,3> >& v2 ) {
		Vector<T,StaticStorePolicy<T,3> > axis = v1^v2;
		axis.normalize();
		T angle = acos(v1*v2);
		this->w    =         cos(angle/2.0) ;
		this->v[0] = axis[0]*sin(angle/2.0) ;
		this->v[1] = axis[1]*sin(angle/2.0) ;
		this->v[2] = axis[2]*sin(angle/2.0) ;
	}

	template<typename T>
	inline Quaternion<T>::Quaternion ( const Vector<T,StaticStorePolicy<T,3> >& axis, const T& angle ) {
		this->w    =         cos(angle/2.0) ;
		this->v[0] = axis[0]*sin(angle/2.0) ;
		this->v[1] = axis[1]*sin(angle/2.0) ;
		this->v[2] = axis[2]*sin(angle/2.0) ;
	}

	template<typename T>
	inline Quaternion<T>::Quaternion( const Matrix4x4<T>& m ) {

		T  tr, s, q[4];
		int i, j, k;
		int nxt[3] = {1, 2, 0};
		tr = m[0][0] + m[1][1] + m[2][2];

		// check the diagonal
		if (tr > 0.0) {
			s = sqrt(tr + 1.0);
			w = s / 2.0;
			s = 0.5 / s;
			v[0] = (m[2][1] - m[1][2]) * s;
			v[1] = (m[0][2] - m[2][0]) * s;
			v[2] = (m[1][0] - m[0][1]) * s;
		}

		else {
			// diagonal is negative
			i = 0;
			if (m[1][1] > m[0][0]) i = 1;
			if (m[2][2] > m[i][i]) i = 2;
			j = nxt[i];
			k = nxt[j];

			s = sqrt((m[i][i] - (m[j][j] + m[k][k])) + 1.0);

			q[i] = s * 0.5;
			if (s != 0.0) s = 0.5 / s;

			q[3] = (m[k][j] - m[j][k]) * s;
			q[j] = (m[j][i] + m[i][j]) * s;
			q[k] = (m[k][i] + m[i][k]) * s;

			v[0] = q[0];
			v[1] = q[1];
			v[2] = q[2];
			w = q[3];
		}
	}

	template<typename T>
	Quaternion<T>::Quaternion( const Matrix3x3<T>& m ){

		T  tr, s, q[4];
		int i, j, k;
		int nxt[3] = {1, 2, 0};
		tr = m[0][0] + m[1][1] + m[2][2];

		// check the diagonal
		if (tr > 0.0) {
			s = sqrt (tr + 1.0);
			w = s / 2.0;
			s = 0.5 / s;
			v[0] = (m[2][1] - m[1][2]) * s;
			v[1] = (m[0][2] - m[2][0]) * s;
			v[2] = (m[1][0] - m[0][1]) * s;
		}

		else {
			// diagonal is negative
			i = 0;
			if (m[1][1] > m[0][0]) i = 1;
			if (m[2][2] > m[i][i]) i = 2;
			j = nxt[i];
			k = nxt[j];

			s = sqrt ((m[i][i] - (m[j][j] + m[k][k])) + 1.0);

			q[i] = s * 0.5;
			if (s != 0.0) s = 0.5 / s;

			q[3] = (m[k][j] - m[j][k]) * s;
			q[j] = (m[j][i] + m[i][j]) * s;
			q[k] = (m[k][i] + m[i][k]) * s;

			v[0] = q[0];
			v[1] = q[1];
			v[2] = q[2];
			w = q[3];
		}
	}

	template<typename T>
	Quaternion<T>::Quaternion(const double& roll, const double& pitch, const double& yaw) {
		double cr, cp, cy, sr, sp, sy, cpcy, spsy;

		cr = cos(degToRad(roll)/2.0);
		cp = cos(degToRad(pitch)/2.0);
		cy = cos(degToRad(yaw)/2.0);

		sr = sin(degToRad(roll)/2.0);
		sp = sin(degToRad(pitch)/2.0);
		sy = sin(degToRad(yaw)/2.0);

		cpcy = cp * cy;
		spsy = sp * sy;

		w    = T(cr * cpcy + sr * spsy);
		v[0] = T(sr * cpcy - cr * spsy);
		v[1] = T(cr * sp * cy + sr * cp * sy);
		v[2] = T(cr * cp * sy - sr * sp * cy);
	}

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator= ( const Quaternion<T>& q ) {
		this->w = q.w;
		this->v = q.v;

		return *this;
	}

	template<typename T>
	inline const T& Quaternion<T>::operator[] ( unsigned int i ) const throw (MathException) {
		if ( i>3  ) throw MathException("There are just 4 components");
		if ( i==0 ) return this->w;
		else        return this->v[i-1];
	}

	template<typename T>
	inline T& Quaternion<T>::operator[] ( unsigned int i ) throw (MathException) {
		if ( i>3  ) throw MathException("There are just 4 components");
		if ( i==0 ) return this->w;
		else        return this->v[i-1];
	}

	template<typename T>
	inline T Quaternion<T>::getAngle ( void ) const {
		return 2.0*acos(this->w);
	}

	template<typename T>
	inline Vector<T,StaticStorePolicy<T,3> > Quaternion<T>::getAxis ( void ) const {
		T norm = sqrt( 1.0 - this->w*this->w );

		return this->v/norm;
	}

	template<typename T>
	inline Matrix4x4<T> Quaternion<T>::getMatrix4 ( void ) const {
		Matrix4x4<T> m(T(0.0));

		m[0][0] = 1.0 - 2.0*this->v[1]*this->v[1] - 2.0*this->v[2]*this->v[2];
		m[0][1] =       2.0*this->v[0]*this->v[1] - 2.0*this->w   *this->v[2];
		m[0][2] =       2.0*this->v[0]*this->v[2] + 2.0*this->w   *this->v[1];
		m[1][0] =       2.0*this->v[1]*this->v[0] + 2.0*this->w   *this->v[2];
		m[1][1] = 1.0 - 2.0*this->v[0]*this->v[0] - 2.0*this->v[2]*this->v[2];
		m[1][2] =       2.0*this->v[1]*this->v[2] - 2.0*this->w   *this->v[0];
		m[2][0] =       2.0*this->v[0]*this->v[2] - 2.0*this->w   *this->v[1];
		m[2][1] =       2.0*this->v[1]*this->v[2] + 2.0*this->w   *this->v[0];
		m[2][2] = 1.0 - 2.0*this->v[0]*this->v[0] - 2.0*this->v[1]*this->v[1];
		m[3][3] = 1.0;

		return m;
	}

	template<typename T>
	inline Matrix3x3<T> Quaternion<T>::getMatrix3 ( void ) const {
		Matrix3x3<T> m;

		m[0][0] = 1.0 - 2.0*this->v[1]*this->v[1] - 2.0*this->v[2]*this->v[2];
		m[0][1] =       2.0*this->v[0]*this->v[1] - 2.0*this->w   *this->v[2];
		m[0][2] =       2.0*this->v[0]*this->v[2] + 2.0*this->w   *this->v[1];
		m[1][0] =       2.0*this->v[1]*this->v[0] + 2.0*this->w   *this->v[2];
		m[1][1] = 1.0 - 2.0*this->v[0]*this->v[0] - 2.0*this->v[2]*this->v[2];
		m[1][2] =       2.0*this->v[1]*this->v[2] - 2.0*this->w   *this->v[0];
		m[2][0] =       2.0*this->v[0]*this->v[2] - 2.0*this->w   *this->v[1];
		m[2][1] =       2.0*this->v[1]*this->v[2] + 2.0*this->w   *this->v[0];
		m[2][2] = 1.0 - 2.0*this->v[0]*this->v[0] - 2.0*this->v[1]*this->v[1];

		return m;
	}

	template<typename T>
	inline void Quaternion<T>::inverse ( void ) {
		Quaternion<T> q = *this;
		this->conjugate();
		this->normalize();
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::getInverse ( void ) const {
		Quaternion<T> q(*this);
		q.inverse();
		return q;
	}

	template<typename T>
	inline T Quaternion<T>::getNorm ( void ) const {
		return sqrt (
			this->w   *this->w    +
			this->v[0]*this->v[0] +
			this->v[1]*this->v[1] +
			this->v[2]*this->v[2]
		);
	}

	template<typename T>
	inline void Quaternion<T>::setIdentity ( void ) {
		this->w = 1.0 ;
		this->v[0] = this->v[1] = this->v[2] = 0.0 ;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::getConjugate ( void ) const {
		Quaternion<T> q(*this);
		q.conjugate();
		return q;
	}

	template<typename T>
	inline void Quaternion<T>::conjugate ( void ) {
		this->v = -this->v ;
	}

	template<typename T>
	inline void Quaternion<T>::normalize ( void ) {
		T norm = this->getNorm();
		if(norm == 0.0) throw MathException("Quaternion's norm is null");
		*this /= this->getNorm();
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::getNormalized ( void ) const {
		Quaternion<T> q(*this);
		q.normalize();

		return q;
	}


	template<typename T>
	Vector<T,StaticStorePolicy<T,3> > Quaternion<T>::getEuler ( void ) const {
		T sqw, sqx, sqy, sqz;

		T rotxrad, rotyrad, rotzrad;

		sqw = w * w;
		sqx = v[0] * v[0];
		sqy = v[1] * v[1];
		sqz = v[2] * v[2];

		rotxrad = (T)atan2(2.0 * ( v[1] * v[2] + v[0] * w ) , 1.0 - 2.0*(sqx+sqy)/*( -sqx - sqy + sqz + sqw )*/);
		rotyrad = (T)asin (2.0 * (-v[0] * v[2] + v[1] * w ));
		rotzrad = (T)atan2(2.0 * ( v[0] * v[1] + v[2] * w ) , 1.0 - 2.0*(sqy+sqz)/*(  sqx - sqy - sqz + sqw )*/);

		return Vector<T,StaticStorePolicy<T,3> >(radToDeg(rotxrad),radToDeg(rotyrad),radToDeg(rotzrad));
	}

	template <typename T>
	inline Vector<T,StaticStorePolicy<T,3> > Quaternion<T>::rotate ( const Vector<T,StaticStorePolicy<T,3> >& v ) const {
		return Vector<T,StaticStorePolicy<T,3> >(((*this) * v * this->getInverse()).getVector());
	}

	template<typename T>
	inline T Quaternion<T>::dot ( const Quaternion& q ) const {
		return this->w*q.w + this->v*q.v;
	}

	template<typename T>
	inline void Quaternion<T>::computeScalar ( void ) {
		T t = 1.0 - v*v;

		this->w = t < 0.0 ? 0.0 : -std::sqrt ( t ) ;
	}

	template<typename T>
	inline const bool Quaternion<T>::operator== ( const Quaternion<T>& q ) const {
		return (q.w == this->w && q.v == this->v);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator- () const {
		return Quaternion<T>(-w, -v);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator~ () {
		return this->getConjugate();
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator+ ( const Quaternion<T>& q ) const {
		return Quaternion<T>( this->w + q.w, this->v + q.v ) ;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator- ( const Quaternion<T>& q ) const {
		return Quaternion<T>( this->w - q.w, this->v - q.v ) ;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator* ( const Quaternion<T>& q ) const {
		return Quaternion<T> (
			this->w   *q[0] - this->v[0]*q[1] - this->v[1]*q[2] - this->v[2]*q[3],
			this->v[0]*q[0] + this->w   *q[1] + this->v[1]*q[3] - this->v[2]*q[2],
			this->v[1]*q[0] + this->w   *q[2] + this->v[2]*q[1] - this->v[0]*q[3],
			this->v[2]*q[0] + this->w   *q[3] + this->v[0]*q[2] - this->v[1]*q[1]
		);
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator/ ( const Quaternion<T>& q ) const {
		return (*this)*q.getInverse();
	}

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator+= ( const Quaternion<T>& q ) {
		this->w += q.w;
		this->v += q.v;

		return *this;
	}

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator-= ( const Quaternion<T>& q ) {
		this->w -= q.w;
		this->v -= q.v;

		return *this;
	}

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator*= ( const Quaternion<T>& q ) {
		this->w*=q.w;
		this->w-=(this->v*q.v);
		this->v = this->w*q.v + q.w*this->v + q.v^this->v;

		return *this;
	}

	template <typename T>
	inline Quaternion<T>& Quaternion<T>::operator/= (const Quaternion<T>& q) {
		return *this = (*this)*q.getInverse();
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator* ( T d ) const {
		Quaternion<T> result(*this);
		result *= d;

		return result;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator/ ( T d ) const throw (MathException) {
		if ( d==0.0 ) throw MathException("Value is null","operator/");
		Quaternion<T> result(*this);
		result /= d;

		return result;
	}

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator*= ( T d ) {
		this->w *= d;
		this->v *= d;

		return *this;
	}

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator/= ( T d ) throw (MathException) {
		if ( d==0.0 ) throw MathException("Value is null","operator/=");

		this->w /= d;
		this->v /= d;

		return *this;
	}

	template<typename T>
	inline Quaternion<T> Quaternion<T>::operator* ( const Vector<T,StaticStorePolicy<T,3> >& v ) const {
		return Quaternion<T> (
		 - (this->v[0]*v[0]) - (this->v[1]*v[1]) - (this->v[2]*v[2]),
		   (this->w   *v[0]) + (this->v[1]*v[2]) - (this->v[2]*v[1]),
		   (this->w   *v[1]) + (this->v[2]*v[0]) - (this->v[0]*v[2]),
		   (this->w   *v[2]) + (this->v[0]*v[1]) - (this->v[1]*v[0])
		);
	}

	template<typename T>
	inline Vector<T,StaticStorePolicy<T,3> > Quaternion<T>::operator^ ( const Vector<T,StaticStorePolicy<T,3> >& v ) const {
		return (this->v).getNormalized()^v.getNormalized();
	}

	template<typename T>
	inline Quaternion<T> operator* ( T d , const Quaternion<T>& q ) {
		return q*d ;
	}

	template<typename T>
	inline Quaternion<T> operator/ ( T d , const Quaternion<T>& q ) {
		return q/d ;
	}

	template<typename T>
	inline Quaternion<T>  lerp ( const Quaternion<T>& p , const Quaternion<T>& q , T t ) {
		Quaternion<T> res(p*(1-t) + q*t);

		res.normalize();

		return res;
	}

	template<typename T>
	inline Quaternion<T> slerp ( const Quaternion<T>& p , const Quaternion<T>& q , T t ) {
		if (t <= 0.0) return p;
		if (t >= 1.0) return q;

		T cosOmega = p.dot(q);

		T w = q[0];
		T x = q[1];
		T y = q[2];
		T z = q[3];

		if (cosOmega < 0.0) {
			w = -w;
			x = -x;
			y = -y;
			z = -z;
			cosOmega = -cosOmega;
		}

		T a, b;

		if (cosOmega > 0.9999) {
			a = 1.0 - t;
			b = t;
		}

		else {
		  T omega = std::acos (cosOmega);
		  T inverseSinOmega = 1.0 / (std::sqrt (1.0 - (cosOmega*cosOmega)));

		  a = std::sin ((1.0 - t) * omega) * inverseSinOmega;
		  b = std::sin (t * omega) * inverseSinOmega;
		}

		return Quaternion<T> (
			(a*p[0]) + (b*w),
			(a*p[1]) + (b*x),
			(a*p[2]) + (b*y),
			(a*p[3]) + (b*z)
		);
	}

	template<typename T>
	inline std::ostream& operator<< ( std::ostream& out, const Quaternion<T>& q ) {
		out << "[" << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "]" << std::endl;

		return out;
	}

	template<typename T>
	inline std::istream& operator>> (std::istream& in, Quaternion<T>& q) {
		char c;

		in >> c >> q[0] >> c >> q[1] >> c >> q[2] >> c >> q[3] >> c;

		return in;
	}
}

/*
 * End of Anti-doublon
 */
#endif
