/***************************************************************************\
* Copyright (C) by University Paris-Est - MISS team
* Matrix.hpp created in 09 2008.
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
#ifndef __OPENKN_MATH__MATRIX_HPP__
#define __OPENKN_MATH__MATRIX_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <vector>
#include <iterator>

/*
 * Internal Includes
 */
#include "Vector.hpp"
#include "MathException.hpp"

/*
 * Namespace
 */
namespace kn {

	/*
	 * Class definition
	 */

	/**
		* \brief class to manipulate a matrix
		*/
	template<class T> class Matrix {

		protected:

			/**
				* \brief Number of rows in the matrix
				*/
			size_t rowsMatrix;

			/**
				* \brief Number of columns in the matrix
				*/
			size_t columnsMatrix;

			/**
				* \brief Content of the matrix
				*/
			T* data;

			/**
				* \brief Pointer on the beginning of the data
				*/
			T* begin_;

			/**
				* \brief Pointer on the end of the data
				*/
			T* end_;

			/**
				* \brief Pointers on the beginning of each rows
				*/
			T** accessor;

		public:

			/*
			 * Constructor
			 */

			/**
				* \brief Constructor to build a 0 size matrix
				*/
			Matrix();

			/**
				* \brief Copy constructor
				* Create a matrix by copying the input matrix
				* \param m the matrix to copy
				*/
			Matrix(const Matrix<T>& m);

			/**
				* \brief Copy constructor
				* Create a matrix by copying the input matrix
				* \param m the pointer to the matrix to copy
				* \throw MathException pointer is null
				*/
			Matrix(const Matrix<T>* m);

			/**
				* \brief Create a n*m matrix
				* Create a n*m matrix. Data are not initialized.
				* \param n number of rows
				* \param m number of columns
				* \throw MathException n or m are null
				*/
			Matrix(const size_t& n,const size_t& m);

			/**
				* \brief Create a n*n matrix
				* Create a n*m matrix. Data are not initialized.
				* \param n number of rows
				* \throw MathException n or m are null
				*/
			explicit Matrix(const size_t& n);

			/**
				* \brief Create a n*m matrix
				* Create a n*m matrix and use the value d to set the data of the matrix
				* \param n number of rows
				* \param m number of columns
				* \param d value used to set data of the matrix
				* \throw MathException n or m are null
				*/
			Matrix(const size_t& n,const size_t& m,const T& d);

			/**
				* \brief create a n*m matrix
				* create a n*m matrix and set data by using the values array d
				* \param n number of rows
				* \param m number of columns
				* \param a pointer to an array of data
				* \throw MathException n or m or d are null
				*/
			Matrix(const size_t& n,const size_t& m,T* a);


			/**
				* \brief create a n*n matrix
				* create a n*n matrix and use the value d to set the data of the matrix
				* \param n number of rows and columns
				* \param a pointer to an array of data
				* \throw MathException n or d are null
				*/
			Matrix(const size_t& n, T* a);

			/**
				* \brief Create a n*(size of v) or (size of v)*n matrix
				* Create a matrix using the vector v. if setasrows is set to true,
				* v is used to fill rows of the matrix, v is used to fill columns otherwise
				* \param n number of rows
				* \param m number of columns
				* \param v a vector
				* \param setasrows defined if vector is used to fill columns or rows
				* \throw MathException n or m or size of vector is null
				*/
			Matrix(const size_t& n,const size_t& m,const Vector<T>& v,const bool& setasrows = true);

			/**
				* \brief Create a n*(size of v) or (size of v)*n matrix
				* Create a matrix using the pointer on the vector v. If setasrows is set to true, v is used to fill rows of the matrix, v is used to fill columns otherwise
				* \param n number of rows or columns
				* \param v a pointer on an array of vectors
				* \param setasrows defined if vector is used to fill columns or rows
				* \throw MathException n or v or *v size are null
				* \throw MathException if *v sizes are different
				*/
			Matrix(const size_t& n,const Vector<T>* v,const bool& setasrows = true);

			/*
			 * Destructor
			 */

			/**
				* \brief Destructor
				*/
			virtual ~Matrix(void){
				if(data!=0){
					delete[] accessor;
					delete[] data;
				}
			}

		protected:

			/**
				* \brief Allocates memory and initialize data
				*/
			void allocate(void);

		public:

			/** \brief getting the raw data of the image
				* \return raw data of the image
				*/
			inline virtual T  * begin() const {return begin_;}

			/** \brief getting the end of raw data of the image
				* \return end of raw data of the image
				*/
			inline virtual T  * end() const {return end_;}


			/**
				* \brief Access to an element of the matrix
				* the function allows to reach a specific element of the matrix using m(i,j).
				* \param i the number of the row
				* \param j the number of the column
				* \return a reference to the element of the matrix
				* \throw MathException i or j are out of bounds
				*/
			T& at(const unsigned int& i, const unsigned int& j);

			/**
				* \brief Access to an element of the matrix
				* the function allows to reach a specific element of the matrix using m(i,j).
				* \param i the number of the row
				* \param j the number of the column
				* \return a reference to the element of the matrix
				* \throw MathException i or j are out of bounds
				*/
			const T& at(const unsigned int& i, const unsigned int& j) const;

			/*
			 * Operators redefinition
			 */

			/**
				* \brief Test if the matrix is equal to another one
				* \param m the matrix which is compared this matrix
				* \return true if matrices are equal, false otherwise
				*/
			bool operator==(const Matrix<T>& m) const;

			/**
				* \brief Test if the matrix differ from another one
				* \param m the matrix which is compared this matrix
				* \return true if matrices are different, false otherwise
				*/
			inline bool operator!=(const Matrix<T>& m) const
			{
				return !(*this == m);
			}

			/**
				* \brief Copy m matrix to this matrix if they have the same size; if this matrix has rows=columns=0, allocate the adequat memory before the copy.
				* \param m the matrix used to defined this matrix
				* \return the matrix
				* \throw MathException matrix size is incorrect
				*/
			Matrix<T>& operator=(const Matrix<T>& m);

			/**
				* \brief Fill the matrix with a value
				* \param value Value to set the matrix with
				* \return the matrix
				*/
			Matrix<T>& operator=(const T & value);

			/**
				* \brief Adds two matrices
				* \param m the matrix added to this matrix
				* \return a copy of the matrix
				* \throw MathException matrix size is incorrect
				*/
			Matrix<T> operator+(const Matrix<T>& m) const;

			/**
				* \brief Subtracts two matrices
				* \param m the matrix subtracted to this matrix
				* \return a copy of the matrix
				* \throw MathException matrix size is incorrect
				*/
			Matrix<T> operator-(const Matrix<T>& m) const;

			/**
				* \brief Divides the matrix with a value
				* \param d the value divided with this matrix
				* \return a copy of the matrix
				* \throw MathException d is null
				*/
			Matrix<T> operator/(const T& d) const;

			/**
				* \brief Multiplies two matrices
				* \param m the matrix multiplied with this matrix
				* \return a copy of the matrix
				* \throw MathException matrice size is incorrect
				*/
			Matrix<T> operator*(const Matrix<T>& m) const;

			/**
				* \brief Multiplies the matrix with a vector
				* \param v the vector multiplied with this matrix
				* \return a vector
				* \throw MathException vector size is incorrect
				*/
			Vector<T> operator*(const Vector<T>& v) const;
			/// \copydoc Matrix::operator*(const Vector<T>& v) const
			Vector<T> operator*(const Vector<T,StaticStorePolicy<T,2> >& v) const;
			/// \copydoc Matrix::operator*(const Vector<T>& v) const
			Vector<T> operator*(const Vector<T,StaticStorePolicy<T,3> >& v) const;
			/// \copydoc Matrix::operator*(const Vector<T>& v) const
			Vector<T> operator*(const Vector<T,StaticStorePolicy<T,4> >& v) const;

			/**
				* \brief Multiplies the matrix with a value
				* \param d the value multiplied with this matrix
				* \return a copy of the matrix
				*/
			Matrix<T> operator*(const T& d) const;

			/**
				* \brief Multiplies the matrix m1 with the matrix m2 in the current matrix
				* \param m1 the first matrix of this multiplication
				* \param m2 the second matrix of this multiplication
				*/
			void times(const Matrix<T>& m1,const Matrix<T>& m2);

			/**
				* \brief Compute opposite of the matrix
				* \return a copy of the matrix
				*/
			Matrix<T> operator-(void) const;

			/**
				* \brief Adds the matrix with a matrix
				* \param m the matrix added with this matrix
				* \return the matrix
				* \throw MathException matrix size is incorrect
				*/
			Matrix<T>& operator+=(const Matrix<T>& m);

			/**
				* \brief Adds d to all the elements of the matrix
				* \param d the value to add
				* \return the matrix
				*/
			Matrix<T>& operator+=(const T& d);

			/**
				* \brief Subtracts the matrix with a matrix
				* \param m the matrix subtracted with this matrix
				* \return the matrix
				* \throw MathException matrix size is incorrect
				*/
			Matrix<T>& operator-=(const Matrix<T>& m);

			/**
				* \brief Subtracts d to all the elements of the matrix
				* \param d the value to subtracts
				* \return the matrix
				*/
			Matrix<T>& operator-=(const T& d);

			/**
				* \brief Divides the matrix with a value
				* All values of the matrix are divided by d
				* \param d the value divided with this matrix
				* \return the matrix
				* \throw MathException d is null
				*/
			Matrix<T>& operator/=(const T& d);

			/**
				* \brief Multiplies the matrix with a matrix
				* \param m the matrix multiplied with this matrix
				* \return the matrix
				* \throw MathException matrix size is incorrect
				*/
			Matrix<T>& operator*=(const Matrix<T>& m);

			/**
				* \brief Multiplies the matrix with a value
				* \param d the value multiplied with this matrix
				* \return the matrix
				*/
			Matrix<T>& operator*=(const T& d);

			/**
				* \brief Access to a row of the matrix
				* The function is used to reach a specific element of the matrix.
				* The function returns a pointer to a row of the matrix.
				* Thus, the access to an element can be achieved as follow : m[i][j]
				* There is no checking on column value access thus use this function at your own risk.
				* \param i the number of the row
				* \return a copy of the pointer to the row
				*/
			T* operator[](const unsigned int& i) const;

			/**
				* \brief Access to an element of the matrix
				* the function allows to reach a specific element of the matrix using m(i,j).
				* \param i the number of the row
				* \param j the number of the column
				* \return a reference to the element of the matrix
				*/
			T& operator()(const unsigned int& i,
					const unsigned int& j);

			/**
				* \brief Access to an element of the matrix
				* the function allows to reach a specific element of the matrix using m(i,j).
				* \param i the number of the row
				* \param j the number of the column
				* \return a reference to the element of the matrix
				*/
			const T& operator()(const unsigned int& i,
					const unsigned int& j) const;

			/*
			 * Accessors
			 */

			/**
				* \brief Returns the number of rows of the matrix
				* \return the number of rows
				*/
			inline size_t rows(void) const{
				return rowsMatrix;
			}

			/**
				* \brief Returns the number of columns of the matrix
				* \return the number of columns
				*/
			inline size_t columns(void) const{
				return columnsMatrix;
			}

			/**
				* \brief Returns the norm of the matrix
				* The norm is defined as follow :
				* \f$ \left\|{A}\right\|_{F}^{2}=\sum_{i,j}{|a_{ij}|^2}=trace({A}\times{A})\f$.
				* \return the norm of the matrix
				*/
			double getNorm(void) const;

			/**
       * \brief Normalize the matrix to 1 (L2-norm)
       * Divide each elements of this matrix by its norm
       */
      Matrix<T>& normalize(void);

      /**
       * \brief Normalize a copy of the matrix
       */
      Matrix<T> getNormalized(void) const;

      /**
				* \brief Returns data of the matrix as an array
				* The size of the array is rows*columns
				* \return an array
				*/
			const T* getMatrixArray(void) const{
				return data;
			}


			/**
				* \brief Transposes inplace the current matrix
				* \return this transposed matrix
				*/
			Matrix<T>& transpose(void);

			/**
				* \brief Transposes a copy of the matrix
				* Creates and transposes a copy of this matrix. The current matrix is unchanged
				* \return the transposed copy of the matrix
				*/
			inline Matrix<T> getTranspose(void) const
			{
				return Matrix<T>(*this).transpose();
			}

			/**
				* \brief Computes inplace the power p of this matrix
				* \return this matrix
				* \throw MathException not a square matrix
				*/
			Matrix<T>& power(const unsigned int& p);

			/**
				* \brief sets the matrix to identity
				*/
			void setIdentity(void);

			/**
				* \brief sets values of the matrix to zero
				*/
			inline void setZero(void)
			{
				std::fill(begin_,end_,T(0.0));
			}

			/**
				* \brief Sets the value d on every entry of the vector
				*/
			inline void fill(const T &d){
				std::fill(begin_,end_,d);
			}

			/**
				* \brief sets values near 0 (d more or less) to 0
				* \param d the limit around which values are set to 0
				*/
			void roundZero(const double& d = 1.0e-14);

			/**
				* \brief Copies the content of matrix m inside this matrix.
				* Data from the matrix m are duplicated inside this matrix at the position row and column.
				* \param row the row where start the copy
				* \param column the column where start the copy
				* \param m matrix duplicated inside this matrix
				* \throw MathException m cannot be duplicated inside this matrix
				* \throw MathException row and column are out of bounds
				*/
			void setSubMatrix(const unsigned int& row,
					const unsigned int& column,
					const Matrix<T>& m);

			/**
				* \brief Return subMatrix of the current matrix.
				* Data from the current matrix are duplicated from the position (firstrow,firstcolumn) and return in a new matrix of size (row,column).
				* \param firstrow the row where start the copy
				* \param row the number of row to copy
				* \param firstcolumn the column where start the copy
				* \param column the number of column to copy
				* \throw MathException row or column are out of bounds
				*/
			Matrix<T> getSubMatrix(const unsigned int& firstrow,const unsigned int& row,
				const unsigned int& firstcolumn,const unsigned int& column);

			/**
				* \brief Defines a row of the matrix using a vector (dynamic, 3D or 4D)
				* \param row the number of the row where the vector is copied
				* \param v the vector
				* \throw MathException v size is null
				* \throw MathException row is out of bounds
				*/
			void setRow(const unsigned int& row,const Vector<T,DynamicStorePolicy<T> >& v);
			/// \copydoc Matrix::setRow(const unsigned int& row,const Vector<T,DynamicStorePolicy<T> >& v)
			void setRow(const unsigned int& row,const Vector<T,StaticStorePolicy<T,3> >& v);
			/// \copydoc Matrix::setRow(const unsigned int& row,const Vector<T,DynamicStorePolicy<T> >& v)
			void setRow(const unsigned int& row,const Vector<T,StaticStorePolicy<T,4> >& v);

			/**
				* \brief Defines a row of the matrix using an array of data
				* \param row the number of the row where the array is copied
				* \param a the array
				* \throw MathException a is null
				* \throw MathException row is out of bounds
				*/
			void setRow(const unsigned int& row,T* a);

			/**
				* \brief Defines a row of the matrix using the constant \a d
				* \param row the number of the row where the constant is copied
				* \param d the constant
				* \throw MathException out of bounds
				*/
			void setRow(const unsigned int& row,const T& d);

			/**
				* \brief Defines a column of the matrix using a vector (dynamic, 3D or 4D)
				* \param column the number of the column where the vector is copied
				* \param v the vector
				* \throw MathException v size is null
				* \throw MathException column is out of bounds
				*/
			void setColumn(const unsigned int& column,const Vector<T,DynamicStorePolicy<T> >& v);
			/// \copydoc Matrix::setColumn(const unsigned int& column,const Vector<T,DynamicStorePolicy<T> >& v)
			void setColumn(const unsigned int& column,const Vector<T,StaticStorePolicy<T,3> >& v);
			/// \copydoc Matrix::setColumn(const unsigned int& column,const Vector<T,DynamicStorePolicy<T> >& v)
			void setColumn(const unsigned int& column,const Vector<T,StaticStorePolicy<T,4> >& v);

			/**
				* \brief Defines a column of the matrix using an array of data
				* \param column the number of the column where the array is copied
				* \param a the array
				* \throw MathException a is null
				* \throw MathException column is out of bounds
				*/
			void setColumn(const unsigned int& column,const T* a);

			/**
				* \brief Defines a column of the matrix using the constant d
				* \param column the number of the column where the constant is copied
				* \param d the constant
				* \throw MathException column is out of bounds
				*/
			void setColumn(const unsigned int& column,const T& d);

			/**
				* \brief Returns a vector with values from a specific row
				* \param row the number of the row
				* \return a vector of values
				* \throw MathException row is out of bounds
				*/
			Vector<T,DynamicStorePolicy<T> > getRow(const unsigned int& row) const;

			/**
			* \brief Returns a vector with values from a specific column
			* \param column the number of the column
			* \return a vector of values
			* \throw MathException column is out of bounds
			*/
			Vector<T,DynamicStorePolicy<T> > getColumn(const unsigned int& column) const;

			/**
			* \brief Swaps two rows of this matrix
			* The swap is not applied if row1=row2
			* \param row1 number of the first row
			* \param row2 number of the second row
			* \throw MathException row1 or row2 are out of bounds
			*/
			void swapRows(const unsigned int& row1,const unsigned int& row2);

			/**
			* \brief Swaps two columns of this matrix
			* The swap is not applied if column1=column2
			* \param column1 number of the first column
			* \param column2 number of the second column
			* \throw MathException column1 or column2 are out of bounds
			*/
			void swapColumns(const unsigned int& column1,const unsigned int& column2);

			/**
			* \brief Sets diagonal of the matrix with values from a vector
			* \param v the vector of values
			* \throw MathException vector size is incorrect
			*/
			void setDiagonal(const Vector<T,DynamicStorePolicy<T> >& v);

			/**
			* \brief Sets diagonal of the matrix with values from an array
			* \param a an array of values
			* \throw MathException pointer is null
			*/
			void setDiagonal(const T* a);

			/**
			* \brief Sets diagonal of the matrix with a constant
			* \param d a value
			*/
			void setDiagonal(const T& d);

			/**
			* \brief Return the diagonal of the matrix as a vector
			* \return a vector
			*/
			Vector<T,DynamicStorePolicy<T> > getDiagonal(void) const;

			/**
			* \brief Check if it is a square matrix or not
			* \return if the matrix is square
			*/
			inline bool isSquare(void) const{
				return rowsMatrix == columnsMatrix;
			}

			/**
			* \brief Trace of the Matrix
			* This represents the sum of each element on the diagonal
			* \return the trace
			*/
			T trace(void) const;

			/**
			* \brief substitute of a vector3 cross product using 3x3 matrix.
			* Given two vector3 x and y, we have z = x^y
			* This equation can be linearized as z = A.y with A : 3x3 matrix.
			* This method fills the A 3x3 matrix from the vector x.
			* \param v : the vector3 used to fill the matrix
			* \throw MathException matrix and vector dimension should be 3
			*/
			void cross3x3(const kn::Vector<T,DynamicStorePolicy<T> > v);
			/// \copydoc Matrix::cross3x3(const kn::Vector<T,DynamicStorePolicy<T> > v)
			void cross3x3(const kn::Vector<T,StaticStorePolicy<T,3> > v);

	};

