/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MutableGraphStruct.cpp created in 10 2008.
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
 * External Includes
 */
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <iostream>
/*
 * Internal Includes
 */

#include <MutableGraphStruct.hpp>
#include <GraphException.hpp>
/*
 * Namespace
 */
namespace kn{
		
	int MutableGraphStruct::beginEdgeIndex()const{
		unsigned int v = 0;
		while(v < maxIndex){
			if(existence[v] && successorsSet[v].size()>0){
				return (int)(v*maxIndex+*(successorsSet[v].begin()));
			}
			v++;
		}
		return -1;
		
	}
			
	int MutableGraphStruct::nextEdgeIndex(int cur)const{
		if(cur == -1)return -1;
		unsigned int from = cur/maxIndex;
		unsigned int dest = cur%maxIndex;
		std::set<unsigned int>::iterator next = successorsSet[from].upper_bound(dest);
		if(next != successorsSet[from].end())return from*maxIndex +(*next);
		while(++from < maxIndex){
			if(existence[from] && successorsSet[from].size()>0){
				if(!directed){
					if(successorsSet[from].count(from))return from*(maxIndex+1);
					next = successorsSet[from].upper_bound(from);
					if(next!=successorsSet[from].end())return from*maxIndex+(*next);
				}else return from*maxIndex + *(successorsSet[from].begin());
			}	
		}
		return -1;
	}
			
	std::pair<unsigned int, unsigned int> MutableGraphStruct::getEdge(int index, unsigned int /*lastIn*/)const{
		return std::make_pair(index/maxIndex, index%maxIndex);
	}
		
	unsigned int MutableGraphStruct::beginVertexIndex()const{
		return nextVertexIndex(-1);
	}
	
			
	unsigned int MutableGraphStruct::nextVertexIndex(int cur)const{
		while((unsigned int)(++cur) < maxIndex && !existence[cur]) ;
		return cur;
	}
	
	unsigned int MutableGraphStruct::endVertexIndex()const{
		return maxIndex;
	}	
		
		
		
		
	MutableGraphStruct::~MutableGraphStruct(){}
	
	MutableGraphStruct::MutableGraphStruct(bool directed){
		isCompacted = true;
		this->directed = directed;
		size = 0;
		maxIndex = 0;
	}
	
	MutableGraphStruct::MutableGraphStruct(const GraphStruct* model){
		buildGraph(model->getSize(), model->edges_begin(), model->edges_end(), model->isDirected());
	}

	MutableGraphStruct::MutableGraphStruct(const GraphStruct& model){
		buildGraph(model.getSize(), model.edges_begin(), model.edges_end(), model.isDirected());
	}
	
	MutableGraphStruct::MutableGraphStruct(unsigned int size, const std::vector<std::pair<unsigned int, unsigned int> >& edges, bool directed){
		buildGraph(size, edges.begin(), edges.end(), directed);	
	}
	
	template<class InputIterator>
	void MutableGraphStruct::buildGraph(unsigned int size,InputIterator edges_start, InputIterator edges_stop, bool directed){
		isCompacted = true;
		this->size = size;
		maxIndex = size;
		this->directed = directed;
		successorsSet.resize( size, std::set<unsigned int>());
		existence.resize(size,true);
		
		while(edges_start != edges_stop){
			std::pair<unsigned int, unsigned int> edge = *edges_start;
			successorsSet[edge.first].insert(edge.second);
			if(!directed)successorsSet[edge.second].insert(edge.first);
			edges_start++;
		}
		computeMaxDegrees();
	}
			
			
	void MutableGraphStruct::computeMaxDegrees(){
		_maxDegree = 0;
		_maxInnerDegree = 0;
		_maxOuterDegree = 0;
		for(unsigned int i = 0; i < maxIndex; i++){
			if(!existence[i])continue;
			unsigned int deg = successorsSet[i].size();
			unsigned int outdeg = deg;
			if(directed){
				unsigned int indeg = 0;
				std::vector< std::set<unsigned int> >::iterator it = successorsSet.begin(), end = successorsSet.end();
				while(it != end){
					if(it->count(i)>0)
						indeg++;
					it++;
				}
				_maxInnerDegree = std::max(_maxInnerDegree, indeg);
				deg += indeg;
			}else{
				if(successorsSet[i].count(i) > 0) deg++;
			}
			
			_maxDegree = std::max(_maxDegree,deg);
			_maxOuterDegree = std::max(_maxOuterDegree, outdeg);
		}
		if(!directed){
			_maxInnerDegree = _maxOuterDegree;
		}
	}
	
			
	
	MutableGraphStruct* MutableGraphStruct::clone()const{
	 	return new MutableGraphStruct(this);
	 }
	
	
	
	std::vector<unsigned int> MutableGraphStruct::neighbours(unsigned int vertex) const{
		if(vertex>=maxIndex)
			throw GraphException("index out of bound", "MutableGraphStruct::neighbours");
		if(!existence[vertex])
			throw GraphException("removed vertex", "MutableGraphStruct::neighbours");
			
		if(!directed)
			return std::vector<unsigned int>(successorsSet[vertex].begin(),successorsSet[vertex].end());
		std::vector<unsigned int> n;
		std::set<unsigned int>::iterator sIt = successorsSet[vertex].begin(), end = successorsSet[vertex].end();
		unsigned int s = *sIt;
		unsigned int p = 0;
		while(true){
			while(p < maxIndex && (!existence[p] || successorsSet[p].count(vertex)==0))p++;
		 	if(sIt == end || p >= maxIndex)break;
		 	while(s <= p && sIt != end){
		 		if(s!=p)n.push_back(s);
		 		sIt++;
		 		s = *sIt;
		 	}
			n.push_back(p);
			p++;
		}
		n.insert(n.end(), sIt, end);
		while(p < maxIndex){
			if(existence[p] && successorsSet[p].count(vertex)>0){
				n.push_back(p);		
			}
			p++;
		 }
		return n;	
	}
			
