/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * GraphStruct.hpp created in 10 2008.
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
#ifndef __OPENKN_GRAPH__GRAPHSTRUCT_HPP__
#define __OPENKN_GRAPH__GRAPHSTRUCT_HPP__


/*
 * External Includes
 */
#include <vector>
#include <utility>
#include <map>
/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{
		
		enum Tribool{T_False, T_True, T_Undef};

		/*
		 * Class definition
		 */
	
		/** \brief Interface for graph structure
		 *
		 */
		class GraphStruct{ 
		
		
		protected:
			virtual int beginEdgeIndex()const = 0;
			virtual int nextEdgeIndex(int cur)const = 0;
			virtual std::pair< unsigned int, unsigned int > getEdge(int index, unsigned int lastIn)const = 0;
			virtual unsigned int beginVertexIndex()const;
			virtual unsigned int nextVertexIndex(int cur)const;
			virtual unsigned int endVertexIndex()const;
		
		protected:
			bool directed;
			unsigned int size;
			unsigned int _maxInnerDegree;
			unsigned int _maxOuterDegree;
			unsigned int _maxDegree;
			Tribool acyclic;
			Tribool connected;
			
			
		protected: 
			void testAcyclic();
			
			void testConnected();
				
		public:
			
			class edges_iterator{
				private : 
					const GraphStruct* graph;
					int index;
					std::pair<unsigned int, unsigned int> cur;
				
				public :	
					inline edges_iterator(const GraphStruct* graph, bool end=false){
						this->graph = graph;
						if(end)
							index = -1;
						else{
							index = graph->beginEdgeIndex();
							cur = graph->getEdge(index,0);
						}
					}
					
					inline ~edges_iterator(){}
						
					inline edges_iterator operator ++ (){
						index = graph->nextEdgeIndex(index);
						cur = graph->getEdge(index,cur.first);
						return *this;
					}
					
					inline edges_iterator operator ++ (int /*n*/){
						index = graph->nextEdgeIndex(index);
						cur = graph->getEdge(index,cur.first);
						return *this;
					}
					
					inline const std::pair<unsigned int, unsigned int>* operator -> (){
						return &cur;
					}  	
					
					inline const std::pair<unsigned int, unsigned int>& operator * (){
						return cur;
					}  	
					
					inline bool operator == (const edges_iterator& it){
						return graph == it.graph && index == it.index;
					}
					
					inline bool operator != (const edges_iterator& it){
						return graph != it.graph || index != it.index;
					}
					
					typedef std::input_iterator_tag iterator_category;
					typedef std::pair<unsigned int, unsigned int> value_type;
					typedef std::pair<unsigned int, unsigned int>* pointer;
					typedef std::pair<unsigned int, unsigned int>& reference;
					typedef ptrdiff_t difference_type;
					
			}; 
			
			class vertices_iterator{
				private : 
					const GraphStruct* graph;
					unsigned int cur;
				
				public :	
					inline vertices_iterator(const GraphStruct* graph, bool end=false){
						this->graph = graph;
						if(end)
							cur = graph->endVertexIndex();
						else
							cur = graph->beginVertexIndex();
					}
					
					inline ~vertices_iterator(){}
						
					inline vertices_iterator operator ++ (){
						cur = graph->nextVertexIndex(cur);
						return *this;
					}
					
					inline vertices_iterator operator ++ (int /*n*/){
						cur = graph->nextVertexIndex(cur);
						return *this;
					}
					
					inline const unsigned int * operator -> (){
						return &cur;
					}  	
					
					inline const unsigned int& operator * (){
						return cur;
					}  	
					
					inline bool operator == (const vertices_iterator& it){
						return graph == it.graph && cur == it.cur;
					}
					
					inline bool operator != (const vertices_iterator& it){
						return graph != it.graph || cur != it.cur;
					}
					
					typedef std::input_iterator_tag iterator_category;
					typedef unsigned int value_type;
					typedef unsigned int* pointer;
					typedef unsigned int& reference;
					typedef ptrdiff_t difference_type;
					
			}; 
			
			friend class edges_iterator;
			friend class vertices_iterator;

			/** \brief Virtual destructor
			 *
			 */
			virtual ~GraphStruct(){}
			
			inline GraphStruct(){
				acyclic = T_Undef;
				connected = T_Undef;
				_maxInnerDegree = 0;
				_maxOuterDegree = 0;
				_maxDegree = 0;
			}
			
			virtual GraphStruct* clone()const=0;

		public :
		
			inline unsigned int getSize() const{
				return size;
			}
			
			inline bool isDirected() const{
				return directed;
			}
			
			inline bool isAcyclic(){
				switch(acyclic){
					case T_Undef :
						testAcyclic();
						return isAcyclic();
					case T_True : 
						return true;
					case T_False : 
						return false;
				}
				return isAcyclic();
			}
			
			inline bool isConnected(){
				switch(connected){
					case T_Undef :
						testConnected();
						return isConnected();
					case T_True : 
						return true;
					case T_False : 
						return false;
				}
			}
			
			virtual std::vector<unsigned int> neighbours(unsigned int vertex) const =0;
			
			virtual std::vector<unsigned int> successors(unsigned int vertex) const =0;
			
			virtual std::vector<unsigned int> predecessors(unsigned int vertex) const =0;
			
			virtual unsigned int degree(unsigned int vertex) const =0;
			
			virtual unsigned int innerDegree(unsigned int vertex) const =0;
			
			virtual unsigned int outerDegree(unsigned int vertex) const =0;
			
			inline unsigned int maxDegree() const{return _maxDegree;}
			
			unsigned int maxInnerDegree() const{return _maxInnerDegree;}
			
			unsigned int maxOuterDegree() const{return _maxOuterDegree;}
			
			virtual bool areLinked(unsigned int vertexA, unsigned int vertexB) const =0;
			
			virtual bool contains(unsigned int vertex) const =0;
			
			edges_iterator edges_begin()const;
			
			edges_iterator edges_end()const;	
			
			vertices_iterator vertices_begin()const;
			
			vertices_iterator vertices_end()const;	
			
			virtual bool isMutable()const = 0;	
		};
	
	
	

		/*
		 * End of Namespace
		 */
}

/*
 * End of Anti-doublon
 */
#endif

