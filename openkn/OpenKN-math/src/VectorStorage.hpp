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
#ifndef __OPENKN_MATH__VECTOR_STORAGE_HPP__
#define __OPENKN_MATH__VECTOR_STORAGE_HPP__

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
namespace kn{
	// Pour explication de cette valeur voir dans eigen fichier Core/utils/Constant.h
	const int Dynamic = 10000;

	// STRUCTURE ALLOWING TO STORE DATA IN FIXED SIZE
	// => TODO : The same thing to align data (for SSE instructions)
	template <typename T, size_t Size> struct kn_vector_array
	{
		T array[Size];
		kn_vector_array() {}
	};


	/** \internal
		*
		* \class kn_vector_storage
		*
		* \brief Stores the data of a vector
		*
		* This class stores the data of fixed-size, dynamic-size or mixed vector
		* in a way as compact as possible.
		*
		* \sa Vector
		*/
	template<typename T, size_t Size> class kn_vector_storage;

	// purely fixed-size vector
	template<typename T, size_t Size> class kn_vector_storage
	{
			kn_vector_array<T,Size> v_data;
		public:
			inline kn_vector_storage() {}		// Allocation vide
			inline kn_vector_storage(size_t) {}		// Allocation explicite
// 			inline kn_vector_storage(int,int,int) {}	// Au cas où on crée un vecteur sans allouer...
			inline ~kn_vector_storage() {}
			inline void swap(kn_vector_storage& other) { std::swap(v_data,other.v_data); }
			inline static size_t size(void) {return Size;}
			inline void resize(size_t) {}	// Au cas où on resize un vecteur fixe ??? => Non permi a priori
			inline const T *data() const { return v_data.array; }
			inline T *data() { return v_data.array; }
			inline const T* begin() const { return v_data.array; }
			inline const T* end() const { return v_data.array + Size; }
	};

	// purely dynamic-size vector
	template<typename T> class kn_vector_storage<T,Dynamic>
	{
			T* v_data;
			size_t v_size;
		public:
			inline kn_vector_storage() : v_data(0), v_size(0) {}		// Allocation vide...
			inline kn_vector_storage(size_t size) : v_data(new T[size]), v_size(size) {}		// Avec allocation des données...
// 			inline kn_vector_storage(int,int,int) {}	// Au cas où on crée un vecteur sans allouer...
			inline ~kn_vector_storage() {if((v_size != 0) && (v_data != 0)) {delete[](v_data);}v_size=0;}
			inline void swap(kn_vector_storage& other) {
				std::swap(v_data,other.v_data); std::swap(v_size,other.v_size);
			}
			inline size_t size(void) const {return v_size;}
			inline void resize(size_t size) {
				if(size != v_size) {
					delete[](v_data);
					v_data = new T[size];
					v_size = size;
				}
			}	// Au cas où on resize
			inline const T *data() const { return v_data; }
			inline T *data() { return v_data; }
			inline const T* begin() const { return v_data; }
			inline const T* end() const { return v_data + v_size; }
	};

}

/*
 * End of Anti-doublon
 */
#endif
