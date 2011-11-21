/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Subset.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-graph.
 *
 * The OpenKraken-graph is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-graph is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_GRAPH__Subset_HPP__
#define __OPENKN_GRAPH__Subset_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */

#include <vector>

/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{
	
		
		/*
		 * Class definition
		 */

		/** \brief 
		
		 */
		class Subset{
		
		private :
		
			unsigned int maxStored;
			std::vector<std::vector<unsigned char> > subsets;
			
		
			
			/*
			 * Constructor & destructors
			 */
		public :
			Subset(unsigned int maxStored);
			
			~Subset();
			 
			
		public : 
			
			const std::vector<unsigned char> getSubset(unsigned int index);
			
			bool isSubset(unsigned int subset, unsigned int set);
			
			unsigned int nextSubsetIndex(unsigned int subset, unsigned int set);
			
			unsigned int complement(unsigned int subset, unsigned int set);
			
			unsigned int set(unsigned char size);
			
			unsigned int setWithoutParia(unsigned int set, unsigned char paria);
			
			char getNextElement(char element, unsigned int set);
			
		};


	
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