	template<typename T>
		Matrix<T>:: Matrix()
		: rowsMatrix(0), columnsMatrix(0){
			data     = NULL;
			begin_   = NULL;
			end_     = NULL;
			accessor = NULL;
		}

	template<typename T>
		Matrix<T>:: Matrix(const Matrix<T>& m)
		: rowsMatrix(m.rows()), columnsMatrix(m.columns()){
			allocate();
			std::copy(m.begin_, m.end_, begin_);
		}


	template<typename T>
		Matrix<T>::Matrix(const Matrix<T>* m)
		: rowsMatrix(m->rows()), columnsMatrix(m->columns()){
			if(m==0)
				throw MathException("Pointer is null");
			allocate();
			std::copy(m->begin_, m->end_, begin_);
		}


	template<typename T>
		Matrix<T>::Matrix(const size_t& n,
				const size_t& m)
		:rowsMatrix(n), columnsMatrix(m){
			if(m==0 || n==0)
				throw MathException("Matrix size is null");
			allocate();
		}


	template<typename T>
		Matrix<T>::Matrix(const size_t& n)
		:rowsMatrix(n), columnsMatrix(n){
			if(n==0)
				throw MathException("Matrix size is null");
			allocate();
		}


	template<typename T>
		Matrix<T>::Matrix(const size_t& n,const size_t& m,const T& d) :rowsMatrix(n), columnsMatrix(m) {
			if(m==0 || n==0)
				throw MathException("Matrix size is null");
			allocate();
			std::fill(begin_, end_, d);
		}


