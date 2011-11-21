/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Vector.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-image.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__VECTOR_HPP__
#define __OPENKN_MATH__VECTOR_HPP__

/* Removing some warnings on Microsoft Visual C++ */
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>

/*
 * Internal Includes
 */
#include "MathException.hpp"
#include "VectorStaticStoragePolicy.hpp"
#include "VectorDynamicStoragePolicy.hpp"


/*
 * Namespace
 */
namespace kn {

	/*
		* Class definition
		*/

	/**
		* \brief Generic vector class (generic for size and type)
		*/
	template < class T,class SP = class kn::DynamicStorePolicy<T> >
		class Vector {

			/*
			* class variable
			*/
			protected :
				/**
					* \brief Vector size
					*/
				SP v_storage;

				/*
				 *	// ----- Recuperation des infos des passes precedentes -----
				 * 
				 *	vec4 previous_iterations_info = texture2D(slices_sampler, gl_TexCoord[0].xy);
				 * 
				 *	float density_integral = previous_iterations_info.a;
				 * 
				 *	vec3 accumulated_radiance = previous_iterations_info.rgb;
				 * 
					* Constructor & destructors
					*/
			public:

				/**
					* \brief default constructor
					* For a fixed sized vector : does nothing
					* For a dynamic sized vector : Does not allocate any array. Such a vector
					* is called a null vector. This constructor is the unique way to create null vectors: resizing
					* a vector to 0 is not supported (even a dynamic one).
					*/
				Vector();

				/**
					* \brief Copy Constructor
					* \param v Source vector
					*/
				Vector(const Vector<T,DynamicStorePolicy<T> >& v);
				Vector(const Vector<T,StaticStorePolicy<T,2> >& v);
				Vector(const Vector<T,StaticStorePolicy<T,3> >& v);
				Vector(const Vector<T,StaticStorePolicy<T,4> >& v);

				/**
					* \brief Copy Constructor
					* \param v Source vector
					*/
				Vector(Vector<T,SP>* v);

				/**
					* \brief Constructor from a data array
					* \param sizeVec Size of vector to store
					* \param a Source data array
					* \throw MathException data array a is null
					*/
				Vector(const size_t& sizeVec,const T *a);

				/**
					* \brief Constructor for a given dimension
					* This construct a vector of dimension \a dim. Note that this is only useful for dynamic-size
					* vectors. For fixed-size vectors, it is redundant to pass the dimension here
					* (it throws an error if size is different),
					* so it makes more sense to use the default constructor Vector() instead.
					*
					* \param dim The size of the created vector
					*/
				Vector(const size_t& dim);

				/**
					* \brief Constructor from a constant : duplicate this constant on all the vector entries
					* \param sizeVec Size of vector to store
					* \param d Element to duplicate
					*/
				Vector(const size_t& sizeVec,const T &d);

				/**
					* \brief Constructor for 2 dimension vector
					* \param x First element (type float to desambiguate from constructor(int,T))
					* \param y Second element
					*/
				Vector(const float&x,const float& y);

				/**
					* \brief Constructor for 2 dimension vector
					* \param x First element (type double to desambiguate from constructor(int,T))
					* \param y Second element
					*/
				Vector(const double&x,const double& y);

				/**
					* \brief Constructor for 3 dimension vector
					* \param x First element
					* \param y Second element
					* \param z Third element
					*/
				Vector(const T &x,const T&y,const T&z);

				/**
					* \brief Constructor for 4 dimension vector
					* \param x First element
					* \param y Second element
					* \param z Third element
					* \param w Fourth element
					*/
				Vector(const T &x,const T&y,const T&z,const T&w);


				/**
					* \brief Destructor
				*/
				inline ~Vector(void) {}


			/*
				* Public methods
				*/
			public :
				/*
					* \brief Access to the storage policy
					* \return a reference on the storage policy member
					*/
				const SP& getStoragePolicy() const {return v_storage;}

				/**
					* \brief Access to an element of the Vector
					* \param i the number of the element
					* \return a reference on the queried variable
					* \throw MathException i is out of bounds
					*/
				T& at(const unsigned int& i);

				/**
					* \brief Access to an element of the Vector
					* \param i the number of the element
					* \return a reference on the queried variable
					* \throw MathException i is out of bounds
					*/
				const T& at(const unsigned int& i) const;


