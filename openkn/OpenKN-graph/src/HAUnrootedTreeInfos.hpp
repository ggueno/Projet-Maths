/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HAUnrootedTreeInfos.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HA_UNROOTED_TREE_INFOS_HPP__
#define __OPENKN_GRAPH__HA_UNROOTED_TREE_INFOS_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */

#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>


/*
 * Internal Includes
 */
#include "GraphException.hpp"
#include "GraphStruct.hpp"
#include "UndirectedGraph.hpp"
#include "RootingInfo.hpp"
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
		class HAUnrootedTreeInfos : public HATreeInfos<V,E>{
		
		private :
			UndirectedGraph<V,E>* tree;
			std::vector<std::pair<unsigned int,unsigned int> > order;
			RootingInfo* rt;
			/*
			 * Constructor & destructors
			 */
		public:
			 HAUnrootedTreeInfos(UndirectedGraph<V,E>* tree);
				
			 ~HAUnrootedTreeInfos(){
			 	delete rt;
			 }
			

		public : 
			
			std::vector<std::pair<unsigned int,unsigned int> >& navigationOrder();
			
			inline std::vector<unsigned int> ancestors(unsigned int vertex, unsigned int root){
				return rt->ancestors(vertex,root);
			}
			
			inline unsigned int parent(unsigned int vertex, unsigned int root){
				return rt->parent(vertex,root);
			}
			
			inline std::vector<unsigned int> children(unsigned int vertex, unsigned int root){
				return rt->children(vertex,root);
			}
		
			inline std::vector<unsigned int> children(unsigned int vertex){
				return tree->neighbours(vertex);
			}
		
			inline unsigned int size(){
				return tree->size();
			}
			
			inline unsigned int height(){
				unsigned int max = 0;
				for(unsigned int v = 0; v < tree->size(); v++)
					max = std::max(max,rt->height(v));
				return max;
			}
			
			inline unsigned int degree(){
				return rt->maxChildrenDegree();
			}
			
			inline bool isRooted(){
				return false;
			}
			
			inline std::vector<unsigned int> possibleRoots(){
				std::vector<unsigned int> root;
				for(unsigned int v = 0; v < tree->size(); v++)
					root.push_back(v);
				return root;
			}
		};


		template<typename V, typename E>
		HAUnrootedTreeInfos<V,E>::HAUnrootedTreeInfos(UndirectedGraph<V,E>* tree){
			this->tree = tree;
			rt = new RootingInfo(tree->getGraphStruct());
			unsigned int s = tree->size();
			
			this->weights.resize(s*s);
			this->distances.resize(s*s);
			for(unsigned int r = 0; r < s; r++){
				for(unsigned int i = r+1; i < s; i++){
					unsigned int par = rt->parent(i,r);
					if(i == par)continue;
					E val = tree->getEdgeData(par,i);
					unsigned int dist = 1;
					this->weights[par*s+i] = val;
					this->weights[par+i*s] = val;
				
					this->distances[par*s+i] = dist;
					this->distances[par+i*s] = dist;
				
					unsigned int ppar;
					ppar = rt->parent(par,r);
					while(par!=ppar){
						dist++;
						if((double)val<0 || (double)(tree->getEdgeData(ppar,par))<0)val = (E)(-1.0);
						else val+=tree->getEdgeData(ppar,par);
						this->weights[ppar*s+i] = val;
						this->weights[ppar+i*s] = val;
						this->distances[ppar*s+i] = dist;
						this->distances[ppar+i*s] = dist;
						par = ppar;
						ppar = rt->parent(par,r);
					} 
				}
			}
		}

		template<typename V, typename E>
		std::vector<std::pair<unsigned int,unsigned int> >& HAUnrootedTreeInfos<V,E>::navigationOrder(){
			if(order.size()!=0)return order;
			std::queue<unsigned int> q;
			unsigned int s = tree->size();
			bool* marker = new bool[s*s];
			std::fill(marker, marker+s*s, false);
			for(unsigned int v = 0; v < s; v++)
				if(tree->degree(v) == 1)
					q.push(v);
			unsigned int cur;
			while(!q.empty()){
				cur = q.front();
				q.pop();
				std::vector<unsigned int> nb = tree->neighbours(cur);
				std::vector<unsigned int>::iterator it = nb.begin(), it2, end = nb.end();
				while(it != end){
					if(!marker[cur*s+(*it)]){
						it2 = nb.begin();
						bool ok = true;
						while(it2!=end){
							if(*it2 != *it && !marker[cur+(*it2)*s]){
								ok = false;
								break;
							}
							it2++;
						}
						if(ok){
							marker[cur*s+(*it)] = true;
							order.push_back(std::make_pair(cur, *it));
							q.push(*it);	
						}
					}
					it++;
				}
			}
			for(unsigned int v = 0; v < s; v++){
				order.push_back(std::make_pair(v,v));
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