	template<typename T>
		Matrix<T>::Matrix(const size_t& n,const size_t& m,T* a) :rowsMatrix(n), columnsMatrix(m) {
			if(m==0 || n==0)
				throw MathException("Matrix size is null");
			if(a==0)
				throw MathException("Pointer is null");
			allocate();
			std::copy(a, a + n*m, this->begin_);
		}



	template<typename T>
		Matrix<T>::Matrix(const size_t& n, T* a)
		:rowsMatrix(n), columnsMatrix(n){
			if(n==0)
				throw MathException("Matrix size is null");
			if(a==0)
				throw MathException("Pointer is null");
			allocate();
			std::copy(a, a + n*n, this->begin_);
		}


	template<typename T>
		Matrix<T>::Matrix(const size_t& n,const size_t& m,const Vector<T>& v,const bool& setasrows)
			:rowsMatrix(n), columnsMatrix(m)
		{
			if(m==0 || n==0)
				throw MathException("Matrix size is null");
			if(v.size()!=n*m)
				throw MathException("Vector size is different from Matrix size");

			allocate();

			if(setasrows)
				for(unsigned int i = 0; i < rowsMatrix*columnsMatrix; ++i)
					data[i] = v[i];
			else
				for(unsigned int j = 0; j < columnsMatrix; ++j)
					for(unsigned int i = 0; i < rowsMatrix; ++i)
						accessor[i][j] = v[j*columnsMatrix+i];
		}


