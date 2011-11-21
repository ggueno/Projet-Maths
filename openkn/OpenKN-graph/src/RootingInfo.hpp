/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * RootingInfo.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__ROOTING_INFO_HPP__
#define __OPENKN_GRAPH__ROOTING_INFO_HPP__

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

		/** \brief rooting informations for any acyclic graph
		
		 */
		class RootingInfo{
		
		private:
			GraphStruct* graph;
			std::vector<unsigned int> parents;
			/*
			 * Constructor & destructors
			 */
		public:
			RootingInfo(const GraphStruct* model, bool checking=true);
			
			~RootingInfo();

		
		public : 
			std::vector<unsigned int> children(unsigned int vertex, unsigned int root);
			
			unsigned int parent(unsigned int vertex, unsigned int root);
			
			std::vector<unsigned int> ancestors(unsigned int vertex, unsigned int root);
			
			unsigned int height(unsigned int vertex, unsigned int root);
			
			unsigned int height(unsigned int root);
			
			unsigned int childrenDegree(unsigned int vertex, unsigned int root);
			
			unsigned int maxChildrenDegree();
			
		};



		
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
