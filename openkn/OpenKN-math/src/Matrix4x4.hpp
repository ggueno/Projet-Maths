/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * Matrix4x4.hpp created in 09 2008.
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
#ifndef __OPENKN_MATH__MATRIX4X4_HPP__
#define __OPENKN_MATH__MATRIX4X4_HPP__

/*
 * Internal Includes
 */
#include "Matrix.hpp"

namespace kn {

  template<class T>
    class Matrix4x4 : public Matrix<T> {

      protected:

      public:

        /**
         * \brief Default constructor
         * Create a 4*4 matrix set to identity
         */
        Matrix4x4(void) : Matrix<T>(4) {
            setIdentity();
				}

        /**
         * \brief Copy constructor
         * Create a matrix by copying the input matrix
         * \param m the matrix to copy
         */
        Matrix4x4(const Matrix4x4<T>& m) : Matrix<T>(4) {
            std::copy(m.begin_, m.end_, this->begin_);
				}

        /**
         * \brief Constructor form Matrix
         * Create a matrix by copying the input matrix
         * \param m the matrix to copy
         * \throw MathException if m dimensions are differents
         */
        Matrix4x4(const Matrix<T>& m);

        /**
         * \brief Copy constructor
         * Create a matrix by copying the input matrix
         * \param m the pointer to the matrix to copy
         * \throw MathException pointer is null
         */
        Matrix4x4(const Matrix4x4<T>* m);

        /**
         * \brief Create a 4*4 matrix
         * Create a 4*4 matrix and use the value d to set the data of the matrix
         * \param d value used to set data of the matrix
         */
        Matrix4x4(const T& d)
          : Matrix<T>(4) {
            std::fill(this->begin_, this->end_, d);
          }

        /**
         * \brief create a 4*4 matrix
         * create a 4*4 matrix and set data by using the values array d
         * \param d pointer to an array of data
         * \throw MathException d is null
         */
        Matrix4x4(const T* d);

        /**
         * \brief Create a 4*4 matrix using a vector v
         * Create a matrix using the vector v. if setasrows is set to true,
         * v is used to fill rows of the matrix, v is used to fill columns otherwise
         * \param v a vector
         * \param setasrows defined if vector is used to fill columns or rows
         * \throw MathException size of vector is different of 4
         */
        Matrix4x4(const Vector<T>& v,const bool& setasrows = true);

        /**
         * \brief Create a 4*4 matrix
         * Create a matrix using the pointer on the vector v. If setasrows is set to true, v is used to fill rows of the matrix, v is used to fill columns otherwise
         * \param v a pointer on an array of vectors
         * \param setasrows defined if vector is used to fill columns or rows
         * \throw MathException v is null
         * \throw MathException if *v size are different of 4
         */
        Matrix4x4(const Vector<T,StaticStorePolicy<T,4> >* v,const bool& setasrows = true);

        /**
         * \brief Destructor
         */
        ~Matrix4x4(void) {}

      public:


        using Matrix<T>::operator*;

        /**
         * \brief Multiplies the matrix with a vector
         * \param v the vector multiplied with this matrix
         * \return a vector
         * \throw MathException vector size is incorrect
         */
        Vector<T,StaticStorePolicy<T,4> > operator*(const Vector<T,StaticStorePolicy<T,4> >& v) const;

				/**
				 * \brief Multiplies the matrix with a vector
				 * \param v the vector multiplied with this matrix
				 * \return a vector
				 * \throw MathException vector size is incorrect
				 */
				Vector<T,DynamicStorePolicy<T> > operator*(const Vector<T,DynamicStorePolicy<T> >& v) const;
				
				/**
         * \brief Returns the number of rows of the matrix
         * \return the number of rows
         */
        inline size_t rows(void) const {
          return 4;
        }

        /**
         * \brief Returns the number of columns of the matrix
         * \return the number of columns
         */
        inline size_t columns(void) const {
          return 4;
        }

        /**
         * \brief Transposes inplace the current matrix
         * \return this transposed matrix
         */
        Matrix4x4<T>& transpose(void);

        /**
         * \brief sets the matrix to identity
         */
        void setIdentity(void);

        /**
         * \brief Check if it is a square matrix or not
         * \return if the matrix is square
         */
        inline bool isSquare(void) const {return true;}

        /**
         * \brief Allocate the matrix m to this matrix
         * \param m the matrix used to defined this matrix
         * \return the matrix
         * \throw MathException matrix size is incorrect
         */
        Matrix4x4<T>& operator=(const Matrix4x4<T>& m);

        /**
         * \brief Adds two matrices
         * \param m the matrix added to this matrix
         * \return a copy of the matrix
         * \throw MathException matrix size is incorrect
         */
        Matrix4x4<T> operator+(const Matrix4x4<T>& m) const;

        /**
         * \brief Subtracts two matrices
         * \param m the matrix subtracted to this matrix
         * \return a copy of the matrix
         * \throw MathException matrix size is incorrect
         */
        Matrix4x4<T> operator-(const Matrix4x4<T>& m) const;

        /**
         * \brief Divides the matrix with a value
         * \param d the value divided with this matrix
         * \return a copy of the matrix
         * \throw MathException d is null
         */
        Matrix4x4<T> operator/(const T& d) const;

        /**
         * \brief Multiplies two matrices
         * \param m the matrix multiplied with this matrix
         * \return a copy of the matrix
         * \throw MathException matrice size is incorrect
         */
        Matrix4x4<T> operator*(const Matrix4x4<T>& m) const;

        /**
         * \brief Multiplies the matrix with a value
         * \param d the value multiplied with this matrix
         * \return a copy of the matrix
         */
        Matrix4x4<T> operator*(const T& d) const;

        /**
         * \brief Compute opposite of the matrix
         * \return a copy of the matrix
         */
        Matrix4x4<T> operator-(void) const;

        /**
         * \brief Adds the matrix with a matrix
         * \param m the matrix added with this matrix
         * \return the matrix
         * \throw MathException matrix size is incorrect
         */
        Matrix4x4<T>& operator+=(const Matrix4x4<T>& m);

        /**
         * \brief Subtracts the matrix with a matrix
         * \param m the matrix subtracted with this matrix
         * \return the matrix
         * \throw MathException matrix size is incorrect
         */
        Matrix4x4<T>& operator-=(const Matrix4x4<T>& m);

        /**
         * \brief Divides the matrix with a value
         * All values of the matrix are divided by d
         * \param d the value divided with this matrix
         * \return the matrix
         * \throw MathException d is null
         */
        Matrix4x4<T>& operator/=(const T& d);

        /**
         * \brief Multiplies the matrix with a matrix
         * \param m the matrix multiplied with this matrix
         * \return the matrix
         * \throw MathException matrix size is incorrect
         */
        Matrix4x4<T>& operator*=(const Matrix4x4<T>& m);

        /**
         * \brief Multiplies the matrix with a value
         * \param d the value multiplied with this matrix
         * \return the matrix
         */
        Matrix4x4<T>& operator*=(const T& d);

        /**
         * \brief Returns a vector with values from a specific row
         * \param row the number of the row
         * \return a vector of values
         * \throw MathException row is out of bounds
         */
        Vector<T,StaticStorePolicy<T,4> > getRow(const unsigned int& row) const;

        /**
         * \brief Returns a vector with values from a specific column
         * \param column the number of the column
         * \return a vector of values
         * \throw MathException column is out of bounds
         */
        Vector<T,StaticStorePolicy<T,4> > getColumn(const unsigned int& column) const;

        /**
         * \brief Return the diagonal of the matrix as a vector
         * \return a vector
         */
        Vector<T,StaticStorePolicy<T,4> > getDiagonal(void) const;

        /**
         * \brief Transposes a copy of the matrix
         * Creates and transposes a copy of this matrix. The current matrix is unchanged
         * \return the transposed copy of the matrix
         */
        inline Matrix4x4<T> getTranspose(void) const
        {
          return Matrix4x4<T>(*this).transpose();
        }

        /**
         * \brief Computes inplace the power p of this matrix
         * \return this matrix
         * \throw MathException not a square matrix
         */
        Matrix4x4<T>& power(const unsigned int& p);

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
    Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>* m)
    : Matrix<T>(4)
    {
      if(m==0)
        throw MathException("Pointer is null");
      std::copy(m->begin_, m->end_, this->begin_);
    }



  template<class T>
    Matrix4x4<T>::Matrix4x4(const T* a)
    : Matrix<T>(4)
    {
      if(a==0)
        throw MathException("Pointer is null");
      std::copy(a, a + 16, this->begin_);
    }


  template<class T>
    Matrix4x4<T>::Matrix4x4(const Vector<T>& v,const bool& setasrows) : Matrix<T>(4)
    {
      if(v.size()!=16)
        throw MathException("Vector size is different from Matrix size");

      if(setasrows)
        for(unsigned int i = 0; i < 16; ++i)
          (this->data)[i] = v[i];
      else
        for(unsigned int j = 0; j < 4; ++j)
          for(unsigned int i = 0; i < 4; ++i)
            (this->accessor)[i][j] = v[j*4+i];
    }


  template<class T>
    Matrix4x4<T>::Matrix4x4(const Vector<T,StaticStorePolicy<T,4> >* v,const bool& setasrows) : Matrix<T>(4)
    {

      if(v==0)
        throw MathException("Pointer is null");

      if(setasrows)
        for(unsigned int i = 0; i < 4; ++i)
          for(unsigned int j = 0; j < 4; ++j)
            (this->accessor)[i][j] = v[i][j];
      else
        for(unsigned int j = 0; j < 4; ++j)
          for(unsigned int i = 0; i < 4; ++i)
            (this->accessor)[i][j] = v[j][i];

    }


  template<class T>
    Matrix4x4<T>::Matrix4x4(const Matrix<T>& m)
    : Matrix<T>(4) {
      if ((m.rows() != 4) || (m.columns() != 4))
        throw MathException("Matrix4x4 Constructor","Matrix sizes are different");
      std::copy(m.getMatrixArray(), m.getMatrixArray()+m.rows()*m.columns(), this->begin_);
    }


  template<class T>
    Vector<T,StaticStorePolicy<T,4> > Matrix4x4<T>::operator*(const Vector<T,StaticStorePolicy<T,4> >& v) const {			
      Vector<T,StaticStorePolicy<T,4> > vtmp;
      vtmp[0] = v[0]*(this->accessor)[0][0] + v[1]*(this->accessor)[0][1] + v[2]*(this->accessor)[0][2] + v[3]*(this->accessor)[0][3];
      vtmp[1] = v[0]*(this->accessor)[1][0] + v[1]*(this->accessor)[1][1] + v[2]*(this->accessor)[1][2] + v[3]*(this->accessor)[1][3];
      vtmp[2] = v[0]*(this->accessor)[2][0] + v[1]*(this->accessor)[2][1] + v[2]*(this->accessor)[2][2] + v[3]*(this->accessor)[2][3];
      vtmp[3] = v[0]*(this->accessor)[3][0] + v[1]*(this->accessor)[3][1] + v[2]*(this->accessor)[3][2] + v[3]*(this->accessor)[3][3];
      return vtmp;
    }