	template<typename T> Matrix<T>::Matrix(const size_t& n,const Vector<T>* v,const bool& setasrows) {
		if(n==0)
			throw MathException("Matrix size is null");
		if(v==0)
			throw MathException("Pointer is null");
		unsigned int checksize = 0;
		for(unsigned int i = 0; i < n; ++i){
			if(v[i].size()==0)
				throw MathException("One vector size is null");
			if(i==0)
				checksize = v[i].size();
			else
				if(v[i].size() != checksize)
					throw MathException("Vectors size are different");
		}

		if(setasrows){
			rowsMatrix = n;
			columnsMatrix = v[0].size();
			allocate();
			for(unsigned int i = 0; i < n; ++i)
				for(unsigned int j = 0; j < (v[i]).size(); ++j)
					accessor[i][j] = v[i][j];
		}else{
			rowsMatrix = v[0].size();
			columnsMatrix = n;
			allocate();
			for(unsigned int j = 0; j < n; ++j)
				for(unsigned int i = 0; i < (v[i]).size(); ++i)
					accessor[i][j] = v[j][i];
		}
	}



	template<typename T>
		void Matrix<T>::allocate(void){
			this->data = this->begin_ = this->end_ = 0;
			this->accessor = 0;
			this->data = new T[rowsMatrix*columnsMatrix];
			this->begin_ = this->data;
			this->end_ = this->begin_ + this->rowsMatrix*this->columnsMatrix;
			this->accessor = new T*[this->rowsMatrix];
			for(unsigned int i = 0; i < this->rowsMatrix; ++i)
				this->accessor[i] = this->begin_ + i*this->columnsMatrix;
		}