				/**
					* \brief Access to the first element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline T& x(void) {return v_storage.data()[0];}

				/**
					* \brief Access to the first element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline const T& x(void) const {return v_storage.data()[0];}


				/**
					* \brief Access to the second element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline T& y(void) {return v_storage.data()[1];}

				/**
					* \brief Access to the second element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline const T& y(void) const {return v_storage.data()[1];}

				/**
					* \brief Access to the third element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline T& z(void) {return v_storage.data()[2];}

				/**
					* \brief Access to the third element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline const T& z(void) const {return v_storage.data()[2];}

				/**
					* \brief Access to the fourth element of the Vector
					* \warning There is no bound check
					* \return a reference on the queried variable
					*/
				inline T& w(void) {return v_storage.data()[3];}

				/**
					* \brief Access to the fourth element of the Vector
					* \return a reference on the queried variable
					*/
				inline const T& w(void) const {return v_storage.data()[3];}


				/**
					* \brief Resize and reset this vector
					* \param size new size for the vector
					*/
				void resize(const int& size);

				/**
					* \brief Resize this vector and copy the v into it
					* Copy v data int this vector
					* \param v vector to be copied
					*/
				void resizeAndCopy(const Vector<T,SP>& v);

				/*
					* Operators redefinition
					*/
				/**
					* \brief test if the vector is equal to another one
					* \param v the vector to test
					* \return true if the vectors values are equal, false otherwise
					*/
				bool operator==(const Vector<T,SP>& v) const;

				/**
					* \brief test if the vector differs from another one
					* \param v the vector to test
					* \return true if the vectors are different, false otherwise
					*/
				inline bool operator!=(const Vector<T,SP>& v) const{
					return !(*this == v);
				}

				/**
					* \brief copy the value of the argument vector to this vector
					* \param v the source vector
					* \return the vector reference
					* \throw MathException the incompatible vector size
					*/
				Vector<T,SP>& operator=(const Vector<T,SP>& v);

				/**
					* \brief Fill the vector with a value
					* \param value Value to set the vector with
					* \return the vector
					*/
				Vector<T,SP>& operator=(const T & value);

				/**
					* \brief adds two vectors
					* \param v the vector to be added
					* \return a copy of the vector
					* \throw MathException incompatible vector size
					*/
				Vector<T,SP> operator+(const Vector<T,SP>& v) const;


				/**
					* \brief subtracts two vectors
					* \param v the vector to be substracted
					* \return a copy of the vector
					*/
				Vector<T,SP> operator-(const Vector<T,SP>& v) const;

				/**
					* \brief Divides the Vector by a value
					* \param d the value dividing this Vector
					* \return a copy of the Vector
					* \throw MathException d is null
					*/
				inline Vector<T,SP> operator/(const T& d) const{
					return Vector(*this) /= d;
				}

				/**
					* \brief dot product
					* \param v the Vector used for the dot product
					* \return a copy of the Vector
					* \throw MathException incompatible vector size
					*/
				T operator*(const Vector<T,SP>& v) const;

				/**
					* \brief dot product
					* \param v the Vector used for the dot product
					* \return a copy of the Vector
					* \throw MathException incompatible vector size
					*/
				inline T dot(const Vector<T,SP>& v) const{
					return (*this)*v;
				}

				/**
					* \brief Multiplies the Vector with a value
					* \param d the value multiplied with this Vector
					* \return a copy of the Vector
					*/
				inline Vector<T,SP> operator*(const T& d) const{
					return Vector(*this) *= d;
				}

				/**
					* \brief Compute opposite of the Vector
					* \return a copy of the Vector
					*/
				inline Vector<T,SP> operator-(void)const{
					return Vector<T,SP>(*this) * ((T)(-1));
				}

				/**
					* \brief Adds the Vector with a Vector
					* \param v the Vector to be added
					* \return the Vector
					* \throw MathException incompatible vector size
					*/
				Vector<T,SP>& operator+=(const Vector<T,SP>& v);

				/**
					* \brief Subtracts the Vector with a Vector
					* \param v the Vector to be subtracted
					* \return the Vector
					* \throw MathException incompatible vector size
					*/
				Vector<T,SP>& operator-=(const Vector<T,SP>& v);

				/**
					* \brief Divides the Vector with a value
					* All values of the Vector are divided by d
					* \param d the value divided with this Vector
					* \return the Vector
					* \throw MathException d is null
					*/
				Vector<T,SP>& operator/=(const T& d);

