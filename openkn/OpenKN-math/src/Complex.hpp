/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Vector.hpp created in 09 2008.
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
#ifndef __OPENKN_MATH__COMPLEX_HPP__
#define __OPENKN_MATH__COMPLEX_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <cmath>


/*
 * Internal Includes
 */
#include "MathException.hpp"


/*
 * Namespace
 */
namespace kn{

  /*
   * Class definition
   */

  /**
   * \brief Generic complex number class (genereic for type)
   */
  template<class T> class Complex {

		public :

			/*
			* class variables
			*/

			/**
				* \brief Real part of the complex number
				*/
			T re;

			/**
				* \brief Imaginary part of the complex number
				*/
			T im;



			/*
			 * Constructors & destructor
			 */
			/**
				* \brief Constructor taking both real and imaginary parts
				* \param part_re Real part of the complex
				* \param part_im Imaginary part of the complex
				*/
			Complex(const T &part_re = T(0.0), const T &part_im = T(0.0));

			/**
				* \brief Copy constructor
				* \param c The complex to copy from
				*/
			Complex(const Complex<T> &c);

			/**
				* \brief Destructor
				*/
			~Complex(void);



			/*
			 * Affectation operator redefinition
			 */
			/**
				* \brief Changes the current real and imaginary parts values with those of the given other complex
				* \param c The other complex to set the current instance with
				* \return The current instance
				*/
			Complex<T> &operator=(const Complex<T> &c);


			/*
				* Comparison operators redefinition
				*/

			/**
				* \brief Tests if the current complex number is equal to the given another complex number
				* \param c The other complex to be compared
				* \return True if the complex numbers are equals, false otherwise
				*/
			bool operator==(const Complex<T> &c) const;

			/**
				* \brief Tests if the current complex number is different to the given another complex number
				* \param c The other complex to be compared
				* \return True if the complex numbers are different, false otherwise
				*/
			bool operator!=(const Complex<T> &c) const;



			/*
				* Mathematical operators redefinition
				*/

			/**
				* \brief Adds two complexes
				* \param c The complex to be added to the current instance
				* \return The result of the operation
				*/
			Complex<T> operator+(const Complex<T> &c) const;

			/**
				* \brief Substracts two complexes
				* \param c The complex to be substracted to the current instance
				* \return The result of the operation
				*/
			Complex<T> operator-(const Complex<T> &c) const;

			/**
				* \brief Multiplies two complexes
				* \param c The complex to be multiplied to the current instance
				* \return The result of the operation
				*/
			Complex<T> operator*(const Complex<T> &c) const;

			/**
				* \brief Divides two complexes
				* \param c The complex to divide the current instance by
				* \return The result of the operation
				*/
			Complex<T> operator/(const Complex<T> &c) const;



			/*
				* Self-modifying operators redefinition
				*/

			/**
				* \brief Adds two complexes, then overwrite the current instance with the result of the operation
				* \param c The complex to be added to the current instance
				* \return A copy of the current instance
				*/
			Complex<T> &operator+=(const Complex<T> &c);

			/**
				* \brief Substracts two complexes, then overwrite the current instance with the result of the operation
				* \param c The complex to be substracted to the current instance
				* \return A copy of the current instance
				*/
			Complex<T> &operator-=(const Complex<T> &c);

			/**
				* \brief Multiplies two complexes, then overwrite the current instance with the result of the operation
				* \param c The complex to be multiplied to the current instance
				* \return A copy of the current instance
				*/
			Complex<T> &operator*=(const Complex<T> &c);

			/**
				* \brief Divides two complexes, then overwrite the current instance with the result of the operation
				* \param c The complex to divide the current instance by
				* \return A copy of the current instance
				*/
			Complex<T> &operator/=(const Complex<T> &c);



			/*
				* Mathematical functions
				*/

			/**
				* \brief Computes the module of the complex
				* \returns The module of the complex
				*/
			T module() const;

			/**
				* \brief Computes the conjugate of the complex
				* \return The conjugate of the complex
				*/
			Complex<T> conjugate() const;
	};



	/*
	 * Constructors & destructor
	 */
	
	template<class T> Complex<T>::Complex(const T &part_re, const T &part_im):re(part_re), im(part_im){
	}
	
	template<class T> Complex<T>::Complex(const Complex<T> &c):re(c.re), im(c.im){
	}
	
	template<class T> Complex<T>::~Complex(){}
	
	
	
	/*
	 * Affectation operator redefinition
	 */
	template<class T> Complex<T> &Complex<T>::operator=(const Complex<T> &c){
		this->re = c.re;
		this->im = c.im;
		return *this;
	}

	/*
	 * Comparison operators redefinition
	 */
	template<class T> bool Complex<T>::operator==(const Complex<T> &c) const{
		return this->re == c.re
		    && this->im == c.im;
	}
	
	template<class T> bool Complex<T>::operator!=(const Complex<T> &c) const{
		return this->re != c.re
		    || this->im != c.im;
	}
	
	
	
	/*
	 * Mathematical operators redefinition
	 */
	template<class T> Complex<T> Complex<T>::operator+(const Complex<T> &c) const{
		return Complex<T>(this->re+c.re,
		                  this->re+c.re);
	}
	
	template<class T> Complex<T> Complex<T>::operator-(const Complex<T> &c) const{
		return Complex<T>(this->re-c.re,
		                  this->im-c.im);
	}
	
	template<class T> Complex<T> Complex<T>::operator*(const Complex<T> &c) const{
		return Complex<T>(this->re*c.re - this->im*c.im,
		                  this->re*c.im + this->im*c.re);
	}
	
	template<class T> Complex<T> Complex<T>::operator/(const Complex<T> &c) const{
		return (*this) * Complex<T>(c.re/(pow(c.re, 2.0f)+pow(c.im, 2.0f)),
		                           -c.im/(pow(c.re, 2.0f)+pow(c.im, 2.0f)));
	}

	/*
	 * Self-modifying operators redefinition
	 */
	template<class T> Complex<T> &Complex<T>::operator+=(const Complex<T> &c){
		this->re = this->re+c.re;
		this->im = this->im+c.im;
		return *this;
	}
	
	template<class T> Complex<T> &Complex<T>::operator-=(const Complex<T> &c){
		this->re = this->re-c.re;
		this->im = this->im-c.im;
		return *this;
	}
	
	template<class T> Complex<T> &Complex<T>::operator*=(const Complex<T> &c){
		this->re = this->re*c.re - this->im*c.im;
		this->im = this->re*c.im + this->im*c.re;
		return *this;
	}
	
	template<class T> Complex<T> &Complex<T>::operator/=(const Complex<T> &c){
		this->re = c.re/(pow(c.re, 2.0f)+pow(c.im, 2.0f));
		this->im = -c.im/(pow(c.re, 2.0f)+pow(c.im, 2.0f));
		return *this;
	}
	
	/*
	 * Mathematical functions
	 */
	template<class T> T Complex<T>::module() const{
		return sqrt(pow(this->re, 2.0f)+pow(this->im, 2.0f));
	}
	
	template<class T> Complex<T> Complex<T>::conjugate() const{
		return Complex<T>(this->re, -this->im);
	}
	
	
	
	/*
	 * End of namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif

