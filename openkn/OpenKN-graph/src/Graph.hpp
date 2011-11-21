/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Graph.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__GRAPH_HPP__
#define __OPENKN_GRAPH__GRAPH_HPP__

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
#include "DenseGraphStruct.hpp"
#include "SparseGraphStruct.hpp"
#include "BiSparseGraphStruct.hpp"
#include "MutableGraphStruct.hpp"
/*
 * Namespace
 */
namespace kn{
		/** \brief Enumeration for graph structure types
		  * DENSE : graph structure by adjacency matrix
		  * SPARSE : graph structure by list of successors
		  * BISPARSE : graph structure by list of successors and list of predecessors
		  * MUTABLE : graph structure allowing edition
		 */
		enum GraphType { DENSE, SPARSE, BISPARSE, MUTABLE};
	
		/*
		 * Class definition
		 */

		/** \brief Generic class for graphs
		 */
		template<typename V, typename E>
		class Graph {
			/*
			 * Constructor & destructors
			 */
		public:
			
			/** \brief Edge iterator
			 */
			typedef GraphStruct::edges_iterator edges_iterator; 
			
			/** \brief Vertex iterator
			 */
			typedef GraphStruct::vertices_iterator vertices_iterator; 
			
			/** \brief Copy constructor
			  * Create a graph by copying the input graph
			  * \param model the graph to copy
			 */
			Graph(const Graph<V,E>& model);
			
			/** \brief Copy constructor
			  * Create a graph by copying the input graph
			  * \param model pointer to the graph to copy
			 */
			Graph(const Graph<V,E>* model);
			
			/** \brief Copy constructor
			  * Create a graph by copying the input graph with specification of graph structure
			  * \param model the graph to copy
			  * \param type type of graph structure 
			 */
			 Graph(const Graph<V,E>& model, GraphType type);
			
			/** \brief Copy constructor
			  * Create a graph by copying the input graph with specification of graph structure
			  * \param model pointer to the graph to copy
			  * \param type type of graph structure 
			 */
			Graph(const Graph<V,E>* model, GraphType type);
			
			/** \brief Create a graph of size "size" using a list of edge for the edge initialization
			  * Create a graph of size "size" using a list of edge for the edge initialization
			  * \param size the number of vertices of the graph
			  * \param edges list of the edges
			  * \param type type of graph structure
			  * \param directed true for a directed graph, false for an undirected graph 
			 */
			Graph(unsigned int size,const std::vector<std::pair<unsigned int, unsigned int> >& edges, GraphType type, bool directed);
			
			
			
			Graph(unsigned int size, const std::vector< V >& verticesDatas, 
						const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas,
						GraphType type, bool directed);
	

			/**
				* \brief Destructor
				*/
			~Graph();


		protected :
		
			
			inline Graph(){}
		
		
			/** \brief container for vertices datas
			 */
			std::vector<V> verticesDatas;
			
			/** \brief markers for vertices datas existence
			 */
			std::vector<bool> vertexDataExistence;
			
			
			/** \brief container for edges datas
			 */
			std::map<std::pair<unsigned int, unsigned int>, E> edgesDatas;
			
			/** \brief graph structure
			 */
			GraphStruct* graphStruct;
			
			
			/** \brief Construct references of edges datas.
			  * Only for constructor use
			 */
			void buildEdgesDatas(const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas);

		public : 
			
			/** \brief Give the number of vertices 
			  * \return the number of vertices
			 */
			inline unsigned int size(){
				return graphStruct->getSize();
			}
		
			/** \brief Test the presence of a specific vertex
			  * \param vertex the vertex to test
			  * \return true if the vertex is contained, false otherwise
			 */
			inline bool contains(unsigned int vertex) const{
				return graphStruct->contains(vertex);
			}
			
			/** \brief Iterator to the first edge of the graph
			  * The dereferenced iterator is a std::pair<unsigned int, unsigned int>
			  * \return iterator to the first edge of the graph
			 */
			inline edges_iterator edges_begin()const{
				return graphStruct->edges_begin();
			}
			
			/** \brief Iterator just past the last edge of the graph
			  * The dereferenced iterator is a std::pair<unsigned int, unsigned int>
			  * \return Iterator just past the last edge of the graph
			 */
			inline edges_iterator edges_end()const{
				return graphStruct->edges_end();
			}
			
			
			/** \brief Iterator to the first vertex of the graph
			  * \return iterator to the first vertex of the graph
			 */
			inline vertices_iterator vertices_begin()const{
				return graphStruct->vertices_begin();
			}
			
			/** \brief Iterator just past the last vertex of the graph
			  * \return Iterator just past the last vertex of the graph
			 */
			inline vertices_iterator vertices_end()const{
				return graphStruct->vertices_end();
			}
			
			/** \brief Set new linked data for a given vertex 
			  * \param vertex the vertex which will be linked to the data
			  * \param data the data which will be linked to the vertex
			 */
			void setVertexData(unsigned int vertex, const V& data); 
			
			/** \brief Give the data linked with a given vertex 
			  * \param vertex the vertex which is linked to the data
			  * \return data the data which is linked to the vertex
			 */
			const V& getVertexData(unsigned int vertex)const; 
			
			/** \brief Set new linked data for a given edge 
			  * \param vertexA begining of the edge which will be linked to the data
			  * \param vertexB end of the edge which will be linked to the data
			  * \param data the data which will be linked to the edge
			 */
			void setEdgeData(unsigned int vertexA, unsigned int vertexB, const E& data); 
			
			/** \brief Give the data linked with a given edge 
			  * \param vertexA begining of the edge which is linked to the data
			  * \param vertexB end of the edge which is linked to the data
			  * \return data the data which is linked to the edge
			 */
			 const E& getEdgeData(unsigned int vertexA, unsigned int vertexB)const; 
			
			/** \brief Test of the directed/undirected type of the graph
			  * \return true if the graph is directed, false if it is undirected
			 */
			inline bool isDirected()const{
				return graphStruct->isDirected();
			}
			
			/** \brief Test of the mutability of the graph (possibility of modifications on the graph structure) 
			  * \return true if the graph is mutable, false otherwise
			 */
			inline bool isMutable()const{
				return graphStruct->isMutable();
			}
			
			/** \brief Test if the graph contains cycles
			  * \return true if the graph is acyclic, false otherwise
			 */
			inline bool isAcyclic()const{
				return graphStruct->isAcyclic();
			}
			
			/** \brief Test the connexity 
			  * \return true if the graph is connected, false otherwise
			 */
			inline bool isConnected()const{
				return graphStruct->isConnected();
			}
			
			/** \brief Test of presence of linked data for a given vertex
			  * \param vertex the vertex which will be tested
			  * \return true if the vertex have linked data, false otherwise
			 */
			inline bool haveLinkedData(unsigned int vertex)const{
				if(!graphStruct->contains(vertex))
					throw GraphException("inexistant vertex","Graph::haveLinkedData");
				return vertexDataExistence[vertex];
			}
			
			/** \brief Test of presence of linked data for a given edge
			  * \param vertexA begining of the edge which will be tested
			  * \param vertexB end of the edge which will be tested
			  * \return true if the edge have linked data, false otherwise
			 */
			inline bool haveLinkedData(unsigned int vertexA, unsigned int vertexB)const{
				if(!graphStruct->areLinked(vertexA,vertexB))
					throw GraphException("inexistant edge","Graph::haveLinkedData");
				return edgesDatas.find(std::make_pair(vertexA, vertexB)) != edgesDatas.end();
			}
			
			inline GraphStruct* getGraphStructCopy()const{
				return graphStruct->clone();
			}
			inline const GraphStruct* getGraphStruct()const{
				return graphStruct;
			}
		};

		/*
		 * Templates definitions
		 */
		 template<typename V, typename E>
		Graph<V,E>::Graph(const Graph<V,E>& model){
			this->graphStruct = model.graphStruct->clone();
			this->vertexDataExistence = model.vertexDataExistence;
			this->verticesDatas = model.verticesDatas;
			this->edgesDatas = model.edgesDatas;
		}
		
		template<typename V, typename E>
		Graph<V,E>::Graph(const Graph<V,E>* model){
			this->graphStruct = model->graphStruct->clone();
			this->vertexDataExistence = model->vertexDataExistence;
			this->verticesDatas = model->verticesDatas;
			this->edgesDatas = model->edgesDatas;
		}
		
		template<typename V, typename E>
		Graph<V,E>::Graph(const Graph<V,E>& model, GraphType type){
			switch(type){
				case DENSE : this->graphStruct = new DenseGraphStruct(model.graphStruct);break;
				case SPARSE : this->graphStruct = new SparseGraphStruct(model.graphStruct);break;
				case BISPARSE : this->graphStruct = new BiSparseGraphStruct(model.graphStruct);break;
				case MUTABLE :  this->graphStruct = new MutableGraphStruct(model.graphStruct);break;
			}
			this->vertexDataExistence = model.vertexDataExistence;
			this->verticesDatas = model.verticesDatas;
			this->edgesDatas = model.edgesDatas;
		}
		
