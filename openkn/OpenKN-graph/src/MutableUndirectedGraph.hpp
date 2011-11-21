/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MutableUndirectedGraph.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__MUTABLE_UNDIRECTED_GRAPH_HPP__
#define __OPENKN_GRAPH__MUTABLE_UNDIRECTED_GRAPH_HPP__

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
		class MutableUndirectedGraph : public MutableGraph<V,E>{
			/*
			 * Constructor & destructors
			 */
		public:
			MutableUndirectedGraph();
		
			MutableUndirectedGraph(const Graph<V,E>& model);
			
			MutableUndirectedGraph(const Graph<V,E>* model);
			
			MutableUndirectedGraph(unsigned int size,const std::vector<std::pair<unsigned int, unsigned int> >& edges);
			
			MutableUndirectedGraph(unsigned int size, const std::vector< V >& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas);
			
			~MutableUndirectedGraph();


		public : 
			
			std::vector<unsigned int> neighbours(unsigned int vertex)const;
			
			bool areLinked(unsigned int vertexA, unsigned int vertexB)const;
			
			
			 
			
		};

		/*
		 * Templates definitions
		 */
		
		
		template<typename V, typename E>
		MutableUndirectedGraph<V,E>::MutableUndirectedGraph():MutableGraph<V,E>(true){
		}
		
		template<typename V, typename E>
		MutableUndirectedGraph<V,E>::MutableUndirectedGraph(const Graph<V,E>& model):MutableGraph<V,E>(model){
			if(model.isDirected())throw GraphException("The graph need to be Undirected", "MutableUndirectedGraph<V,E>::MutableUndirectedGraph(const Graph<V,E>& model)");
		}
		
		template<typename V, typename E>
		MutableUndirectedGraph<V,E>::MutableUndirectedGraph(const Graph<V,E>* model):MutableGraph<V,E>(model){
			if(model->isDirected())throw GraphException("The graph need to be Undirected", "MutableUndirectedGraph<V,E>::MutableUndirectedGraph(const Graph<V,E>* model)");
		}
			
		template<typename V, typename E>
		MutableUndirectedGraph<V,E>::MutableUndirectedGraph(unsigned int size,
			const std::vector<std::pair<unsigned int, unsigned int> >& edges):MutableGraph<V,E>(size, edges, true){
		}
			
		template<typename V, typename E>
		MutableUndirectedGraph<V,E>::MutableUndirectedGraph(unsigned int size, const std::vector<V>& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, 
			const std::vector<E>& edgesDatas):MutableGraph<V,E>(size, verticesDatas, edges, edgesDatas, true){
			
		}
			
		template<typename V, typename E>
		MutableUndirectedGraph<V,E>::~MutableUndirectedGraph(){
			
		}
		
		template<typename V, typename E>
		std::vector<unsigned int> MutableUndirectedGraph<V,E>::neighbours(unsigned int vertex)const{
			return this->graphStruct->neighbours(vertex);
		}
		
		
		template<typename V, typename E>
		bool MutableUndirectedGraph<V,E>::areLinked(unsigned int vertexA, unsigned int vertexB)const{
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
