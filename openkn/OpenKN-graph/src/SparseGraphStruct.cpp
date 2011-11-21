/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * SparseGraphStruct.cpp created in 10 2008.
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

#include <SparseGraphStruct.hpp>
#include <GraphException.hpp>
/*
 * Namespace
 */
namespace kn{
		
	int SparseGraphStruct::beginEdgeIndex()const{
		if(firstSuccessor[size]==0)
			return -1;
		return 0;
		
	}
			
	int SparseGraphStruct::nextEdgeIndex(int cur)const{
		unsigned int ind = cur+1;
		if(!directed)
			while(firstSuccessor[size]>ind && ind>=firstSuccessor[successorsList[ind]+1])
				ind++;
			
		if(firstSuccessor[size]<=ind)
			return -1;
		return ind;
	}
			
	std::pair<unsigned int, unsigned int> SparseGraphStruct::getEdge(int index, unsigned int lastIn)const{
		if(index == -1)
			return std::make_pair(size, size);
		unsigned int dest = successorsList[index];
		while((unsigned int)index>=firstSuccessor[lastIn+1])lastIn++;
		return std::make_pair(lastIn, dest);
	}
		
	
	SparseGraphStruct::~SparseGraphStruct(){	
	}

	SparseGraphStruct::SparseGraphStruct(const GraphStruct* model){
		buildGraph(model->getSize(),model->edges_begin(), model->edges_end(), model->isDirected());
	}

	SparseGraphStruct::SparseGraphStruct(const GraphStruct& model){
		buildGraph(model.getSize(),model.edges_begin(), model.edges_end(), model.isDirected());
	}
	
	SparseGraphStruct::SparseGraphStruct(unsigned int size, const std::vector<std::pair<unsigned int, unsigned int> >& edges, bool directed){
		buildGraph(size, edges.begin(), edges.end(), directed);
	}
	
	template<class InputIterator>
	void SparseGraphStruct::buildGraph(unsigned int size,InputIterator edges_start, InputIterator edges_stop, bool directed){
		this->size = size;
		this->directed = directed;
		firstSuccessor.resize(size+1,0);
		std::set<unsigned int>* successors = new std::set<unsigned int>[size];
		while(edges_start != edges_stop){
			std::pair<unsigned int, unsigned int> edge = *edges_start;
			successors[edge.first].insert(edge.second);
			if(!directed)successors[edge.second].insert(edge.first);
			edges_start++;
		}
		unsigned int sSize = 0;
		for(unsigned int i = 0; i < size; i++){
			sSize += successors[i].size();
		}
		successorsList.resize(sSize);
		unsigned int index = 0;
		for(unsigned int i = 0; i < size; i++){
			firstSuccessor[i] = index;
			std::set<unsigned int>::iterator it2 = successors[i].begin(), end2 = successors[i].end();
			while(it2 != end2){
				successorsList[index++] = *it2;
				it2++;
			}
		}
		firstSuccessor[size] = index;
		_maxDegree = 0;
		_maxInnerDegree = 0;
		_maxOuterDegree = 0;
		for(unsigned int i = 0; i < size; i++){
			_maxDegree = std::max(degree(i), _maxDegree);
			_maxInnerDegree = std::max(innerDegree(i), _maxInnerDegree);
			_maxOuterDegree = std::max(outerDegree(i), _maxOuterDegree);
		}
		delete[] successors;
	}
			
	SparseGraphStruct* SparseGraphStruct::clone()const{
		return new SparseGraphStruct(this);
	}
	
	
	
	std::vector<unsigned int> SparseGraphStruct::neighbours(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::neighbours");
		std::vector<unsigned int> n;
		unsigned int end = firstSuccessor[vertex+1];
		for(unsigned int i = firstSuccessor[vertex];i < end; i++)
			n.push_back(successorsList[i]);
		
		if(directed){
			unsigned int i = firstSuccessor[vertex];
			unsigned int from = 0;
			unsigned int cur = 0;
			end = firstSuccessor[1];
			unsigned int sSize = firstSuccessor[size];	
			while(cur != sSize){
				while(from == successorsList[i] && i < firstSuccessor[vertex+1]){
					
					i++;
					
					cur = end;
					from++;
					end = firstSuccessor[from+1];
				}
				while(cur < end && end <= sSize){			
					if(successorsList[cur++] == vertex)
						n.push_back(from);
				}
				end = firstSuccessor[(++from)+1];
			}	
		}
		return n;	
	}
			
	std::vector<unsigned int> SparseGraphStruct::successors(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::successors");
		std::vector<unsigned int> n;
		unsigned int end = firstSuccessor[vertex+1];
		for(unsigned int i = firstSuccessor[vertex];i < end; i++)
			n.push_back(successorsList[i]);
		return n;	
	}
	
	std::vector<unsigned int> SparseGraphStruct::predecessors(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::predecessors");
		std::vector<unsigned int> n;
		
		if(directed){
			unsigned int from = 0;
			unsigned int cur = 0;
			unsigned int end = firstSuccessor[1];
			unsigned int sSize = firstSuccessor[size];
			while(cur != sSize){
				while(cur < end){
					if(successorsList[cur++] == vertex)
						n.push_back(from);
				}
				end = firstSuccessor[(++from)+1];
			}
		}else{
			unsigned int end = firstSuccessor[vertex+1];
			for(unsigned int i = firstSuccessor[vertex];i < end; i++)
				n.push_back(successorsList[i]);
		}
		return n;	
	}
	
	unsigned int SparseGraphStruct::degree(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::degree");
		if(directed){
			return innerDegree(vertex)+outerDegree(vertex);
		}
		unsigned int begin = firstSuccessor[vertex];
		unsigned int end = firstSuccessor[vertex+1];
		unsigned int deg = end-begin;
		return deg + std::count(successorsList.begin() + begin,successorsList.begin() + end, vertex);
	}
			
	unsigned int SparseGraphStruct::innerDegree(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::innerDegree");
		return std::count(successorsList.begin(), successorsList.end(), vertex);
	}
			
	unsigned int SparseGraphStruct::outerDegree(unsigned int vertex)const{
		if(vertex>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::outerDegree");
		return firstSuccessor[vertex+1] - firstSuccessor[vertex];
	}
	
	bool SparseGraphStruct::areLinked(unsigned int vertexA, unsigned int vertexB) const{
		if(vertexA>=size || vertexB>=size)
			throw GraphException("index out of bound", "SparseGraphStruct::neighbours");
		unsigned int end = firstSuccessor[vertexA+1];
		for(unsigned int i = firstSuccessor[vertexA];i < end; i++)
			if(successorsList[i] == vertexB) return true;
		return false;
	}
	
	
	bool SparseGraphStruct::contains(unsigned int vertex) const{
		return vertex<size;
	}
	
		/*
		 * End of Namespace
		 */
}

