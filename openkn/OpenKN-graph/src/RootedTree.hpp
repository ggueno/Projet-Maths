/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * RootedTree.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__ROOTED_TREE_HPP__
#define __OPENKN_GRAPH__ROOTED_TREE_HPP__

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
#include "DenseGraphStruct.hpp"
#include "SparseGraphStruct.hpp"
#include "BiSparseGraphStruct.hpp"
#include "DirectedGraph.hpp"

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
		class RootedTree : public DirectedGraph<V,E>{
		
		private:
			unsigned int _root;
			unsigned int _height;
			std::vector<unsigned int> parents;
		
			/*
			 * Constructor & destructors
			 */
		public:
			RootedTree(const Graph<V,E>& model);
			
			RootedTree(const Graph<V,E>* model);
			
			RootedTree(const Graph<V,E>& model, GraphType type);
			
			RootedTree(const Graph<V,E>* model, GraphType type);
		
			RootedTree(unsigned int size,const std::vector<std::pair<unsigned int, unsigned int> >& edges, GraphType type);
			
			RootedTree(unsigned int size, const std::vector< V >& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector< E >& edgesDatas,
			GraphType type, bool checking=true);
			
			~RootedTree();

		private : 
			bool checkTreeProperties(bool checking=true);
		

		public : 
			std::vector<unsigned int> children(unsigned int vertex);
			
			unsigned int parent(unsigned int vertex);
			
			std::vector<unsigned int> ancestors(unsigned int vertex);
			
			std::vector<unsigned int> siblings(unsigned int vertex);
			
			unsigned int height(unsigned int vertex);
			
			unsigned int height();
			
			unsigned int childrenDegree(unsigned int vertex);
			
			unsigned int maxChildrenDegree();
			
			unsigned int root(){
				return _root;
			}
			
		};



		template<typename V, typename E>
		bool RootedTree<V,E>::checkTreeProperties(bool checking){
			if(checking){
			if(!this->isAcyclic())return false;
			}
			_height = this->graphStruct->getSize();
			unsigned int nbRoots = 0;
			GraphStruct::vertices_iterator it = this->graphStruct->vertices_begin(), end = this->graphStruct->vertices_end();
			while(it!=end){
				if(this->innerDegree(*it) == 0){
					_root = *it;
					nbRoots++;
					if(nbRoots>1)return false;
				}
				it++;
			}
			if(nbRoots == 0)return false;
			if(checking){
			std::vector<bool> mark(this->graphStruct->getSize(), false);
			std::stack<unsigned int> fifo;
			fifo.push(_root);
			while(!fifo.empty()){
				std::vector<unsigned int> succ = this->graphStruct->successors(fifo.top());
				mark[fifo.top()] = true;
				fifo.pop();
				std::vector<unsigned int>::iterator i = succ.begin(), e = succ.end(); 
				while(i != e){
					fifo.push(*i);
					i++;
				}
			}
			it = this->graphStruct->vertices_begin();
			while(it!=end){
				if(!mark[*it])return false;
				it++;
			}
			}
			//computation of the parents
			std::vector<unsigned int> pred;
			parents.resize(_height);
			for(unsigned int v = 0; v < _height; v++){
		 		pred = this->graphStruct->predecessors(v);
				if(pred.size() == 0)parents[v] = v;
				else parents[v] = pred[0];
			}
			return true;
		}
		

		/*
		 * Templates definitions
		 */
		
		
		template<typename V, typename E>
		RootedTree<V,E>::RootedTree(const Graph<V,E>& model):DirectedGraph<V,E>(model){
			if(!model.isDirected())throw GraphException("The graph need to be directed", "RootedTree<V,E>::RootedTree(const Graph<V,E>& model)");
			if(!checkTreeProperties())throw GraphException("The graph need to be a rooted tree", "RootedTree<V,E>::RootedTree(const Graph<V,E>& model)");
		}
		
		template<typename V, typename E>
		RootedTree<V,E>::RootedTree(const Graph<V,E>* model):DirectedGraph<V,E>(model){
			if(!model->isDirected())throw GraphException("The graph need to be directed", "RootedTree<V,E>::RootedTree(const Graph<V,E>* model)");
			if(!checkTreeProperties())throw GraphException("The graph need to be a rooted tree", "RootedTree<V,E>::RootedTree(const Graph<V,E>* model)");
		}
			
		template<typename V, typename E>
		RootedTree<V,E>::RootedTree(const Graph<V,E>& model, GraphType type):DirectedGraph<V,E>(model,type){
			if(!model.isDirected())throw GraphException("The graph need to be directed", "RootedTree<V,E>::RootedTree(const Graph<V,E>& model, GraphType type)");
			if(!checkTreeProperties())throw GraphException("The graph need to be a rooted tree", "RootedTree<V,E>::RootedTree(const Graph<V,E>& model, GraphType type)");
		}
		
		template<typename V, typename E>
		RootedTree<V,E>::RootedTree(const Graph<V,E>* model, GraphType type):DirectedGraph<V,E>(model,type){
			if(!model->isDirected())throw GraphException("The graph need to be directed", "RootedTree<V,E>::RootedTree(const Graph<V,E>* model, GraphType type)");
			if(!checkTreeProperties())throw GraphException("The graph need to be a rooted tree", "RootedTree<V,E>::RootedTree(const Graph<V,E>* model, GraphType type)");
		}
		
		template<typename V, typename E>
		RootedTree<V,E>::RootedTree(unsigned int size,
						  const std::vector<std::pair<unsigned int, unsigned int> >& edges, 
						  GraphType type):DirectedGraph<V,E>(size, edges, type){
						  if(!checkTreeProperties())throw GraphException("The graph need to be a rooted tree", "RootedTree<V,E>::RootedTree(unsigned int size, const std::vector<std::pair<unsigned int, unsigned int> >& edges, GraphType type)");
		}
			
		template<typename V, typename E>
		RootedTree<V,E>::RootedTree(unsigned int size, const std::vector<V>& verticesDatas, 
			const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector<E>& edgesDatas,
			GraphType type, bool checking):DirectedGraph<V,E>(size, verticesDatas, edges, edgesDatas, type){
			if(!checkTreeProperties(checking))throw GraphException("The graph need to be a rooted tree", "RootedTree(unsigned int size, const std::vector<V>& verticesDatas, const std::vector<std::pair<unsigned int, unsigned int> >& edges, const std::vector<E>& edgesDatas, GraphType type)");
		}
			
		template<typename V, typename E>
		RootedTree<V,E>::~RootedTree(){
		
		
		
		}
		
		
		/*
		 * Functions definitions
		 */
		template<typename V, typename E>
		std::vector<unsigned int> RootedTree<V,E>::children(unsigned int vertex){
			return this->graphStruct->successors(vertex);
		}
			
		template<typename V, typename E>
		unsigned int RootedTree<V,E>::parent(unsigned int vertex){
			return parents[vertex];
		}
			
		template<typename V, typename E>
		std::vector<unsigned int> RootedTree<V,E>::ancestors(unsigned int vertex){
			std::vector<unsigned int> anc;
			unsigned int par = parent(vertex); 
			while(par != vertex){
				anc.push_back(par);
				vertex = par;
				par = parent(vertex); 
			}
			return anc;
		}
			
		template<typename V, typename E>
		std::vector<unsigned int> RootedTree<V,E>::siblings(unsigned int vertex){
			std::vector<unsigned int> sib;
			unsigned int par = parent(vertex);
			if(par == vertex)return sib;
			std::vector<unsigned int> ch = children(par);
			std::vector<unsigned int>::iterator i = ch.begin(), e = ch.end();
			while(i!=e){
				if(*i!=vertex)
					sib.push_back(*i);
				i++;
			}
			return sib;
		}
			
		template<typename V, typename E>
		unsigned int RootedTree<V,E>::height(unsigned int vertex){
			return ancestors(vertex).size();
		}
		
		
		template<typename V, typename E>
		unsigned int RootedTree<V,E>::childrenDegree(unsigned int vertex){
			return this->graphStruct->outerDegree(vertex);	
		}	
			
		template<typename V, typename E>
		unsigned int RootedTree<V,E>::maxChildrenDegree(){
			return this->graphStruct->maxOuterDegree();
		}
		
		template<typename V, typename E>
		unsigned int RootedTree<V,E>::height(){
			if(_height < this->graphStruct->getSize())return _height;
			_height = 0;
			for(unsigned int h = 0; h < this->graphStruct->getSize(); h++){
				_height = std::max(_height, height(h));
			}
			return _height;
		}
		
		
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