  template<class T>
    Vector<T,DynamicStorePolicy<T> > Matrix4x4<T>::operator*(const Vector<T,DynamicStorePolicy<T> >& v) const {
			Vector<T,DynamicStorePolicy<T> > vtmp(4);
      vtmp[0] = v[0]*(this->accessor)[0][0] + v[1]*(this->accessor)[0][1] + v[2]*(this->accessor)[0][2] + v[3]*(this->accessor)[0][3];
      vtmp[1] = v[0]*(this->accessor)[1][0] + v[1]*(this->accessor)[1][1] + v[2]*(this->accessor)[1][2] + v[3]*(this->accessor)[1][3];
      vtmp[2] = v[0]*(this->accessor)[2][0] + v[1]*(this->accessor)[2][1] + v[2]*(this->accessor)[2][2] + v[3]*(this->accessor)[2][3];
      vtmp[3] = v[0]*(this->accessor)[3][0] + v[1]*(this->accessor)[3][1] + v[2]*(this->accessor)[3][2] + v[3]*(this->accessor)[3][3];
      return vtmp;
    }

  template<class T>
    Matrix4x4<T>& Matrix4x4<T>::transpose(void)	{

      for(unsigned int i = 0; i < 4; ++i)
        for(unsigned int j = 0; j < i; ++j)
          std::swap((this->accessor)[i][j],(this->accessor)[j][i]);

      return *this;
    }

  template<class T>
    void Matrix4x4<T>::setIdentity(void){
      this->setZero();
      (this->accessor)[0][0] = (this->accessor)[1][1] = (this->accessor)[2][2] = (this->accessor)[3][3] = T(1.0);
    }