				/**
					* \brief Multiplies the Vector with a value
					* \param d the value multiplied with this Vector
					* \return the Vector
					*/
				Vector<T,SP>& operator*=(const T& d);

				/**
					* \brief Access to an element of the Vector
					* \param i the number of the element
					* \return a reference on the queried variable
					*/
				T& operator[](const unsigned int& i);

				/**
					* \brief Access to an element of the Vector
					* \param i the number of the element
					* \return a reference on the queried variable
					*/
				const T& operator[](const unsigned int& i) const;

				/**
					* \brief Access to an element of the Vector
					* \param i the number of the element
					* \return a reference on the queried variable
					*/
				T& operator()(const unsigned int& i);

				/**
					* \brief Access to an element of the Vector
					* \param i the number of the element
					* \return a reference on the queried variable
					*/
				const T& operator()(const unsigned int& i) const;

				/**
					* \brief cross product between 2 vectors of size 3
					* \param v vector of size 3
					* \return the Vector (of fixed size 3) computed for the cross product ot this and v
					* \throw MathException cross product only with vectors of size 3
					*/
				Vector<T,SP> operator^(const Vector<T,SP>& v) const;

				/**
					* \brief cross product between 2 vectors of size 3
					* \param v vector of size 3
					* \return the Vector computed for the cross product ot this and v
					* \throw MathException cross product only with vectors of size 3
					*/
				inline Vector<T,SP> cross(const Vector<T,SP>& v) const {
					return (*this)^v;
				}



				/*
				 * Vector methods
				 */

				/**
					* \brief Returns the size of the vector (number of elements)
					* \return vector size
					*/
				inline size_t size(void) const {
					return v_storage.size();
				}

				/**
					* \brief Sets the value d on every entry of the vector
					*/
				inline void fill(const T &d){
					std::fill((T*)v_storage.begin(),(T*)v_storage.end(),d);
				}

				/**
					* \brief Reset the vector entries to zero
					*/
				inline void setZero(void){
					fill(T(0.0));
				}

				/**
					* \brief Sets the small values ( |x| < d) to 0
					* \param d the limit around which values are set to 0
					*/
				void roundZero(const double & d = 1.0e-14);

				/**
					* \brief Copies the content of a vector v inside this vector
					* The data from the vector v is duplicated inside this vector from the position "index".
					* \param index : position where the copy starts
					* \param v : the vector to be duplicated
					* \throw MathException v size too big
					* \throw MathException index out of bounds
					*/
				void setSubVector(const unsigned int& index, const Vector<T,SP>& v);

				/**
					* \brief Copies the content of a vector v inside this vector
					* The data from the vector v is duplicated inside this vector from the position "index".
					* \param index1 : position where the copy starts
					* \param index2 : position where we start to copy in v
					* \param size	 : number of element to copy
					* \param v : the vector to be (partially) duplicated
					* \throw MathException size too big
					* \throw MathException index1 out of bounds
					* \throw MathException index2 out of bounds
					*/
				void setSubVector(const unsigned int& index1, const unsigned int& index2,
													const unsigned int& size, const Vector<T,SP>& v);

				/**
					* \brief Returns a sub Vector of the vector
					* \param index : position where the sub Vector starts
					* \param size : size of the sub Vector
					* \throw MathException size too big
					* \throw MathException index out of bounds
					*/
				Vector<T,SP> getSubVector(const unsigned int& index, const int& size) const;


				/**
					* \brief Returns the beginning of the vector data
					* \return a pointer on the vector data array
					*/
				inline const T* begin(void) const {
					return v_storage.begin();
				}


				/**
					* \brief Returns the end of the vector data
					* \return a pointer on the end of the vector data array
					*/
				inline const T* end(void) const {
					return v_storage.end();
				}


				/**
					* \brief Returns the norm of the vector
					* \return vector norm
					*/
				double getNorm(void) const;

				/**
					* \brief Normalize the vector
					* Divide each elements of this vector its norm
					*/
				Vector<T,SP>& normalize(void);

				/**
					* \brief Normalize a copy of the vector
					*/
				Vector<T,SP> getNormalized(void) const;

				/**
					* \brief Swaps two elements of this vector
					* \param index1 1st element
					* \param index2 2nd element
					* \throw MathException index1 or index2 are out of bounds
					*/
				void swap(const unsigned int& index1, const unsigned int& index2);

