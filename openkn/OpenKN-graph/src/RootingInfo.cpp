/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RootingInfo.cpp created in 10 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-RootingInfo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-RootingInfo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

#include "RootingInfo.hpp"
#include <queue>
#include <iostream>
/*
 * Namespace
 */
namespace kn {

		RootingInfo::RootingInfo(const GraphStruct* model, bool checking){
			graph = model->clone();
			if(checking){
				if(graph->isDirected())throw GraphException("The graph need to be undirected","RootingInfo(const GraphStruct* model, bool precompute)");
				if(!graph->isAcyclic())throw GraphException("The graph need to be acyclic","RootingInfo(const GraphStruct* model, bool precompute)");
			}			
			GraphStruct::vertices_iterator root = graph->vertices_begin(), end = graph->vertices_end();
			unsigned int size = graph->getSize();
			//compute parents for each rooting
			parents.resize(size*size, size);
			while(root!=end){
				parents[(*root)*(size+1)] = *root;	
				std::queue<unsigned int> fifo;
				fifo.push(*root);
				while(!fifo.empty()){
					unsigned int cur = fifo.front();
					unsigned int par  = parents[(*root)*size+cur];
					std::vector<unsigned int> ch = graph->neighbours(cur);
					std::vector<unsigned int>::iterator i = ch.begin(), e = ch.end();
					while(i!=e){
						if(*i != par){
							parents[(*root)*size+*i] = cur;
							fifo.push(*i);
						}
						i++;
					}
					fifo.pop();
					
				}
				root++;			
			}
			
		}
			
		RootingInfo::~RootingInfo(){
			delete graph;
		}
	
		std::vector<unsigned int> RootingInfo::children(unsigned int vertex, unsigned int root){
			if(!graph->contains(vertex) || !graph->contains(root))throw GraphException("unknown vertex id","children(unsigned int vertex, unsigned int root)");
			std::vector<unsigned int> nb = graph->neighbours(vertex);
			unsigned int par = parents[root*graph->getSize()+vertex];
			std::vector<unsigned int> ch;
			std::vector<unsigned int>::iterator it = nb.begin(), end = nb.end();
			while(it!=end){
				if(*it != par)
					ch.push_back(*it);
				it++;
			}
			return ch;
		}
		
		unsigned int RootingInfo::parent(unsigned int vertex, unsigned int root){
			if(!graph->contains(vertex) || !graph->contains(root))throw GraphException("unknown vertex id","parent(unsigned int vertex, unsigned int root)");
			return parents[root*graph->getSize()+vertex];		
		}
		
		
			
		std::vector<unsigned int> RootingInfo::ancestors(unsigned int vertex, unsigned int root){
			unsigned int offset = root*graph->getSize();
			std::vector<unsigned int> anc;
			unsigned int par = parents[offset+vertex];
			while(vertex!=par){
				anc.push_back(par);
				vertex = par;
				par = parents[offset+vertex];
			}
			return anc;
		}
			
			
		unsigned int RootingInfo::height(unsigned int vertex, unsigned int root){
			unsigned int offset = root*graph->getSize();
			unsigned int h = 0;
			unsigned int par = parents[offset+vertex];
			while(vertex!=par){
				h++;
				vertex = par;
				par = parents[offset+vertex];
			}
			return h;
		}
			
		unsigned int RootingInfo::height(unsigned int root){
			unsigned int max = 0;
			unsigned int s = graph->getSize();
			for(unsigned int i = 0; i < s; i++){
				max = std::max(max, height(i,root));
			}
			return max;
		}
			
		unsigned int RootingInfo::childrenDegree(unsigned int vertex, unsigned int root){	
			if(!graph->contains(vertex) || !graph->contains(root))throw GraphException("unknown vertex id","childrenDegree(unsigned int vertex, unsigned int root)");
			if(vertex == parents[root*graph->getSize()+vertex])
				return graph->degree(vertex);
			return graph->degree(vertex)-1;			
		}
			
		unsigned int RootingInfo::maxChildrenDegree(){
			return graph->maxDegree();
		}

  /*
   * End of Namespace
   */
}

