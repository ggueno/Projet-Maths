/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MutableDirectedGraph.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__MUTABLE_DIRECTED_GRAPH_HPP__
#define __OPENKN_GRAPH__MUTABLE_DIRECTED_GRAPH_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */

#include <map>
#include <vector>
#include <algorithm>

/*
 * Internal Includes
 */
#include "GraphException.hpp"
#include "GraphStruct.hpp"
#include "Graph.hpp"
#include "MutableGraph.hpp"

/*
 * Namespace
 */
namespace kn{
	
		
		/*
		 * Class definition
		 */

		/** \brief abstract class for graphs
		
		 */
		template<typename V, typename E>
		class MutableDirectedGraph : public MutableGraph<V,E>{
			/*
			 * Constructor & destructors
			 */
		public:
			MutableDirectedGraph();
		
			MutableDirectedGraph(const Graph<V,E>& model);
			
			MutableDirectedGraph(const Graph<V,E>* model);
			
			MutableDirectedGraph(unsigned int size,const std::vector<std::pair<unsigned int, unsigned int> >& edges);
			
			MutableDirectedGraph(unsigned int size, const std::vector< V >& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas);
			
			~MutableDirectedGraph();


		public : 
			
			std::vector<unsigned int> successors(unsigned int vertex)const;
			
			std::vector<unsigned int> predecessors(unsigned int vertex)const;
			
			bool accessTo(unsigned int vertexA, unsigned int vertexB)const;
			
			 
			
		};

		/*
		 * Templates definitions
		 */
		
		
		template<typename V, typename E>
		MutableDirectedGraph<V,E>::MutableDirectedGraph():MutableGraph<V,E>(true){
		}
		
		template<typename V, typename E>
		MutableDirectedGraph<V,E>::MutableDirectedGraph(const Graph<V,E>& model):MutableGraph<V,E>(model){
			if(!model.isDirected())throw GraphException("The graph need to be directed", "MutableDirectedGraph<V,E>::MutableDirectedGraph(const Graph<V,E>& model)");
		}
		
		template<typename V, typename E>
		MutableDirectedGraph<V,E>::MutableDirectedGraph(const Graph<V,E>* model):MutableGraph<V,E>(model){
			if(!model->isDirected())throw GraphException("The graph need to be directed", "MutableDirectedGraph<V,E>::MutableDirectedGraph(const Graph<V,E>* model)");
		}
			
		template<typename V, typename E>
		MutableDirectedGraph<V,E>::MutableDirectedGraph(unsigned int size,
						  const std::vector<std::pair<unsigned int, unsigned int> >& edges):MutableGraph<V,E>(size, edges, true){
		}
			
		template<typename V, typename E>
		MutableDirectedGraph<V,E>::MutableDirectedGraph(unsigned int size, const std::vector<V>& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector<E>& edgesDatas):MutableGraph<V,E>(size, verticesDatas, edges, edgesDatas, true){
			
		}
			
		template<typename V, typename E>
		MutableDirectedGraph<V,E>::~MutableDirectedGraph(){
			
		}
		
		template<typename V, typename E>
		std::vector<unsigned int> MutableDirectedGraph<V,E>::successors(unsigned int vertex)const{
			return this->graphStruct->successors(vertex);
		}
		
		template<typename V, typename E>
		std::vector<unsigned int> MutableDirectedGraph<V,E>::predecessors(unsigned int vertex)const{
			return this->graphStruct->predecessors(vertex);
		}
		
		template<typename V, typename E>
		bool MutableDirectedGraph<V,E>::accessTo(unsigned int vertexA, unsigned int vertexB)const{
			return this->graphStruct->areLinked(vertexA, vertexB);
		}


		/*
		 * Functions definitions
		 */
		

		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