				/**
					* \brief Returns the homogeneous form of the vector by adding a component.
					* The default value is 1.0 (a finite vector) but could be set as '0' (ideal point) or something else.
					* \param d : value to set on the additional component
					*/
				Vector<T,DynamicStorePolicy<T> > getHomogeneous(const T &d = T(1.0)) const;


				/**
					* \brief Returns the unhomogeneous form of the vector by removing a component.
					* All the component of the vector are devided by the last component, except if this component is zero.
					* \param zeroValue : limit to consider a number equal to zero
					* \throw MathException if called vector size differs from 3
					*/
				Vector<T,DynamicStorePolicy<T> > getUnhomogeneous(const T &zeroValue = T(1.0e-13)) const;

				/**
					* \brief Returns the unhomogeneous 2D form of the 3D vector by removing a component.
					* All the component of the vector are devided by the last component, exept if this component is zero.
					* \param zeroValue : limit to consider a number equal to zero
					* \throw MathException if called vector size differs from 4
				*/
				//Vector<T,3> getUnhomogeneous3(const T &zeroValue = T(1.0e-13)) const;

				/**
					* \brief set the last vector component to 1 (if non-zero).
					* Divide all the components of the vector by the last component if non-zero.
					* \param zeroValue : limit to consider a number equal to zero
					*/
				void setHomogeneousNormalForm(const T &zeroValue = T(1.0e-13));


				/**
					* \brief return a copy the vector in homogeneous normal form (i.e. the last vector component is 1 (if non-zero)).
					* Divide all the components of the vector by the last component if non-zero.
					* \param zeroValue : limit to consider a number equal to zero.
					* \return a copy of the vector in homogeneous normal form.
					*/
				Vector<T,DynamicStorePolicy<T> >  getHomogeneousNormalForm(const T &zeroValue = T(1.0e-13)) const;

	};

	template<class T,class SP>
    Vector<T,SP>::Vector() : v_storage() {}

	template<class T,class SP>
		Vector<T,SP>::Vector(const size_t& dim) : v_storage(dim) {}

	template<class T,class SP>
		Vector<T,SP>::Vector(const Vector<T,DynamicStorePolicy<T> >& v) : v_storage(v.size()) {
			std::copy((T*)(v.begin()),(T*)(v.end()),(T*)begin());
		}
	template<class T,class SP>
		Vector<T,SP>::Vector(const Vector<T,StaticStorePolicy<T,2> >& v) : v_storage(v.size()) {
			std::copy((T*)(v.begin()),(T*)(v.end()),(T*)begin());
		}
	template<class T,class SP>
		Vector<T,SP>::Vector(const Vector<T,StaticStorePolicy<T,3> >& v) : v_storage(v.size()) {
			std::copy((T*)(v.begin()),(T*)(v.end()),(T*)begin());
		}
	template<class T,class SP>
		Vector<T,SP>::Vector(const Vector<T,StaticStorePolicy<T,4> >& v) : v_storage(v.size()) {
			std::copy((T*)(v.begin()),(T*)(v.end()),(T*)begin());
		}
	//*/

	template<class T,class SP>
		Vector<T,SP>::Vector(Vector<T,SP> * v) : v_storage((v!=0)?v->size():0) {
			if(v == 0) throw MathException("Null pointer exception");
			std::copy((T*)v->begin(), (T*)v->end(), (T*)begin());
		}

	template<class T,class SP>
		Vector<T,SP>::Vector(const size_t& dataSize,const T* a) : v_storage(dataSize) {
			if(a == 0) throw MathException("Null pointer exception");
			std::copy((T*)a,(T*)(a+dataSize),(T*)this->begin());
		}

	template<class T,class SP>
		Vector<T,SP>::Vector(const size_t& dataSize,const T &d) : v_storage(dataSize) {
			fill(d);
		}

	template<class T,class SP>
		Vector<T,SP>::Vector(const float &x,const float&y) : v_storage(2) {
			v_storage.data()[0] = x;
			v_storage.data()[1] = y;
		}

	template<class T,class SP>
		Vector<T,SP>::Vector(const double&x,const double&y) : v_storage(2) {
			v_storage.data()[0] = x;
			v_storage.data()[1] = y;
		}


	template<class T,class SP>
		Vector<T,SP>::Vector(const T &x,const T&y,const T&z) : v_storage(3) {
			v_storage.data()[0] = x;
			v_storage.data()[1] = y;
			v_storage.data()[2] = z;
		}

	template<class T,class SP>
		Vector<T,SP>::Vector(const T &x,const T&y,const T&z,const T&w) : v_storage(4) {
			v_storage.data()[0] = x;
			v_storage.data()[1] = y;
			v_storage.data()[2] = z;
			v_storage.data()[3] = w;
		}



	template<class T,class SP>
		void Vector<T,SP>::resize(const int& size){
			v_storage.resize(size);
		}
	/*
	template<class T,class SP>
		Vector<T,Dynamic> Vector<T,s>::convertToDynamic() {
			Vector<T,Dynamic> res(v_storage.size());
			std::copy((T*)begin(),(T*)end(),(T*)res.begin());
			return res;
		}
	*/

	template<class T,class SP>
		void Vector<T,SP>::resizeAndCopy(const Vector<T,SP>& v) {
			v_storage.resize(v.size());
			std::copy((T*)v.begin(),(T*)v.end(),(T*)begin());
		}

	template<class T,class SP>
		T& Vector<T,SP>::at(const unsigned int& i) {
			// CHECK BOUNDS ...
			if(i >= v_storage.size()) throw MathException("Index out of bounds");
			return v_storage.data()[i];
		}

	template<class T,class SP>
		const T& Vector<T,SP>::at(const unsigned int& i) const{
			if(i >= v_storage.size()) throw MathException("Index out of bounds");
			return v_storage.data()[i];
		}

	template<class T,class SP>
		bool Vector<T,SP>::operator==(const Vector<T,SP>& v) const{
			if(v.size() != v_storage.size()) return false;
			return std::equal(begin(), end(), v.begin());
		}

	/// \todo Check that resizement is ok for dynamic vector ? Improvment can be done (no test for fixed vector should be fine ?)
	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::operator=(const Vector<T,SP>& v) {
			if(&v == this) return *this;
			v_storage.resize(v.size());
			std::copy((T*)v.begin(),(T*)v.end(),(T*)begin());
			return *this;
		}

	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::operator=(const T & value) {
			std::fill((T*)begin(),(T*)end(),T(value));
			return *this;
		}

	template<class T,class SP>
		Vector<T,SP> Vector<T,SP>::operator+(const Vector<T,SP>& v) const{
			if(v_storage.size() != v.size()) throw MathException("Incompatible vector size");

			Vector<T,SP> tmp(v.size());
			std::transform((T*)begin(),(T*)end(),(T*)v.begin(),(T*)tmp.begin(), std::plus<T>());
			return tmp;
		}


	template<class T,class SP>
		Vector<T,SP> Vector<T,SP>::operator-(const Vector<T,SP>& v) const{
			if(v_storage.size() != v.size()) throw MathException("Incompatible vector size");

			Vector<T,SP> tmp(v.size());
			std::transform((T*)begin(),(T*)end(),(T*)v.begin(),(T*)tmp.begin(), std::minus<T>());
			return tmp;
		}

	template<class T,class SP>
		T Vector<T,SP>::operator*(const Vector<T,SP>& v) const{
			if(v_storage.size() != v.size()) throw MathException("Incompatible vector size");
			return std::inner_product(begin(), end(), v.begin(),T(0.0));
		}

	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::operator+=(const Vector<T,SP>& v)
		{
			if(v_storage.size() != v.size()) throw MathException("Incompatible vector size");
			std::transform((T*)begin(),(T*)end(),(T*)v.begin(),(T*)begin(), std::plus<T>()); /// \todo : à tester serieusement
			return *this;
		}

	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::operator-=(const Vector<T,SP>& v){
			if(v_storage.size() != v.size()) throw MathException("Incompatible vector size");

			std::transform((T*)begin(),(T*)end(),(T*)v.begin(),(T*)begin(), std::minus<T>()); /// \todo : à tester serieusement
			return *this;
		}

	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::operator/=(const T& d){
			std::transform((T*)begin(),(T*)end(),(T*)begin(), std::bind2nd(std::divides<T>(), d));
			return *this;
		}

	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::operator*=(const T& d){
			std::transform((T*)begin(),(T*)end(),(T*)begin(), std::bind2nd(std::multiplies<T>(), d));
			return *this;
		}

	template<class T,class SP>
		T& Vector<T,SP>::operator[](const unsigned int& i){
			return v_storage.data()[i];
		}

