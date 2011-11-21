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
#ifndef __OPENKN_MATH__VECTOR_DYNAMIC_STORAGE_POLICY_HPP__
#define __OPENKN_MATH__VECTOR_DYNAMIC_STORAGE_POLICY_HPP__

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
	template<class T>
		class DynamicStorePolicy {
			protected:
				T* array;
				size_t v_size;
			public:
				/**
				* \brief Construction (no allocation)
				*/
				inline DynamicStorePolicy() : v_size(0), array(0) {}
				/**
				* \brief Construction avec allocation explicite
				* \param s The size of the created vector
				*/
				inline DynamicStorePolicy(size_t s) : array(new T[s]),v_size(s) {}

				/// Destructor
				inline ~DynamicStorePolicy() {if((v_size != 0) && (array != 0)) {delete[](array);}v_size=0;}

				/**
				* \brief Get size
				*/
				inline const size_t size(void) const {return v_size;}
				/**
				* \brief Resize
				*/
				inline void resize(size_t new_size) {
					if(v_size != new_size) {
						if (array) delete[](array);
						array = new T[new_size];
						v_size = new_size;
					}
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
