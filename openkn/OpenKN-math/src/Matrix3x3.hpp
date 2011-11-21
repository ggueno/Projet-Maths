/*************************************************************************** \
* Copyright (C) by University Paris-Est - MISS team
* Matrix3x3.hpp created in 09 2008.
* Mail : biri@univ-mlv.fr
*
* This file is part of the OpenKraken-math.
*
* The OpenKraken-math is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* The OpenKraken-math is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
\***************************************************************************/

/*
* Anti-doublon
*/
#ifndef __OPENKN_MATH__MATRIX3X3_HPP__
#define __OPENKN_MATH__MATRIX3X3_HPP__

/*
* Internal Includes
*/
#include "Matrix.hpp"

namespace kn
{

	template<class T> class Matrix3x3 : public Matrix <T>
	{

		public:

			/**
				* \brief Default constructor
				* Create a 3*3 matrix set to identity
				*/
			Matrix3x3(void) : Matrix<T>(3)
			{
				setIdentity();
			}

			/**
				* \brief Copy constructor
				* Create a matrix by copying the input matrix
				* \param m the matrix to copy
				*/
			Matrix3x3(const Matrix3x3<T>& m) : Matrix<T>(3)
			{
				std::copy(m.begin_, m.end_, this->begin_);
			}

			/**
				* \brief Constructor form Matrix
				* Create a matrix by copying the input matrix
				* \param m the matrix to copy
				* \throw MathException if m dimensions are differents
				*/
			Matrix3x3(const Matrix<T>& m);

			/**
				* \brief Copy constructor
				* Create a matrix by copying the input matrix
				* \param m the pointer to the matrix to copy
				* \throw MathException pointer is null
				*/
			Matrix3x3(const Matrix3x3<T>* m);

			/**
				* \brief Create a 3*3 matrix
				* Create a 3*3 matrix and use the value d to set the data of the matrix
				* \param d value used to set data of the matrix
				*/
			Matrix3x3(const T& d) : Matrix<T>(3)
			{
				std::fill(this->begin_, this->end_, d);
			}


			/**
				* \brief create a 3*3 matrix
				* create a 3*3 matrix and set data by using the values array d
				* \param d pointer to an array of data
				* \throw MathException d is null
				*/
			Matrix3x3(const T* d);

			/**
				* \brief Create a 3*3 or matrix
				* Create a matrix using the vector v. if setasrows is set to true,
				* v is used to fill rows of the matrix, v is used to fill columns otherwise
				* \param v a vector
				* \param setasrows defined if vector is used to fill columns or rows
				* \throw MathException size of vector is different of 3
				*/
			Matrix3x3(const Vector<T>& v,const bool& setasrows = true);

			/**
				* \brief Create a 3*3 matrix
				* Create a matrix using the pointer on the vector v. If setasrows is set to true, v is used to fill rows of the matrix, v is used to fill columns otherwise
				* \param v a pointer on an array of vectors
				* \param setasrows defined if vector is used to fill columns or rows
				* \throw MathException v is null
				* \throw MathException if *v size are different of 3
				*/
			Matrix3x3(const Vector<T,StaticStorePolicy<T,3> >* v,const bool& setasrows = true);

			/**
				* \brief Destructor
				*/
			~Matrix3x3(void) {}


		public:

			using Matrix<T>::operator*;


			/**
				* \brief Multiplies the matrix with a vector
				* \param v the vector multiplied with this matrix
				* \return a vector (static storage)
				* \throw MathException vector size is incorrect
				*/
			Vector<T,StaticStorePolicy<T,3> > operator*(const Vector<T,StaticStorePolicy<T,3> >& v) const;

			/**
			 * \brief Multiplies the matrix with a vector
			 * \param v the vector multiplied with this matrix
			 * \return a vector (dynamic storage)
			 * \throw MathException vector size is incorrect
			 */
			Vector<T,DynamicStorePolicy<T> > operator*(const Vector<T,DynamicStorePolicy<T> >& v) const;
			
			
			/**
				* \brief Returns the number of rows of the matrix
				* \return the number of rows
				*/
			inline size_t rows(void) const {
				return 3;
			}

			/**
				* \brief Returns the number of columns of the matrix
				* \return the number of columns
				*/
			inline size_t columns(void) const {
				return 3;
			}

			/**
				* \brief Transposes inplace the current matrix
				* \return this transposed matrix
				*/
			Matrix3x3<T>& transpose(void);

			/**
				* \brief Transposes a copy of the matrix
				* Creates and transposes a copy of this matrix. The current matrix is unchanged
				* \return the transposed copy of the matrix
				*/
			inline Matrix3x3<T> getTranspose(void) const
			{
				return Matrix3x3<T>(*this).transpose();
			}

			/**
				* \brief sets the matrix to identity
				*/
			void setIdentity(void);

			/**
				* \brief Check if it is a square matrix or not
				* \return if the matrix is square
				*/
			inline bool isSquare(void) const {
				return true;
			}

			/**
			* \brief substitute of a vector3 cross product using 3x3 matrix.
			* Given two vector3 x and y, we have z = x^y
			* This equation can be linearized as z = A.y with A : 3x3 matrix.
			* This method fills the A 3x3 matrix from the vector x.
			* \param v : the vector3 used to fill the matrix
			*/
			void cross3x3(const kn::Vector<T,StaticStorePolicy<T,3> > v);

			/**
			* \brief Allocate the matrix m to this matrix
			* \param m the matrix used to defined this matrix
			* \return the matrix
			* \throw MathException matrix size is incorrect
			*/
			Matrix3x3<T>& operator=(const Matrix3x3<T>& m);

			/**
			* \brief Adds two matrices
			* \param m the matrix added to this matrix
			* \return a copy of the matrix
			* \throw MathException matrix size is incorrect
			*/
			Matrix3x3<T> operator+(const Matrix3x3<T>& m) const;

			/**
			* \brief Subtracts two matrices
			* \param m the matrix subtracted to this matrix
			* \return a copy of the matrix
			* \throw MathException matrix size is incorrect
			*/
			Matrix3x3<T> operator-(const Matrix3x3<T>& m) const;

			/**
			* \brief Divides the matrix with a value
			* \param d the value divided with this matrix
			* \return a copy of the matrix
			* \throw MathException d is null
			*/
			Matrix3x3<T> operator/(const T& d) const;

			/**
			* \brief Multiplies two matrices
			* \param m the matrix multiplied with this matrix
			* \return a copy of the matrix
			* \throw MathException matrice size is incorrect
			*/
			Matrix3x3<T> operator*(const Matrix3x3<T>& m) const;

			/**
			* \brief Multiplies the matrix with a value
			* \param d the value multiplied with this matrix
			* \return a copy of the matrix
			*/
			Matrix3x3<T> operator*(const T& d) const;

			/**
			* \brief Compute opposite of the matrix
			* \return a copy of the matrix
			*/
			Matrix3x3<T> operator-(void) const;

			/**
			* \brief Adds the matrix with a matrix
			* \param m the matrix added with this matrix
			* \return the matrix
			* \throw MathException matrix size is incorrect
			*/
			Matrix3x3<T>& operator+=(const Matrix3x3<T>& m);

			/**
			* \brief Subtracts the matrix with a matrix
			* \param m the matrix subtracted with this matrix
			* \return the matrix
			* \throw MathException matrix size is incorrect
			*/
			Matrix3x3<T>& operator-=(const Matrix3x3<T>& m);

			/**
			* \brief Divides the matrix with a value
			* All values of the matrix are divided by d
			* \param d the value divided with this matrix
			* \return the matrix
			* \throw MathException d is null
			*/
			Matrix3x3<T>& operator/=(const T& d);

			/**
			* \brief Multiplies the matrix with a matrix
			* \param m the matrix multiplied with this matrix
			* \return the matrix
			* \throw MathException matrix size is incorrect
			*/
			Matrix3x3<T>& operator*=(const Matrix3x3<T>& m);

			/**
			* \brief Multiplies the matrix with a value
			* \param d the value multiplied with this matrix
			* \return the matrix
			*/
			Matrix3x3<T>& operator*=(const T& d);

			/**
			* \brief Returns a vector with values from a specific row
			* \param row the number of the row
			* \return a vector of values
			* \throw MathException row is out of bounds
			*/
			Vector<T,StaticStorePolicy<T,3> > getRow(const unsigned int& row) const;

			/**
			* \brief Returns a vector with values from a specific column
			* \param column the number of the column
			* \return a vector of values
			* \throw MathException column is out of bounds
			*/
			Vector<T,StaticStorePolicy<T,3> > getColumn(const unsigned int& column) const;

			/**
			* \brief Return the diagonal of the matrix as a vector
			* \return a vector
			*/
			Vector<T,StaticStorePolicy<T,3> > getDiagonal(void) const;

			/**
			* \brief Computes inplace the power p of this matrix
			* \return this matrix
			* \throw MathException not a square matrix
			*/
			Matrix3x3<T>& power(const unsigned int& p);

			/**
			* \brief Trace of the Matrix
			*
			* This represents the sum of each element on the diagonal
			*
			* \return the trace
			*/
			T trace(void) const;

	};