	template<class T,class SP>
		const T& Vector<T,SP>::operator[](const unsigned int& i) const{
			return v_storage.data()[i];
		}

	template<class T,class SP>
		T& Vector<T,SP>::operator()(const unsigned int& i) {
			return v_storage.data()[i];
		}

	template<class T,class SP>
		const T& Vector<T,SP>::operator()(const unsigned int& i) const{
			return v_storage.data()[i];
		}

	template<class T,class SP>
		Vector<T,SP> Vector<T,SP>::operator^(const Vector<T,SP>& v) const {
			if(v_storage.size() != 3) throw MathException("(this) cross product only with vectors of size 3");
			if(v.size() != 3) throw MathException("cross product only with vectors of size 3");

			Vector<T,SP> tmp(3);																							/// TO CHECK
			tmp[0] = v_storage.data()[1]*v[2] - v_storage.data()[2]*v[1];
			tmp[1] = v_storage.data()[2]*v[0] - v_storage.data()[0]*v[2];
			tmp[2] = v_storage.data()[0]*v[1] - v_storage.data()[1]*v[0];

			return tmp;
		}

	template<class T,class SP>
		void Vector<T,SP>::roundZero(const double & d){
			T *iter = (T*)begin();

			while(iter != end()){
				if(std::fabs((double)(*iter)) < d) (*iter) = T(0.0);
				++iter;
			}
		}


	template<class T,class SP>
		void Vector<T,SP>::setSubVector(const unsigned int& index, const Vector<T,SP>& v) {
			if(index >= v_storage.size()) throw MathException("Index is out of bounds");
			if(index + v.size() > v_storage.size()) throw MathException("Index is out of bounds(v.sizeVector is too big)");
			std::copy((T*)v.begin(),(T*)v.end(),(T*)(begin() + index));
		}

	template<class T,class SP>
		void Vector<T,SP>::setSubVector(const unsigned int& index1, const unsigned int& index2,
																		const unsigned int& size, const Vector<T,SP>& v)
		{
			if(index1 >= v_storage.size()) throw MathException("Index1 is out of bounds");
			if(index1 + size > v_storage.size()) throw MathException("Index1 is out of bounds(size is too big)");
			if(index2 >= v.size()) throw MathException("Index2 is out of bounds");
			if(index2 + size > v.size()) throw MathException("Index2 is out of bounds(size is too big)");
			std::copy((T*)(v.begin()+index2),(T*)(v.begin()+index2+size),(T*)(begin() + index1));
		}

	template<class T,class SP>
		Vector<T,SP> Vector<T,SP>::getSubVector(const unsigned int& index, const int& size) const{
			if(index >= v_storage.size()) throw MathException("index is out of bounds");
			if(index + size > v_storage.size()) throw MathException("index is out of bounds (size is too big)");

			Vector<T,SP> v(size);
			std::copy((T*)(begin() + index),(T*)(begin() + index + size),(T*)(v.begin()));
			return v;
		}

	template<class T,class SP>
		double Vector<T,SP>::getNorm(void) const{
			double squareSum = 0.0;
			for(unsigned int i=0;i<size();i++) {
				squareSum += (double)(v_storage.data()[i]*v_storage.data()[i]);
			}
			return sqrt(squareSum);
		}

	template<class T,class SP>
		Vector<T,SP>& Vector<T,SP>::normalize(void) {
			double norm = getNorm();
			for(unsigned int i=0;i<v_storage.size();i++) {
				v_storage.data()[i] = T(v_storage.data()[i] / norm);
			}
			return *this;
		}

	template<class T,class SP>
		Vector<T,SP> Vector<T,SP>::getNormalized(void) const{
			Vector<T,SP> v(*this);
			v.normalize();
			return v;
		}

	template<class T,class SP>
		Vector<T,DynamicStorePolicy<T> > Vector<T,SP>::getHomogeneous(const T &d) const{
			Vector<T,DynamicStorePolicy<T> > tmp(v_storage.size()+1);

			std::copy((T*)begin(),(T*)end(),(T*)tmp.begin());
			tmp[v_storage.size()] = d;

			return tmp;
		}