	template<typename T>
		T& Matrix<T>::at(const unsigned int& i, const unsigned int& j) {
			if(i>=rowsMatrix || j>=columnsMatrix)
				throw MathException("Out of bounds");

			return accessor[i][j];
		}

	template<typename T>
		const T& Matrix<T>::at(const unsigned int& i, const unsigned int& j) const {
			if(i>=rowsMatrix || j>=columnsMatrix)
				throw MathException("Out of bounds");

			return accessor[i][j];
		}


	template<typename T>
		bool Matrix<T>::operator==(const Matrix<T>& m) const{
			if(m.rowsMatrix != rowsMatrix || m.columnsMatrix != columnsMatrix) return false;
			return std::equal(begin_, end_, m.begin_);
		}


	template<typename T>
		Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m){
			if(&m == this) return *this;

			if(rowsMatrix == 0 && columnsMatrix == 0){
	rowsMatrix = m.rowsMatrix;
	columnsMatrix = m.columnsMatrix;
	allocate();
			}

			if(m.rowsMatrix == rowsMatrix && m.columnsMatrix == columnsMatrix)
	std::copy(m.begin_,m.end_,begin_);
			else
				throw  MathException("Matrices'size are different");

			return *this;
		}

	template<typename T>
		Matrix<T>& Matrix<T>::operator=(const T & value) {
			std::fill(begin_,end_,T(value));

			return *this;
		}


	template<typename T>
		Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const{
			Matrix<T> result = *this;
			result += m;
			return result;
		}


	template<typename T>
		Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const{
			Matrix<T> result = *this;
			result -= m;
			return result;
		}


	template<typename T>
		Matrix<T> Matrix<T>::operator/(const T& d) const{
			Matrix<T> result = *this;
			result /= d;
			return result;
		}


	template<typename T>
		Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const{

			if(m.rowsMatrix != columnsMatrix)
				throw MathException("Matrices'size is incorrect");

			Matrix<T> result(rowsMatrix,m.columnsMatrix);
			result.times(this,m);
			return result;
		}

		template<typename T>
		void Matrix<T>::times(const Matrix<T>& m1,const Matrix<T>& m2){

			if(m1.columnsMatrix != m2.rowsMatrix)
				throw MathException("Matrices'size is incorrect");

			if(m1.rowsMatrix != rowsMatrix)
				throw MathException("Matrices' rows size is incorrect");

			if(m2.columnsMatrix != columnsMatrix)
				throw MathException("Matrices' columns size is incorrect");

			T sum;
			for(unsigned int i = 0; i < rowsMatrix; ++i)
				for(unsigned int j = 0; j < columnsMatrix; ++j){
					sum = T(0.0);
					for(unsigned int k = 0; k < m1.columnsMatrix; ++k){
						sum += m1[i][k]*m2[k][j];
					}
					accessor[i][j] = sum;
				}
		}

	template<typename T>
		Vector<T> Matrix<T>::operator*(const Vector<T>& v) const {
			if(v.size() != columnsMatrix)
				throw MathException("Matrice rows and vector size are different");

			Vector<T,DynamicStorePolicy<T> > vtmp(rowsMatrix);
			T sum;
			for(unsigned int i = 0; i < rowsMatrix; ++i){
				sum = T(0);
				for(unsigned int j = 0; j < columnsMatrix; ++j){
					sum += accessor[i][j]*v[j];
				}
				vtmp[i] = sum;
			}
			return vtmp;
		}
		
	template<typename T>
		Vector<T,DynamicStorePolicy<T> > Matrix<T>::operator*(const Vector<T,StaticStorePolicy<T,2> >& v) const {
			if(v.size() != columnsMatrix)
				throw MathException("Matrice rows and vector size are different");

			Vector<T,DynamicStorePolicy<T> > vtmp(rowsMatrix);
			T sum;
			for(unsigned int i = 0; i < rowsMatrix; ++i) {
				sum = T(0);
				for(unsigned int j = 0; j < columnsMatrix; ++j) {
					sum += accessor[i][j]*v[j];
				}
				vtmp[i] = sum;
			}
			return vtmp;
		}
	template<typename T>
		Vector<T,DynamicStorePolicy<T> > Matrix<T>::operator*(const Vector<T,StaticStorePolicy<T,3> >& v) const {
			if(v.size() != columnsMatrix)
				throw MathException("Matrice rows and vector size are different");

			Vector<T,DynamicStorePolicy<T> > vtmp(rowsMatrix);
			T sum;
			for(unsigned int i = 0; i < rowsMatrix; ++i){
				sum = T(0);
				for(unsigned int j = 0; j < columnsMatrix; ++j){
					sum += accessor[i][j]*v[j];
				}
				vtmp[i] = sum;
			}
			return vtmp;
		}
	template<typename T>
		Vector<T,DynamicStorePolicy<T> > Matrix<T>::operator*(const Vector<T,StaticStorePolicy<T,4> >& v) const {
			if(v.size() != columnsMatrix)
				throw MathException("Matrice rows and vector size are different");

			Vector<T,DynamicStorePolicy<T> > vtmp(rowsMatrix);
			T sum;
			for(unsigned int i = 0; i < rowsMatrix; ++i){
				sum = T(0);
				for(unsigned int j = 0; j < columnsMatrix; ++j){
					sum += accessor[i][j]*v[j];
				}
				vtmp[i] = sum;
			}
			return vtmp;
		}


	template<typename T>
		Matrix<T> Matrix<T>::operator*(const T& d) const{
			Matrix<T> result = *this;
			result *= d;
			return result;
		}


	template<typename T>
		Matrix<T> Matrix<T>::operator-(void) const{
			Matrix<T> result = *this;
			std::transform(begin_, end_, result.begin_, std::negate<T>());
			return result;
		}


	template<typename T>
		Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m){
			if(m.rowsMatrix != rowsMatrix || m.columnsMatrix != columnsMatrix)
				throw MathException("Matrices'size is incorrect");
			std::transform(begin_, end_, m.begin_, begin_, std::plus<T>());
			return *this;
		}


	template<typename T>
		Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m){
			if(m.rowsMatrix != rowsMatrix || m.columnsMatrix != columnsMatrix)
				throw MathException("Matrices'size is incorrect");
			std::transform(begin_, end_, m.begin_, begin_, std::minus<T>());
			return *this;
		}

	template<typename T>
		Matrix<T>& Matrix<T>::operator/=(const T& d){
			if(d==0)
				throw MathException("Value is null");
			std::transform(begin_, end_, begin_, std::bind2nd(std::divides<T>(),d));
			return *this;
		}

	template<typename T>
		Matrix<T>& Matrix<T>::operator+=(const T& d){
			std::transform(begin_, end_, begin_, std::bind2nd(std::plus<T>(),d));
			return *this;
		}

	template<typename T>
		Matrix<T>& Matrix<T>::operator-=(const T& d){
			std::transform(begin_, end_, begin_, std::bind2nd(std::minus<T>(),d));
			return *this;
		}

	template<typename T>
		Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m){

			if(rowsMatrix != columnsMatrix)
				throw MathException("Matrices'size is incorrect");

			if(m.rowsMatrix != m.columnsMatrix)
				throw MathException("Matrices'size is incorrect");

			if(m.rowsMatrix != columnsMatrix)
				throw MathException("Matrices'size is incorrect");

			Matrix<T> tmp = *this;
			T sum;
			for(unsigned int i = 0; i < rowsMatrix; ++i)
				for(unsigned int j = 0; j < m.columnsMatrix; ++j){
					sum = T(0.0);

					for(unsigned int k = 0; k < columnsMatrix; ++k){
						sum += tmp[i][k]*m[k][j];
					}
					accessor[i][j] = sum;
				}
			return *this;
		}

	template<typename T>
		Matrix<T>& Matrix<T>::operator*=(const T& d){
			std::transform(begin_, end_, begin_, std::bind2nd(std::multiplies<T>(),d));
			return *this;
		}


	template<typename T>
		T* Matrix<T>::operator[](const unsigned int& i) const{
			return accessor[i];
		}

	template<typename T>
		T& Matrix<T>::operator()(const unsigned int& i, const unsigned int& j) {
			return accessor[i][j];
		}

	template<typename T>
		const T& Matrix<T>::operator()(const unsigned int& i, const unsigned int& j) const{
			return accessor[i][j];
		}

	template<typename T>
		double Matrix<T>::getNorm(void) const{
			double norm = 0.0;
			for(unsigned int i = 0; i < rowsMatrix*columnsMatrix; ++i)
				norm += data[i]*data[i];
			return sqrt(norm);
		}

  template<class T>
    Matrix<T>& Matrix<T>::normalize(void){
      double norm = getNorm();
      double epsilon = 1.0e-14;
      if(fabs(norm) < epsilon) return *this;
      T *iter = begin_;
      while(iter != end_){
        *iter /= norm;
        ++iter;
      }
      return *this;
    }

  template<class T>
    Matrix<T> Matrix<T>::getNormalized(void) const{
      Matrix<T> m(*this);
      m.normalize();
      return m;
    }


	/**
	* \brief Transposes inplace the current matrix
	* \return this transposed matrix
	*/
	template<typename T>
		Matrix<T>& Matrix<T>::transpose(void){
			Matrix<T> tmp(*this);
			std::swap(rowsMatrix,columnsMatrix);

			if(data!=0){
				delete[] accessor;
				delete[] data;
			}
			allocate();
			for(unsigned int i = 0; i < rowsMatrix; ++i)
				for(unsigned int j = 0; j < columnsMatrix; ++j)
					accessor[i][j] = tmp[j][i];

			return *this;
		}


	template<typename T>
		Matrix<T>& Matrix<T>::power(const unsigned int& p){
			if(rowsMatrix != columnsMatrix)
				throw MathException("Matrix is not square");

			if(p == 0){
				setIdentity();
				return *this;
			}
			Matrix<T> tmp(*this);

			for(unsigned int i=1; i < p; ++i)
				*this *= tmp;

			return *this;
		}

	/**
	* \brief sets the matrix to identity
	*/
	template<typename T>
		void Matrix<T>::setIdentity(void){
			setZero();
			setDiagonal(T(1.0));
		}


	template<typename T>
		void Matrix<T>::roundZero(const double& d){
			T *iter = begin_;

			while(iter != end_){
				if(std::abs((*iter)) < d) (*iter) = T(0.0);
				++iter;
			}
		}

	template<typename T>
		void Matrix<T>::setSubMatrix(const unsigned int& row,
				const unsigned int& column,
				const Matrix<T>& m){

			if(row + m.rowsMatrix > rowsMatrix || column + m.columnsMatrix > columnsMatrix)
				throw MathException("Input matrix size is incorrect");

			for(unsigned int i = 0; i < m.rowsMatrix; ++i)
				std::copy(m.accessor[i], m.accessor[i]+m.columnsMatrix,accessor[i+row]+column);

		}

	template<typename T>
		Matrix<T> Matrix<T>::getSubMatrix(const unsigned int& firstrow,const unsigned int& row,
				const unsigned int& firstcolumn,const unsigned int& column){

			if(firstrow + row > rowsMatrix || firstcolumn + column > columnsMatrix)
				throw MathException("Input parameter row/column size is incorrect");

			Matrix<T> tmp(row,column);

			for(unsigned int i = 0; i < row; ++i)
				std::copy(accessor[firstrow+i]+firstcolumn, accessor[firstrow+i]+firstcolumn+column,tmp.accessor[i]);

			return tmp;
		}

	template<typename T>
		void Matrix<T>::setRow(const unsigned int& row,const Vector<T,DynamicStorePolicy<T> >& v) {
			if(row >= rowsMatrix)
				throw MathException("Out of bounds");
			if (v.size() > columnsMatrix)
				throw MathException("Input vector size is incorrect");

			for(unsigned int i = 0; i < columnsMatrix; ++i)
				accessor[row][i] = v[i];
		}

	template<typename T>
		void Matrix<T>::setRow(const unsigned int& row,const Vector<T,StaticStorePolicy<T,3> >& v) {
			if (columnsMatrix != 3) throw MathException("Error in setRow with explicit 3D Vector : columns of matrix must be 3 !");
			if(row >= rowsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < columnsMatrix; ++i)
				accessor[row][i] = v[i];
		}

	template<typename T>
		void Matrix<T>::setRow(const unsigned int& row,const Vector<T,StaticStorePolicy<T,4> >& v) {
			if (columnsMatrix != 4) throw MathException("Error in setRow with explicit 4D Vector : columns of matrix must be 4 !");
			if(row >= rowsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < columnsMatrix; ++i)
				accessor[row][i] = v[i];
		}

	template<typename T>
		void Matrix<T>::setRow(const unsigned int& row,T* a) {
			if(row >= rowsMatrix)
				throw MathException("Out of bounds");
			std::copy(a, a+columnsMatrix,accessor[row]);
		}

	template<typename T>
		void Matrix<T>::setRow(const unsigned int& row,const T& d) {
			if(row >= rowsMatrix)
				throw MathException("Out of bounds");
			std::fill(accessor[row], accessor[row]+columnsMatrix,d);
		}


	template<typename T>
		void Matrix<T>::setColumn(const unsigned int& column,const Vector<T,DynamicStorePolicy<T> >& v) {
			if(column >= columnsMatrix)
				throw MathException("Out of bounds");
			if (v.size() > rowsMatrix)
				throw MathException("Input vector size is incorrect");

			for(unsigned int i = 0; i < rowsMatrix; ++i)
				accessor[i][column] = v[i];
		}

	template<typename T>
		void Matrix<T>::setColumn(const unsigned int& column,const Vector<T,StaticStorePolicy<T,3> >& v) {
			if (rowsMatrix!=3) throw MathException("Error in setColumn with explicit 3D Vector : columns of matrix must be 3 !");
			if(column >= columnsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < rowsMatrix; ++i)
				accessor[i][column] = v[i];
		}

	template<typename T>
		void Matrix<T>::setColumn(const unsigned int& column,const Vector<T,StaticStorePolicy<T,4> >& v) {
			if (rowsMatrix!=4) throw MathException("Error in setColumn with explicit 4D Vector : columns of matrix must be 4 !");
			if(column >= columnsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < rowsMatrix; ++i)
				accessor[i][column] = v[i];
		}


	template<typename T>
		void Matrix<T>::setColumn(const unsigned int& column,const T* a) {
			if(column >= columnsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < rowsMatrix; ++i)
				accessor[i][column] = a[i];
		}


	template<typename T>
		void Matrix<T>::setColumn(const unsigned int& column,const T& d) {
			if(column >= columnsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < rowsMatrix; ++i)
				accessor[i][column] = d;
		}

	template<typename T>
		Vector<T,DynamicStorePolicy<T> > Matrix<T>::getRow(const unsigned int& row) const {
			if(row >= rowsMatrix)
				throw MathException("Out of bounds");
			Vector<T,DynamicStorePolicy<T> > v(columnsMatrix);
			for(unsigned int i = 0; i < columnsMatrix; ++i)
				v[i] = accessor[row][i];
			return v;
		}

	template<typename T>
		Vector<T,DynamicStorePolicy<T> > Matrix<T>::getColumn(const unsigned int& column) const {
			if(column >= columnsMatrix)
				throw MathException("Out of bounds");
			Vector<T,DynamicStorePolicy<T> > v(rowsMatrix);
			for(unsigned int i = 0; i < rowsMatrix; ++i)
				v[i] = accessor[i][column];
			return v;
		}


	template<typename T>
		void Matrix<T>::swapRows(const unsigned int& row1,
				const unsigned int& row2){
			if(row1 >= rowsMatrix || row2 >= rowsMatrix)
				throw MathException("Out of bounds");

			std::swap_ranges(accessor[row1],accessor[row1]+columnsMatrix,accessor[row2]);
		}


	template<typename T>
		void Matrix<T>::swapColumns(const unsigned int& column1,
				const unsigned int& column2){
			if(column1 >= columnsMatrix || column2 >= columnsMatrix)
				throw MathException("Out of bounds");

			for(unsigned int i = 0; i < rowsMatrix; ++i)
				std::swap(accessor[i][column1],accessor[i][column2]);
		}


	template<typename T>
		void Matrix<T>::setDiagonal(const Vector<T,DynamicStorePolicy<T> >& v){
			unsigned int min = std::min(columnsMatrix,rowsMatrix);

			if(v.size() != min)
				throw MathException("Vector size is incorrect");

			for(unsigned int i = 0; i < min; ++i)
				accessor[i][i] = v[i];
		}


	template<typename T>
		void Matrix<T>::setDiagonal(const T* a){
			unsigned int min = std::min(columnsMatrix,rowsMatrix);

			for(unsigned int i = 0; i < min; ++i)
				accessor[i][i] = a[i];
		}

	template<typename T>
		void Matrix<T>::setDiagonal(const T& d)
		{
			unsigned int min = std::min(columnsMatrix,rowsMatrix);

			for(unsigned int i = 0; i < min; ++i)
				accessor[i][i] = d;
		}


	template<typename T>
		Vector<T,DynamicStorePolicy<T> > Matrix<T>::getDiagonal(void) const{
			unsigned int min = std::min(columnsMatrix,rowsMatrix);
			Vector<T,DynamicStorePolicy<T> > v(min);
			for(unsigned int i = 0; i < min; ++i)
				v[i] = accessor[i][i];
			return v;
		}

	template<typename T>
		T Matrix<T>::trace(void) const{
			T sum = 0;
			unsigned int min = std::min(columnsMatrix,rowsMatrix);
			for(unsigned int i = 0; i < min; ++i)
				sum += accessor[i][i];
			return sum;
		}

	template<typename T>
		void Matrix<T>::cross3x3(const kn::Vector<T,DynamicStorePolicy<T> > v) {
			if(v.size() != 3)
				throw MathException("Cross3x3 : argument shoud be a 3-vector");

			if(rowsMatrix != 3 && columnsMatrix != 3)
				throw MathException("Cross3x3 is valid only with 3x3 matrices");

			accessor[0][0] =   0.0;  accessor[0][1] = -v[2];  accessor[0][2] =  v[1];
			accessor[1][0] =  v[2];  accessor[1][1] =   0.0;  accessor[1][2] = -v[0];
			accessor[2][0] = -v[1];  accessor[2][1] =  v[0];  accessor[2][2] =   0.0;
		}
	template<typename T>
		void Matrix<T>::cross3x3(const kn::Vector<T,StaticStorePolicy<T,3> > v) {
			if(rowsMatrix != 3 && columnsMatrix != 3)
				throw MathException("Cross3x3 is valid only with 3x3 matrices");

			accessor[0][0] =   0.0;  accessor[0][1] = -v[2];  accessor[0][2] =  v[1];
			accessor[1][0] =  v[2];  accessor[1][1] =   0.0;  accessor[1][2] = -v[0];
			accessor[2][0] = -v[1];  accessor[2][1] =  v[0];  accessor[2][2] =   0.0;
		}



	/**
	* \brief Redefines display for a matrix
	* \param stream the output stream
	* \param m the matrix
	* \return a stream
	*/
	template<class U> std::ostream& operator<< (std::ostream& stream,
			const Matrix<U>& m){
		for(unsigned int i=0; i<m.rows(); ++i){
			for (unsigned int j=0; j<m.columns(); ++j)
				stream<<m[i][j] << " " ;
			stream<<std::endl;
		}
		return stream;
	}

	/**
	* \brief Redefines display for a std::vector< kn::Matrix >
	* \param stream the output stream
	* \param m std::vector of kn::Matrix
	* \return a stream
	*/
	template<class U> std::ostream& operator<< (std::ostream& stream,
			const std::vector< Matrix<U> >& m){
		for(unsigned int c=0; c<m.size() ;c++){
			for(unsigned int i=0; i<m.at(c).rows(); ++i){
	for (unsigned int j=0; j<m.at(c).columns(); ++j)
		stream<<m.at(c).at(i,j) << " " ;
	stream<<std::endl;
			}
			stream<<std::endl;
		}
		return stream;
	}

	/**
	* \brief Multiplies a vector with a matrix
	* \param v the vector
	* \param m the matrix
	* \return a vector
	* \throw MathException matrix or vector size is incorrect
	*/
	template<class U> Vector<U,DynamicStorePolicy<U> > operator* (const Vector<U,DynamicStorePolicy<U> >& v,
																																const Matrix<U>& m) {
		if(m.rows() != v.size())
			throw MathException("Matrix or vector size is incorrect");

		Vector<U,DynamicStorePolicy<U> > result(m.columns());
		U sum;
		for(unsigned int i=0; i<m.columns(); ++i){
			sum = U(0.0);
			for(unsigned int j=0; j<m.rows(); ++j)
				sum += m[j][i] * v[j];
			result[i] = sum;
		}
		return result;
	}

	/**
	* \brief Multiplies a scalar with a matrix
	* \param d a scalar
	* \param m the matrix
	* \return a matrix
	*/
	template<class U> Matrix<U> operator* (const U& d,const Matrix<U>& m){
		return m*d;
	}

	/*
	* Type definition
	*/

	typedef Matrix<float>  Matrixf;
	typedef Matrix<double> Matrixd;
	typedef Matrix<int>	   Matrixi;


	/*
	* End of Namespace
	*/
}


/*
* End of Anti-doublon
*/
#endif
