/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * VectorStorage.hpp created in 09 2008.
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
#ifndef __OPENKN_MATH__VECTOR_STATIC_STORAGE_POLICY_HPP__
#define __OPENKN_MATH__VECTOR_STATIC_STORAGE_POLICY_HPP__

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


/*
 * Namespace
 */
namespace kn {

	/**
		* \brief Static storage policy for Vector allocation
		*/
	template<class T,size_t SizeAtCompileTime>
		class StaticStorePolicy {
		private:
			T array[SizeAtCompileTime];
			static const size_t v_size = SizeAtCompileTime;
		public:
			/**
			 * \brief Constructor (implicit allocation)
			 */
			inline StaticStorePolicy() {}
			/**
			 * \brief Constructor (explicit allocation)
			 * \warning Should not be called
			 * \param t The size of the fixed size vector
			 * \throw MathException if called vector size differs from t
			 */
			inline StaticStorePolicy(size_t t) {
				if (t != SizeAtCompileTime) {
					throw MathException("Explicit allocation on a fixed size vector with an incompatible size");
				}
			}
			/*
			 * \brief Copy Constructor
			 * \warning Should not be called
			 * \param t The size of the fixed size vector
			 * \throw MathException if called vector size differs from t
			 */
			/*
			inline StaticStorePolicy(DynamicStorePolicy dyn_pol) {
				if (dyn_pol )
				if (t != SizeAtCompileTime) {
					throw MathException("Explicit allocation on a fixed size vector with an incompatible size");
				}
			}
			*/

			/// Destructor
			inline ~StaticStorePolicy() {}

			/**
			 * \brief Get size
			 */
			inline const size_t size(void) const{return v_size;}
			
			/**
			 * \brief Resize
			 * \warning Should not be called
			 * \throw MathException It is illegal to resize a fixed size vector
			 */
			inline void resize(size_t new_size) {
				if (new_size != v_size)
					throw MathException("Resizement of a fixed size vector is not allowed (isn't it obvious ?)");
			}

			inline const T *data() const { return array; }
			inline T *data() { return array; }
			inline const T* begin() const { return array; }
			inline const T* end() const { return array + v_size; }

	};

}

/*
 * End of Anti-doublon
 */
#endif