  template<class T,class SP>
    Vector<T,DynamicStorePolicy<T> > Vector<T,SP>::getUnhomogeneous(const T &zeroValue) const{
      if(v_storage.size() == 1) return *this;

      Vector<T,DynamicStorePolicy<T> > tmp(v_storage.size()-1);

      // unhomogenize
      T value = v_storage.data()[v_storage.size()-1];
      if(std::fabs((float)value) > zeroValue && value != T(1.0))
        std::transform((T*)begin(), (T*)(((T*)end())-1), (T*)(tmp.begin()), std::bind2nd(std::divides<T>(), value));
      else
        std::copy((T*)begin(), ((T*)end())-1, (T*)(tmp.begin()));

      return tmp;
    }



	template<class T,class SP>
		void Vector<T,SP>::setHomogeneousNormalForm(const T &zeroValue){
			T value = v_storage.data()[v_storage.size()-1];
			if(std::fabs((float)value) > (float)zeroValue && value != T(1.0)){
				std::transform((T*)begin(),((T*)end())-1,(T*)begin(), std::bind2nd(std::divides<T>(), value));
				v_storage.data()[v_storage.size()-1] = T(1.0);
			}
		}


	template<class T,class SP>
		Vector<T,DynamicStorePolicy<T> > Vector<T,SP>::getHomogeneousNormalForm(const T &zeroValue) const{
			Vector<T,DynamicStorePolicy<T> > tmp(*this);
			tmp.setHomogeneousNormalForm(zeroValue);
			return tmp;
		}


	/// \todo Verifier serieusement la fonction void Vector<T,SP>::swap !
	template<class T,class SP>
		void Vector<T,SP>::swap(const unsigned int& index1,const unsigned int& index2) {
			if(index1 >= v_storage.size() || index2 >= v_storage.size()) throw MathException("Index out of bounds");
			std::swap(this->at(index1),this->at(index2));
		}

	/**
		* \brief operator <<
		* \param stream output stream
		* \param v Vector to print
		* \return output stream
		*/
	template<class U,class SP>
		std::ostream& operator<< (std::ostream& stream,const Vector<U,SP>& v) {
			if(v.size()==0){
				stream << "Not initialized yet -> size is 0";
				return stream;
			}
			
			stream << "(";
			for (unsigned int i=0; i<v.size()-1; ++i)
				stream << v[i] << " , ";

			stream << v[v.size()-1]<< ")";
			return stream;
		}

	/**
		* \brief operator <<
		* \param stream output stream
		* \param v std::vector of Vector to print
		* \return output stream
		*/
	template<class U,class SP>
		std::ostream& operator<< (std::ostream& stream,const std::vector< Vector<U,SP> >& v) {
			for(unsigned int c=0;c<v.size();c++) {
				if(v.at(c).size()==0) {
					stream << "Not initialized yet -> size is 0"<<std::endl;
					return stream;
				}
				for (unsigned int i=0; i<v.at(c).size(); ++i)
					stream << v.at(c).at(i) << " ";
				stream << std::endl;
			}
			return stream;
		}

	/**
		* \brief Multiplies a value with a Vector
		* \param d the value multiplied with this Vector
		* \param v the vector
		* \return a copy of the Vector
		*/
	template<class U,class SP>
		Vector<U,SP> operator* (const U& d,const Vector<U,SP>& v) {
			return v*d;
		}

  /*
   * Type definition
   */

	//typedef template<class T,Dynamic> Vector<T,Dynamic> Vector<T>;

	typedef Vector<float>    Vectorf;
	typedef Vector<double>   Vectord;
	typedef Vector<int>      Vectori;

	//typedef template<T> Vector<T,StaticStorePolicy<float,2> > Vector2<T>;

	typedef Vector<float,StaticStorePolicy<float,3> >   Vector3f;
	typedef Vector<double,StaticStorePolicy<double,3> > Vector3d;
	typedef Vector<int,StaticStorePolicy<int,3> >       Vector3i;

	typedef Vector<float,StaticStorePolicy<float,2> >   Vector2f;
	typedef Vector<double,StaticStorePolicy<double,2> > Vector2d;
	typedef Vector<int,StaticStorePolicy<int,2> >       Vector2i;

	typedef Vector<float,StaticStorePolicy<float,4> >   Vector4f;
	typedef Vector<double,StaticStorePolicy<double,4> > Vector4d;
	typedef Vector<int,StaticStorePolicy<int,4> >       Vector4i;

	//template <typename T>
	//class AnonymeVectorClass {
	//	typedef Vector<T,StaticStorePolicy<T,2> > Vector2;
	//};

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