	std::vector<unsigned int> MutableGraphStruct::successors(unsigned int vertex) const{
		if(vertex>=maxIndex)
			throw GraphException("index out of bound", "MutableGraphStruct::successors");
		if(!existence[vertex])
			throw GraphException("removed vertex", "MutableGraphStruct::successors");
		return std::vector<unsigned int>(successorsSet[vertex].begin(),successorsSet[vertex].end());	
	}
	
	std::vector<unsigned int> MutableGraphStruct::predecessors(unsigned int vertex) const{
		if(vertex>=maxIndex)
			throw GraphException("index out of bound", "MutableGraphStruct::predecessors");
		if(!existence[vertex])
			throw GraphException("removed vertex", "MutableGraphStruct::predecessors");
		
		if(directed){
			std::vector<unsigned int> n;
			unsigned int p = 0;
			while(p < maxIndex){
				if(existence[p] && successorsSet[p].count(vertex)>0)
					n.push_back(p);
				p++;
			}
			return n;
		}
		return std::vector<unsigned int>(successorsSet[vertex].begin(),successorsSet[vertex].end());		
	}
	
	
	
	
	unsigned int MutableGraphStruct::degree(unsigned int vertex) const{
		if(directed){
			return successors(vertex).size()+predecessors(vertex).size();
		}
		std::vector<unsigned int> nb = neighbours(vertex);
		return nb.size()+std::count(nb.begin(), nb.end(),vertex);
	}
			
	unsigned int MutableGraphStruct::innerDegree(unsigned int vertex) const{
		return predecessors(vertex).size();
	}
			
	unsigned int MutableGraphStruct::outerDegree(unsigned int vertex)const{
		return successors(vertex).size();
	}
			
	
	
	
	
	bool MutableGraphStruct::areLinked(unsigned int vertexA, unsigned int vertexB) const{
		if(vertexA>=maxIndex || vertexB>=maxIndex)
			throw GraphException("index out of bound", "MutableGraphStruct::areLinked");
		if(!existence[vertexA] || !existence[vertexB])
			throw GraphException("removed vertex", "MutableGraphStruct::areLinked");
			
		return successorsSet[vertexA].count(vertexB)>0;
	}
	
	
	unsigned int MutableGraphStruct::addVertex(){
		size++;
		existence.resize(++maxIndex, true);
		successorsSet.push_back(std::set<unsigned int>());
		return maxIndex-1;
	}
			
	void MutableGraphStruct::removeVertex(unsigned int vertex, bool recompact){
		if(!existence[vertex])return;
		size--;
		if(vertex<size)isCompacted = false;
		existence[vertex]=false;
		successorsSet[vertex].clear();
		unsigned int p = 0;	
		while(p < maxIndex){
			if(existence[p])
				successorsSet[p].erase(vertex);
			p++;
		}	
		if(recompact)compact();
		computeMaxDegrees();
		acyclic = T_Undef;
	}
	
	void MutableGraphStruct::addEdge(unsigned int vertexA, unsigned int vertexB){
		if(vertexA>=maxIndex || vertexB>=maxIndex)
			throw GraphException("index out of bound", "MutableGraphStruct::addEdge");
		if(!existence[vertexA] || !existence[vertexB])
			throw GraphException("removed vertex", "MutableGraphStruct::addEdge");
			
		successorsSet[vertexA].insert(vertexB);
		if(!directed)successorsSet[vertexB].insert(vertexA);	
		acyclic = T_Undef;	
	}
			
	void MutableGraphStruct::removeEdge(unsigned int vertexA, unsigned int vertexB){
		if(vertexA>=size || vertexB>=size || !existence[vertexA] || !existence[vertexB])
			return;
		successorsSet[vertexA].erase(vertexB);
		if(!directed)successorsSet[vertexB].erase(vertexA);	
		computeMaxDegrees();
		acyclic = T_Undef;
	}
			
	std::map<unsigned int, unsigned int> MutableGraphStruct::compact(){
		std::map<unsigned int, unsigned int> decal;
		if(isCompacted)return decal;
		std::vector<unsigned int> lut;
		unsigned int dec=0;
		for(unsigned int i = 0; i < maxIndex; i++){
			if(!existence[i]) dec++;
			else lut.push_back(i);
			decal[i]=dec;
		}
		
		for(unsigned int i = 0; i < size; i++){
			existence[i]=true;
			unsigned int match = lut[i];
			std::set<unsigned int> newValues;
			std::set<unsigned int>::iterator it = successorsSet[match].begin(), end = successorsSet[match].end();
			while(it!=end){
				newValues.insert(*it-decal[*it]);
				it++;
			}
			successorsSet[i] = newValues;
		}
		existence.erase(existence.begin()+size, existence.end());
		successorsSet.erase(successorsSet.begin()+size, successorsSet.end());
		maxIndex = size;
		isCompacted = true;
		return decal;
	}
	
	
	
	bool MutableGraphStruct::contains(unsigned int vertex) const{
		return vertex<maxIndex && existence[vertex];
	}
	
	
		/*
		 * End of Namespace
		 */
}

