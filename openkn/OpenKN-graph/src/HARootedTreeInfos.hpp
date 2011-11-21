/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HARootedTreeInfos.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HA_ROOTED_TREE_INFOS_HPP__
#define __OPENKN_GRAPH__HA_ROOTED_TREE_INFOS_HPP__

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
#include "RootedTree.hpp"
#include "HATreeInfos.hpp"
/*
 * Namespace
 */
namespace kn{
	
		
		/*
		 * Class definition
		 */

		/** \brief Rooted tree informations, usefull for homeomorphic alignment
		
		 */
		template<typename V, typename E>
		class HARootedTreeInfos : public HATreeInfos<V,E>{
		
		private :
			
			RootedTree<V,E>* tree;
			std::vector<std::pair<unsigned int,unsigned int> > order;
			std::vector<bool> isAncestor;
			/*
			 * Constructor & destructors
			 */
		public:
			 HARootedTreeInfos(RootedTree<V,E>* tree);
				
			 ~HARootedTreeInfos(){}
			

		public : 
			
			std::vector<std::pair<unsigned int,unsigned int> >& navigationOrder();
			
			inline std::vector<unsigned int> ancestors(unsigned int vertex, unsigned int /*root*/){
				return tree->ancestors(vertex);
			}
			
			inline unsigned int parent(unsigned int vertex, unsigned int root){
				if(!isAncestor[root*tree->size()+vertex])return vertex;
				return tree->parent(vertex);
			}
			
			inline std::vector<unsigned int> children(unsigned int vertex, unsigned int /*root*/){
				return tree->children(vertex);
			}
		
			inline std::vector<unsigned int> children(unsigned int vertex){
				return tree->children(vertex);
			}
			
			inline unsigned int size(){
				return tree->size();
			}
			
			inline unsigned int height(){
				return tree->height();
			}
			
			inline unsigned int degree(){
				return tree->maxChildrenDegree();
			}
			
			inline bool isRooted(){
				return true;
			}
			
			inline std::vector<unsigned int> possibleRoots(){
				std::vector<unsigned int> root(1, tree->root());
				return root;
			}
			
		};


		template<typename V, typename E>
		HARootedTreeInfos<V,E>::HARootedTreeInfos(RootedTree<V,E>* tree){
			this->tree = tree;
			unsigned int s = tree->size();
			this->weights.resize(s*s);
			this->distances.resize(s*s);
			isAncestor.resize(s*s, false);
			for(unsigned int i = 0; i < s; i++){
				unsigned int par = tree->parent(i);
				if(i == par)continue;
				E val = tree->getEdgeData(par,i);
				this->weights[par*s+i] = val;
				this->weights[par+i*s] = val;
				this->distances[par*s+i] = 1;
				this->distances[par+i*s] = 1;
				isAncestor[par*s+i] = true;
				unsigned int dist=1;
				unsigned int ppar;
				ppar = tree->parent(par);
				while(par!=ppar){
					dist++;
					if((double)val<0 || (double)(tree->getEdgeData(ppar,par))<0)val = (E)(-1.0);
					else val+=tree->getEdgeData(ppar,par);
					this->weights[ppar*s+i] = val;
					this->weights[ppar+i*s] = val;
					this->distances[ppar*s+i] = dist;
					this->distances[ppar+i*s] = dist;
					isAncestor[ppar*s+i] = true;
					par = ppar;
					ppar = tree->parent(par);
				} 
			}
		}

		template<typename V, typename E>
		std::vector<std::pair<unsigned int,unsigned int> >& HARootedTreeInfos<V,E>::navigationOrder(){
			if(order.size()!=0)return order;
			unsigned int s = tree->size();
			std::stack<unsigned int> lifo;
			lifo.push(tree->root());
			while(!lifo.empty()){
				if(lifo.top() == s){
					lifo.pop();
					order.push_back(std::make_pair(lifo.top(), tree->parent(lifo.top())));
					lifo.pop();
				}else{
					std::vector<unsigned int> ch = tree->children(lifo.top());
					lifo.push(s);
					std::vector<unsigned int>::iterator it = ch.begin(), end = ch.end();
					while(it != end){
						lifo.push(*it);
						it++;
					}
				}			
			}
			return order;
		}
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
