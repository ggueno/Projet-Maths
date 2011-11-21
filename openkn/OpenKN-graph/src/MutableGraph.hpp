/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MutableGraph.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__MUTABLE_GRAPH_HPP__
#define __OPENKN_GRAPH__MUTABLE_GRAPH_HPP__

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
#include "MutableGraphStruct.hpp"

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
		class MutableGraph : public Graph<V,E>{
		private:
			MutableGraphStruct* mutableGraphStruct;
		
			/*
			 * Constructor & destructors
			 */
		public:
			MutableGraph();
			
			MutableGraph(bool directed);
			
			MutableGraph(const Graph<V,E>& model);
			
			MutableGraph(const Graph<V,E>* model);
			
			MutableGraph(unsigned int size,const std::vector<std::pair<unsigned int, unsigned int> >& edges, bool directed);
			
			MutableGraph(unsigned int size, const std::vector< V >& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas, bool directed);
			
			~MutableGraph();


		public : 
			
			unsigned int addVertex();
			unsigned int addVertex(V& data);
			void removeVertex(unsigned int vertex, bool recompact=false);
			void addEdge(unsigned int vertexA, unsigned int vertexB);
			void addEdge(unsigned int vertexA, unsigned int vertexB, E& data);
			void removeEdge(unsigned int vertexA, unsigned int vertexB);
			void compact();
		};

		/*
		 * Templates definitions
		 */
		 template<typename V, typename E>
		MutableGraph<V,E>::MutableGraph(){
			this->graphStruct = this->mutableGraphStruct = new MutableGraphStruct();
		}
		
		 
		template<typename V, typename E>
		MutableGraph<V,E>::MutableGraph(bool directed){
			this->graphStruct = this->mutableGraphStruct = new MutableGraphStruct(directed);
		}
		
		template<typename V, typename E>
		MutableGraph<V,E>::MutableGraph(const Graph<V,E>& model):Graph<V,E>(model, MUTABLE){
			this->mutableGraphStruct = (MutableGraphStruct*)(this->graphStruct);
		}
			
		template<typename V, typename E>
		MutableGraph<V,E>::MutableGraph(const Graph<V,E>* model):Graph<V,E>(model, MUTABLE){
			this->mutableGraphStruct = (MutableGraphStruct*)(this->graphStruct);
		}
			
		template<typename V, typename E>
		MutableGraph<V,E>::MutableGraph(unsigned int size,
						  const std::vector<std::pair<unsigned int, unsigned int> >& edges, 
						  bool directed):Graph<V,E>(size,edges, MUTABLE,directed){
			this->mutableGraphStruct = (MutableGraphStruct*)(this->graphStruct);
		}
			
		template<typename V, typename E>
		MutableGraph<V,E>::MutableGraph(unsigned int size, const std::vector<V>& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector<E>& edgesDatas,
			bool directed):Graph<V,E>(size,verticesDatas,edges,edgesDatas,MUTABLE,directed){
			this->mutableGraphStruct = (MutableGraphStruct*)(this->graphStruct);
		}
			
		template<typename V, typename E>
		MutableGraph<V,E>::~MutableGraph(){
			
		}
		
		template<typename V, typename E>
		unsigned int MutableGraph<V,E>::addVertex(){
			unsigned int key = mutableGraphStruct->addVertex();
			this->verticesDatas.resize(key+1);
			return key;
		}
		
		template<typename V, typename E>
		unsigned int MutableGraph<V,E>::addVertex(V& data){
			unsigned int key = mutableGraphStruct->addVertex();
			this->vertexDataExistence.resize(key+1);
			this->vertexDataExistence[key] = true;
			this->verticesDatas.resize(key+1);
			this->verticesDatas[key] = data;
			return key;
		}
		
		template<typename V, typename E>
		void MutableGraph<V,E>::removeVertex(unsigned int vertex, bool recompact){
			mutableGraphStruct->removeVertex(vertex, false);
			if(recompact)compact();
		}
			
		template<typename V, typename E>
		void MutableGraph<V,E>::addEdge(unsigned int vertexA, unsigned int vertexB){
			mutableGraphStruct->addEdge(vertexA, vertexB);
		}
		
		template<typename V, typename E>
		void MutableGraph<V,E>::addEdge(unsigned int vertexA, unsigned int vertexB, E& data){
			mutableGraphStruct->addEdge(vertexA, vertexB);
			this->edgesDatas[std::make_pair(vertexA, vertexB)] = data;
		}
		
		template<typename V, typename E>
		void MutableGraph<V,E>::removeEdge(unsigned int vertexA, unsigned int vertexB){
			mutableGraphStruct->removeEdge(vertexA, vertexB);
		}
			
		template<typename V, typename E>
		void MutableGraph<V,E>::compact(){
			if(mutableGraphStruct->isCompact())return;
			std::map<unsigned int, unsigned int> d = mutableGraphStruct->compact();
			typename std::map<std::pair<unsigned int, unsigned int>, E> newEdgesDatas;
			typename std::map<std::pair<unsigned int, unsigned int>, E>::const_iterator eit = this->edgesDatas.begin(), eend = this->edgesDatas.end();
			while(eit!=eend){
				unsigned int a = eit->first.first;
				unsigned int b = eit->first.second;
				newEdgesDatas[std::make_pair(a-d[a], b-d[b])] = eit->second;
				eit++;
			}
			this->edgesDatas = newEdgesDatas;
			for(unsigned int i = 0; i < this->verticesDatas.size(); i++){
				this->verticesDatas[i-d[i]] = this->verticesDatas[i];
				this->vertexDataExistence[i-d[i]] = this->vertexDataExistence[i];
			}
			
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