		template<typename V, typename E>
		Graph<V,E>::Graph(const Graph<V,E>* model, GraphType type){
			switch(type){
				case DENSE : this->graphStruct = new DenseGraphStruct(model->graphStruct);break;
				case SPARSE : this->graphStruct = new SparseGraphStruct(model->graphStruct);break;
				case BISPARSE : this->graphStruct = new BiSparseGraphStruct(model->graphStruct);break;
				case MUTABLE :  this->graphStruct = new MutableGraphStruct(model->graphStruct);break;
			}
			this->vertexDataExistence = model->vertexDataExistence;
			this->verticesDatas = model->verticesDatas;
			this->edgesDatas = model->edgesDatas;
		}
		
		
		template<typename V, typename E>
		Graph<V,E>::Graph(unsigned int size,const std::vector<std::pair<unsigned int, unsigned int> >& edges, GraphType type, bool directed){
			switch(type){
				case DENSE : this->graphStruct = new DenseGraphStruct(size, edges, directed);break;
				case SPARSE : this->graphStruct = new SparseGraphStruct(size, edges, directed);break;
				case BISPARSE : this->graphStruct = new BiSparseGraphStruct(size, edges, directed);break;
				case MUTABLE :  this->graphStruct = new MutableGraphStruct(size, edges, directed);break;
			}
			this->vertexDataExistence.resize(size, false);
		}
			
		template<typename V, typename E>
		Graph<V,E>::Graph(unsigned int size, const std::vector<V>& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector<E>& edgesDatas,
			GraphType type, bool directed){
			
			switch(type){
				case DENSE : this->graphStruct = new DenseGraphStruct(size, edges, directed);break;
				case SPARSE : this->graphStruct = new SparseGraphStruct(size, edges, directed);break;
				case BISPARSE : this->graphStruct = new BiSparseGraphStruct(size, edges, directed);break;
				case MUTABLE :  this->graphStruct = new MutableGraphStruct(size, edges, directed);break;
			}
			this->vertexDataExistence.resize(size, true);
			this->verticesDatas = verticesDatas;
			buildEdgesDatas(edges, edgesDatas);
		}
			
		template<typename V, typename E>
		Graph<V,E>::~Graph(){
			delete this->graphStruct;
		}
		
		template<typename V, typename E>
		void Graph<V,E>::buildEdgesDatas(const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas){
			if(edges.size() != edgesDatas.size())
				throw GraphException("dismatching for edges datas","Graph<V,E>::buildEdgesDatas");
			std::vector<std::pair<unsigned int, unsigned int> >::const_iterator pit = edges.begin(), pend = edges.end();
			typename std::vector<E>::const_iterator dit = edgesDatas.begin(), dend = edgesDatas.end();
			while(pit != pend){	
				this->edgesDatas[*pit] = *dit;
				if(!this->graphStruct->isDirected()) {
					std::pair<unsigned int, unsigned int> op(pit->second, pit->first);
					this->edgesDatas[op] = *dit;
				}
				pit++;
				dit++;
			}
		}

		 
		 
		template<typename V, typename E>
		void Graph<V,E>::setVertexData(unsigned int vertex, const V& data){
			if(!graphStruct->contains(vertex))
				throw GraphException("inexistant vertex","Graph::setVertexData");
			verticesDatas.resize(vertex+1);
			vertexDataExistence.resize(vertex+1,true);
			verticesDatas[vertex] = data;
		} 
			
		template<typename V, typename E>
		const V& Graph<V,E>::getVertexData(unsigned int vertex)const {
			if(!graphStruct->contains(vertex))
				throw GraphException("inexistant vertex","Graph::getVertexData");
			if(!vertexDataExistence[vertex])
				throw GraphException("no linked datas for this vertex","Graph::getVertexData");
			return verticesDatas[vertex];
		} 
			
		template<typename V, typename E>
		void Graph<V,E>::setEdgeData(unsigned int vertexA, unsigned int vertexB, const E& data){
			if(!graphStruct->areLinked(vertexA,vertexB))
				throw GraphException("inexistant edge","Graph::setEdgeData");
			edgesDatas[std::make_pair(vertexA, vertexB)] = data;
			if(!graphStruct->isDirected())
				edgesDatas[std::make_pair(vertexB, vertexA)] = data;
			
		} 
			
		template<typename V, typename E>
		const E& Graph<V,E>::getEdgeData(unsigned int vertexA, unsigned int vertexB)const {
			if(!graphStruct->areLinked(vertexA,vertexB))
				throw GraphException("inexistant edge","Graph::getEdgeData");
			typename std::map<std::pair<unsigned int, unsigned int>, E>::const_iterator iter = edgesDatas.find(std::make_pair(vertexA, vertexB));
    			if(iter == edgesDatas.end())
    				throw GraphException("no linked datas for this edge","Graph::getEdgeData");
			return iter->second;
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