  /**
   * \brief Multiplies a vector with a matrix
	 * \param v the vector (static storage)
   * \param m the matrix
   * \return a matrix
   * \throw MathException matrix size is incorrect
   */
  template<class U>
    Vector<U,StaticStorePolicy<U,4> > operator* (const Vector<U,StaticStorePolicy<U,4> >& v,const Matrix4x4<U>& m) {
      Vector<U,StaticStorePolicy<U,4> > result;
      result[0] = m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2] + m[3][0]*v[3];
      result[1] = m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2] + m[3][1]*v[3];
      result[2] = m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2] + m[3][2]*v[3];
      result[3] = m[0][3]*v[0] + m[1][3]*v[1] + m[2][3]*v[2] + m[3][3]*v[3];
      return result;
    }

  /**
   * \brief Multiplies a vector with a matrix
   * \param v the vector (dynamic storage)
   * \param m the matrix
   * \return a matrix
   * \throw MathException matrix size is incorrect
   */
  template<class U>
    Vector<U,DynamicStorePolicy<U> > operator* (const Vector<U,DynamicStorePolicy<U> >& v,const Matrix4x4<U>& m) {
			Vector<U,DynamicStorePolicy<U> > result(4);
      result[0] = m[0][0]*v[0] + m[1][0]*v[1] + m[2][0]*v[2] + m[3][0]*v[3];
      result[1] = m[0][1]*v[0] + m[1][1]*v[1] + m[2][1]*v[2] + m[3][1]*v[3];
      result[2] = m[0][2]*v[0] + m[1][2]*v[1] + m[2][2]*v[2] + m[3][2]*v[3];
      result[3] = m[0][3]*v[0] + m[1][3]*v[1] + m[2][3]*v[2] + m[3][3]*v[3];
      return result;
    }


  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4<T>& m){
      if(&m == this) return *this;

      std::copy(m.begin_,m.end_,this->begin_);

      return *this;
    }


  template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& m) const{
      Matrix4x4<T> result = *this;
      result += m;
      return result;
    }


  template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& m) const{
      Matrix4x4<T> result = *this;
      result -= m;
      return result;
    }


  template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator/(const T& d) const{
      Matrix4x4<T> result = *this;
      result /= d;
      return result;
    }


  template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& m) const{

      Matrix4x4<T> result;
      T sum;
      for(unsigned int i = 0; i < 4; ++i)
        for(unsigned int j = 0; j < 4; ++j){
          sum = T(0.0);

          for(unsigned int k = 0; k < 4; ++k){
            sum += (*this)[i][k]*m[k][j];
          }
          result[i][j] = sum;
        }

      return result;
    }

  template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator*(const T& d) const{
      Matrix4x4<T> result = *this;
      result *= d;
      return result;
    }


  template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator-(void) const{
      Matrix4x4<T> result = *this;
      std::transform(this->begin_, this->end_, result.begin_, std::negate<T>());
      return result;
    }


  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T>& m){
      std::transform(this->begin_, this->end_, m.begin_, this->begin_, std::plus<T>());
      return *this;
    }


  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T>& m){
      std::transform(this->begin_, this->end_, m.begin_, this->begin_, std::minus<T>());
      return *this;
    }

  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator/=(const T& d){
      if(d==0)
        throw MathException("Value is null");
      std::transform(this->begin_, this->end_, this->begin_, std::bind2nd(std::divides<T>(),d));
      return *this;
    }


  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& m){
      Matrix4x4<T> tmp = *this;
      T sum;
      for(unsigned int i = 0; i < 4; ++i)
        for(unsigned int j = 0; j < 4; ++j){
          sum = T(0.0);

          for(unsigned int k = 0; k < 4; ++k){
            sum += tmp[i][k]*m[k][j];
          }
          this->accessor[i][j] = sum;
        }
      return *this;
    }

  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator*=(const T& d){
      std::transform(this->begin_, this->end_, this->begin_, std::bind2nd(std::multiplies<T>(),d));
      return *this;
    }


  template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::power(const unsigned int& p){
      if(p == 0){
        setIdentity();
        return *this;
      }
      Matrix4x4<T> tmp(*this);

      for(unsigned int i=1; i < p; ++i)
        *this *= tmp;

      return *this;
    }

  template<typename T>
    Vector<T,StaticStorePolicy<T,4> > Matrix4x4<T>::getDiagonal(void) const{
      Vector<T,StaticStorePolicy<T,4> > v;
      for(unsigned int i = 0; i < 4; ++i)
        v[i] = this->accessor[i][i];
      return v;
    }

  template<typename T>
    Vector<T,StaticStorePolicy<T,4> > Matrix4x4<T>::getRow(const unsigned int& row) const{
      if(row >= this->rowsMatrix)
        throw MathException("Out of bounds");
      Vector<T,StaticStorePolicy<T,4> > v;
      for(unsigned int i = 0; i < this->columnsMatrix; ++i)
        v[i] = this->accessor[row][i];
      return v;
    }

  template<typename T>
    Vector<T,StaticStorePolicy<T,4> > Matrix4x4<T>::getColumn(const unsigned int& column) const{
      if(column >= this->columnsMatrix)
        throw MathException("Out of bounds");
      Vector<T,StaticStorePolicy<T,4> > v;
      for(unsigned int i = 0; i < this->columnsMatrix; ++i)
        v[i] = this->accessor[i][column];
      return v;
    }

  /**
   * \brief Trace of the Matrix
   *
   * This represents the sum of each element on the diagonal
   *
   * \return the trace
   */
  template<typename T>
    T Matrix4x4<T>::trace(void) const{
      return (this->accessor[0][0] + this->accessor[1][1] + this->accessor[2][2] + this->accessor[3][3]);
    }


  /**
   * \brief Multiplies a scalar with a matrix4x4
   * \param d a scalar
   * \param m the matrix4x4
   * \return a matrix4x4
   */
  template<class U> Matrix4x4<U> operator* (const U& d,
      const Matrix4x4<U>& m){
    return m*d;
  }

  /**
   * \brief Redefines display for a std::vector< kn::Matrix4x4 >
   * \param stream the output stream
   * \param m std::vector of kn::Matrix4x4
   * \return a stream
   */
  template<class U> std::ostream& operator<< (std::ostream& stream,const std::vector< Matrix4x4<U> >& m){
		for(unsigned int c=0; c<m.size() ;c++){
			for(unsigned int i=0; i<4; ++i){
				for (unsigned int j=0; j<4; ++j)
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

  typedef Matrix4x4<float>  Matrix4x4f;
  typedef Matrix4x4<double> Matrix4x4d;
  typedef Matrix4x4<int>    Matrix4x4i;

}


#endif
