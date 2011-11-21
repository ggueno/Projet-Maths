/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * SparseGraphStruct.hpp created in 10 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_GRAPH__SPARSEGRAPHSTRUCT_HPP__
#define __OPENKN_GRAPH__SPARSEGRAPHSTRUCT_HPP__


/*
 * External Includes
 */
#include <vector>
#include <utility>

/*
 * Internal Includes
 */

#include "GraphStruct.hpp"
/*
 * Namespace
 */
namespace kn{
		/*
		 * Class definition
		 */
	
		/** \brief Interface for graph structure
		 *
		 */
		class SparseGraphStruct : public GraphStruct{ 
		private:
			int beginEdgeIndex()const;
			
			int nextEdgeIndex(int cur)const;
			
			std::pair<unsigned int, unsigned int> getEdge(int index, unsigned int lastIn)const;
			
			template<class InputIterator>
			void buildGraph(unsigned int size,InputIterator edges_start, InputIterator edges_stop, bool directed);
			
		private:
			std::vector<unsigned int> firstSuccessor;
			std::vector<unsigned int> successorsList;			
			
			
		public:
			/** \brief Virtual destructor
			 *
			 */
			~SparseGraphStruct();

			SparseGraphStruct(const GraphStruct* model);
			
			SparseGraphStruct(const GraphStruct& model);
			
			SparseGraphStruct(unsigned int size, const std::vector<std::pair<unsigned int, unsigned int> >& edges, bool directed);

			SparseGraphStruct* clone()const;
		public :
		
			std::vector<unsigned int> neighbours(unsigned int vertex) const;
			
			std::vector<unsigned int> successors(unsigned int vertex) const;
			
			std::vector<unsigned int> predecessors(unsigned int vertex) const;
			
			unsigned int degree(unsigned int vertex) const;
			
			unsigned int innerDegree(unsigned int vertex) const;
			
			unsigned int outerDegree(unsigned int vertex)const;
			
			bool areLinked(unsigned int vertexA, unsigned int vertexB) const;
			
			bool contains(unsigned int vertex) const;
			
			inline bool isMutable()const{return false;}
			
		};
		/*
		 * End of Namespace
		 */
}

/*
 * End of Anti-doublon
 */
#endif

