/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HATreeInfos.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HA_TREE_INFOS_HPP__
#define __OPENKN_GRAPH__HA_TREE_INFOS_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */

#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

/*
 * Internal Includes
 */
#include "GraphException.hpp"
#include "GraphStruct.hpp"
#include "Graph.hpp"

/*
 * Namespace
 */
namespace kn{
	
		
		/*
		 * Class definition
		 */

		/** \brief common interface for both rooted and unrooted tree informations, usefull for homeomorphic alignment
		
		 */
		template<typename V, typename E>
		class HATreeInfos{
		
		protected :
			/** \brief stockage of paths weights
			*/
			std::vector<E> weights;
			
			std::vector<unsigned int> distances;
			
			/*
			 * Constructor & destructors
			 */
		public:
			virtual ~HATreeInfos(){}
			

		public : 
			
			inline E pathWeight(unsigned int start, unsigned int end){
				return weights[start*size()+end];
			}
			inline unsigned int pathSize(unsigned int start, unsigned int end){
				return distances[start*size()+end];
			}
			
			
			
			virtual std::vector<std::pair<unsigned int,unsigned int> >& navigationOrder()=0;
			
			virtual std::vector<unsigned int> ancestors(unsigned int vertex, unsigned int root)=0;
			
			virtual unsigned int parent(unsigned int vertex, unsigned int root)=0;
			
			virtual std::vector<unsigned int> children(unsigned int vertex, unsigned int root)=0;
			
			virtual std::vector<unsigned int> children(unsigned int vertex)=0;
		
			virtual unsigned int size()=0;
			
			virtual unsigned int height()=0;
			
			virtual unsigned int degree()=0;
			
			virtual bool isRooted()=0;
			
			virtual std::vector<unsigned int> possibleRoots()=0;
		};



		
		
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