	template<class T>
		Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>* m)
		: Matrix<T>(3)
		{
			if(m==0)
				throw MathException("Pointer is null");
			std::copy(m->begin_, m->end_, this->begin_);
		}


	template<class T>
		Matrix3x3<T>::Matrix3x3(const T* a)
		: Matrix<T>(3)
		{
			if(a==0)
				throw MathException("Pointer is null");
			std::copy(a, a + 9, this->begin_);
		}


	template<class T>
		Matrix3x3<T>::Matrix3x3(const Vector<T>& v,const bool& setasrows) : Matrix<T>(3)
		{
			if(v.size()!=9)
				throw MathException("Vector size is different from Matrix size");

			if(setasrows)
				for(unsigned int i = 0; i < 9; ++i)
					(this->data)[i] = v[i];
			else
				for(unsigned int j = 0; j < 3; ++j)
					for(unsigned int i = 0; i < 3; ++i)
						(this->accessor)[i][j] = v[j*3+i];
		}


	template<class T>
		Matrix3x3<T>::Matrix3x3(const Vector<T,StaticStorePolicy<T,3> >* v,const bool& setasrows)
		: Matrix<T>(3)
		{

			if(v==0)
				throw MathException("Pointer is null");

			if(setasrows)
				for(unsigned int i = 0; i < 3; ++i)
					for(unsigned int j = 0; j < 3; ++j)
						(this->accessor)[i][j] = v[i][j];
			else
				for(unsigned int j = 0; j < 3; ++j)
					for(unsigned int i = 0; i < 3; ++i)
						(this->accessor)[i][j] = v[j][i];

		}

	template<class T>
		Matrix3x3<T>::Matrix3x3(const Matrix<T>& m)
		: Matrix<T>(3) {
			if ((m.rows() != 3) || (m.columns() != 3))
				throw MathException("Matrix3x3 Constructor","Matrix sizes are different");
			std::copy(m.getMatrixArray(), m.getMatrixArray()+m.rows()*m.columns(), this->begin_);
		}

	template<class T>
		Vector<T,StaticStorePolicy<T,3> > Matrix3x3<T>::operator*(const Vector<T,StaticStorePolicy<T,3> >& v) const
		{
// 			std::cerr<<"M3*v with static storage"<<std::endl;
			Vector<T,StaticStorePolicy<T,3> > vtmp;
			vtmp[0] = v[0]*(this->accessor)[0][0] + v[1]*(this->accessor)[0][1] + v[2]*(this->accessor)[0][2];
			vtmp[1] = v[0]*(this->accessor)[1][0] + v[1]*(this->accessor)[1][1] + v[2]*(this->accessor)[1][2];
			vtmp[2] = v[0]*(this->accessor)[2][0] + v[1]*(this->accessor)[2][1] + v[2]*(this->accessor)[2][2];
			return vtmp;
		}

	template<class T>
		Vector<T,DynamicStorePolicy<T> > Matrix3x3<T>::operator*(const Vector<T,DynamicStorePolicy<T> >& v) const
		{
// 			std::cerr<<"M3*v with dyn storage"<<std::endl;
			if(v.size() != 3)
				throw MathException("Matrice rows and vector size are different");

			Vector<T,DynamicStorePolicy<T> > vtmp(3);
			vtmp[0] = v[0]*(this->accessor)[0][0] + v[1]*(this->accessor)[0][1] + v[2]*(this->accessor)[0][2];
			vtmp[1] = v[0]*(this->accessor)[1][0] + v[1]*(this->accessor)[1][1] + v[2]*(this->accessor)[1][2];
			vtmp[2] = v[0]*(this->accessor)[2][0] + v[1]*(this->accessor)[2][1] + v[2]*(this->accessor)[2][2];
			return vtmp;
		}


	template<class T>
		Matrix3x3<T>& Matrix3x3<T>::transpose(void)
		{

			for(unsigned int i = 0; i < 3; ++i)
				for(unsigned int j = 0; j < i; ++j)
		std::swap((this->accessor)[i][j],(this->accessor)[j][i]);

			return *this;
		}


	template<class T>
		void Matrix3x3<T>::setIdentity(void)
		{
			this->setZero();
			(this->accessor)[0][0] = (this->accessor)[1][1] = (this->accessor)[2][2] = T(1.0);
		}




	/**
		* \brief Multiplies a vector with a matrix
		* \param v the vector
		* \param m the matrix
		* \return a matrix
		* \throw MathException matrix size is incorrect
		*/
	template<class U>
		Vector<U,StaticStorePolicy<U,3> > operator* (const Vector<U,StaticStorePolicy<U,3> >& v,
				const Matrix3x3<U>& m)
		{
// 			std::cerr<<"v*M3 with static storage"<<std::endl;
			Vector<U,StaticStorePolicy<U,3> > result;
			result[0] = m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2];
			result[1] = m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2];
			result[2] = m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2];
			return result;
		}
		
		
		/**
		 * \brief Multiplies a vector with a matrix
		 * \param v the vector
		 * \param m the matrix
		 * \return a matrix
		 * \throw MathException matrix size is incorrect
		 */
		template<class U>
		Vector<U,DynamicStorePolicy<U> > operator* (const Vector<U,DynamicStorePolicy<U> >& v,
																								 const Matrix3x3<U>& m)
		{
// 			std::cerr<<"v*M3 with dynamic storage"<<std::endl;
			
			Vector<U,DynamicStorePolicy<U> > result(3);
			result[0] = m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2];
			result[1] = m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2];
			result[2] = m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2];
			return result;
		}
		

	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix3x3<T>& m){
			if(&m == this) return *this;
			std::copy(m.begin_,m.end_,this->begin_);

			return *this;
		}


	template<typename T>
		Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& m) const{
			Matrix3x3<T> result = *this;
			result += m;
			return result;
		}


	template<typename T>
		Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& m) const{
			Matrix3x3<T> result = *this;
			result -= m;
			return result;
		}


	template<typename T>
		Matrix3x3<T> Matrix3x3<T>::operator/(const T& d) const{
			Matrix3x3<T> result = *this;
			result /= d;
			return result;
		}


	template<typename T>
		Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& m) const{

			Matrix3x3<T> result;
			T sum;
			for(unsigned int i = 0; i < 3; ++i)
				for(unsigned int j = 0; j < 3; ++j){
		sum = T(0.0);

		for(unsigned int k = 0; k < 3; ++k){
			sum += (*this)[i][k]*m[k][j];
		}
		result[i][j] = sum;
				}

			return result;
		}

	template<typename T>
		Matrix3x3<T> Matrix3x3<T>::operator*(const T& d) const{
			Matrix3x3<T> result = *this;
			result *= d;
			return result;
		}


	template<typename T>
		Matrix3x3<T> Matrix3x3<T>::operator-(void) const{
			Matrix3x3<T> result = *this;
			std::transform(this->begin_, this->end_, result.begin_, std::negate<T>());
			return result;
		}


	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3<T>& m){
			std::transform(this->begin_, this->end_, m.begin_, this->begin_, std::plus<T>());
			return *this;
		}


	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3<T>& m){
			std::transform(this->begin_, this->end_, m.begin_, this->begin_, std::minus<T>());
			return *this;
		}

	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::operator/=(const T& d){
			if(d==0)
				throw MathException("Value is null");
			std::transform(this->begin_, this->end_, this->begin_, std::bind2nd(std::divides<T>(),d));
			return *this;
		}


	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3<T>& m){

			Matrix3x3<T> tmp = *this;
			T sum;
			for(unsigned int i = 0; i < 3; ++i)
				for(unsigned int j = 0; j < 3; ++j){
		sum = T(0.0);

		for(unsigned int k = 0; k < 3; ++k){
			sum += tmp[i][k]*m[k][j];
		}
		this->accessor[i][j] = sum;
				}
			return *this;
		}

	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::operator*=(const T& d){
			std::transform(this->begin_, this->end_, this->begin_, std::bind2nd(std::multiplies<T>(),d));
			return *this;
		}


	template<typename T>
		Matrix3x3<T>& Matrix3x3<T>::power(const unsigned int& p){

			if(p == 0){
				setIdentity();
				return *this;
			}
			Matrix3x3<T> tmp(*this);

			for(unsigned int i=1; i < p; ++i)
				*this *= tmp;

			return *this;
		}

	template<typename T>
		Vector<T,StaticStorePolicy<T,3> > Matrix3x3<T>::getDiagonal(void) const{
			Vector<T,StaticStorePolicy<T,3> > v;
			for(unsigned int i = 0; i < 3; ++i)
				v[i] = this->accessor[i][i];
			return v;
		}

	template<typename T>
		Vector<T,StaticStorePolicy<T,3> > Matrix3x3<T>::getRow(const unsigned int& row) const{
			if(row >= this->rowsMatrix)
				throw MathException("Out of bounds");
			Vector<T,StaticStorePolicy<T,3> > v;
			for(unsigned int i = 0; i < 3; ++i)
				v[i] = this->accessor[row][i];
			return v;
		}

	template<typename T>
		Vector<T,StaticStorePolicy<T,3> > Matrix3x3<T>::getColumn(const unsigned int& column) const{
			if(column >= this->columnsMatrix)
				throw MathException("Out of bounds");
			Vector<T,StaticStorePolicy<T,3> > v;
			for(unsigned int i = 0; i < 3; ++i)
				v[i] = this->accessor[i][column];
			return v;
		}

	template<typename T>
		void Matrix3x3<T>::cross3x3(const kn::Vector<T,StaticStorePolicy<T,3> > v){
			this->accessor[0][0] =   0.0;  this->accessor[0][1] = -v[2];  this->accessor[0][2] =  v[1];
			this->accessor[1][0] =  v[2];  this->accessor[1][1] =   0.0;  this->accessor[1][2] = -v[0];
			this->accessor[2][0] = -v[1];  this->accessor[2][1] =  v[0];  this->accessor[2][2] =   0.0;
		}


	/**
		* \brief Trace of the Matrix
		*
		* This represents the sum of each element on the diagonal
		*
		* \return the trace
		*/
	template<typename T>
		T Matrix3x3<T>::trace(void) const{
			return (this->accessor[0][0] + this->accessor[1][1] + this->accessor[2][2]);
		}


	/**
		* \brief Multiplies a scalar with a matrix3x3
		* \param d a scalar
		* \param m the matrix3x3
		* \return a matrix3x3
		*/
	template<class U> Matrix3x3<U> operator* (const U& d,
			const Matrix3x3<U>& m){
		return m*d;
	}


	/**
		* \brief Redefines display for a std::vector< kn::Matrix3x3 >
		* \param stream the output stream
		* \param m std::vector of kn::Matrix3x3
		* \return a stream
		*/
	template<class U> std::ostream& operator<< (std::ostream& stream,
			const std::vector< Matrix3x3<U> >& m){
		for(unsigned int c=0; c<m.size() ;c++){
			for(unsigned int i=0; i<3; ++i){
				for (unsigned int j=0; j<3; ++j)
		stream<<m.at(c).at(i,j) << " " ;
				stream<<std::endl;
			}
			stream<<std::endl;
		}
		return stream;
	}


	/*
		* Type definition
		*/

	typedef Matrix3x3<float>  Matrix3x3f;
	typedef Matrix3x3<double> Matrix3x3d;
	typedef Matrix3x3<int>    Matrix3x3i;


	}


	#endif
