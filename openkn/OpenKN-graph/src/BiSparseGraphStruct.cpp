/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * BiSparseGraphStruct.cpp created in 10 2008.
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

#include <BiSparseGraphStruct.hpp>
#include <GraphException.hpp>
/*
 * Namespace
 */
namespace kn{
		
	int BiSparseGraphStruct::beginEdgeIndex()const{
		if(firstSuccessor[size]==0)
			return -1;
		return 0;
	}
	
			
	int BiSparseGraphStruct::nextEdgeIndex(int cur)const{
		unsigned int ind = cur+1;
		if(!directed)
			while(firstSuccessor[size]>ind && ind>=firstSuccessor[successorsList[ind]+1])
				ind++;
			
		if(firstSuccessor[size]<=ind)
			return -1;
		return ind;
	}
			
	std::pair<unsigned int, unsigned int> BiSparseGraphStruct::getEdge(int index, unsigned int lastIn)const{
		if(index == -1)
			return std::make_pair(size, size);
		unsigned int dest = successorsList[index];
		while((unsigned int)index>=firstSuccessor[lastIn+1])lastIn++;
		return std::make_pair(lastIn, dest);
	}
		
	BiSparseGraphStruct::~BiSparseGraphStruct(){
	}


	BiSparseGraphStruct::BiSparseGraphStruct(const GraphStruct* model){
		buildGraph(model->getSize(), model->edges_begin(), model->edges_end(), model->isDirected());
	}


	BiSparseGraphStruct::BiSparseGraphStruct(const GraphStruct& model){
		buildGraph(model.getSize(), model.edges_begin(), model.edges_end(), model.isDirected());
	}
	

	BiSparseGraphStruct::BiSparseGraphStruct(unsigned int size, const std::vector<std::pair<unsigned int, unsigned int> >& edges, bool directed){
		buildGraph(size, edges.begin(), edges.end(), directed);
	}
	
	
	template<class InputIterator>
	void BiSparseGraphStruct::buildGraph(unsigned int size,InputIterator edges_start, InputIterator edges_stop, bool directed){
		this->size = size;
		this->directed = directed;
		firstSuccessor.resize(size+1);
		if(directed)
			firstPredecessor.resize(size+1);
			
		std::set<unsigned int>* successors = new std::set<unsigned int>[size];
		std::set<unsigned int>* predecessors = NULL;
		if(directed) predecessors = new std::set<unsigned int>[size];
		
		while(edges_start != edges_stop){
			std::pair<unsigned int, unsigned int> edge = *edges_start;
			successors[edge.first].insert(edge.second);
			if(!directed)successors[edge.second].insert(edge.first);
			else predecessors[edge.second].insert(edge.first);
			edges_start++;
		}
		unsigned int sSize = 0;
		for(unsigned int i = 0; i < size; i++){
			sSize += successors[i].size();
		}
		successorsList.resize(sSize);
		if(directed)
			predecessorsList.resize(sSize);
			
		unsigned int index = 0;
		unsigned int index2 = 0;
		for(unsigned int i = 0; i < size; i++){
			firstSuccessor[i] = index;
			std::set<unsigned int>::iterator it2 = successors[i].begin(), end2 = successors[i].end();
			while(it2 != end2){
				successorsList[index++] = *it2;
				it2++;
			}
			if(directed){
				firstPredecessor[i] = index2;
				it2 = predecessors[i].begin(), end2 = predecessors[i].end();
				while(it2 != end2){
					predecessorsList[index2++] = *it2;
					it2++;
				}
			}
		}
		firstSuccessor[size] = index;
		if(directed)firstPredecessor[size] = index2;
		
		_maxDegree = 0;
		_maxInnerDegree = 0;
		_maxOuterDegree = 0;
		for(unsigned int i = 0; i < size; i++){
			_maxDegree = std::max(degree(i), _maxDegree);
			_maxInnerDegree = std::max(innerDegree(i), _maxInnerDegree);
			_maxOuterDegree = std::max(outerDegree(i), _maxOuterDegree);
		}
		
		delete[] successors;
		if(directed) delete[] predecessors;
	}
	
	BiSparseGraphStruct* BiSparseGraphStruct::clone() const{
		return new BiSparseGraphStruct(this);
	}
	
	
	std::vector<unsigned int> BiSparseGraphStruct::neighbours(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "BiSparseGraphStruct::neighbours");
		
		std::vector<unsigned int> n;
		if(!directed){
			unsigned int end = firstSuccessor[vertex+1];
			for(unsigned int i = firstSuccessor[vertex];i < end; i++)
				n.push_back(successorsList[i]);
		}else{
			unsigned int endS = firstSuccessor[vertex+1];
			unsigned int endP = firstPredecessor[vertex+1];
			unsigned int s = firstSuccessor[vertex];
			unsigned int p = firstPredecessor[vertex];
			while(s < endS && p < endP){
				if(successorsList[s] == predecessorsList[s]){
					n.push_back(successorsList[s]);
					s++;
					p++;
				}else if(successorsList[s] < predecessorsList[s]){
					n.push_back(successorsList[s]);
					s++;
				}else{
					n.push_back(predecessorsList[p]);
					p++;
				}
			}
			for(; s < endS; s++)
				n.push_back(successorsList[s]);
			for(; p < endP; p++)
				n.push_back(predecessorsList[p]);
		}
		return n;	
	}
		
					
	std::vector<unsigned int> BiSparseGraphStruct::successors(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "BiSparseGraphStruct::neighbours");
		std::vector<unsigned int> n;
		unsigned int end = firstSuccessor[vertex+1];
		for(unsigned int i = firstSuccessor[vertex];i < end; i++)
			n.push_back(successorsList[i]);
		return n;	
	}
	

	std::vector<unsigned int> BiSparseGraphStruct::predecessors(unsigned int vertex) const{
		std::vector<unsigned int> n;
		
		if(directed){
			unsigned int end = firstPredecessor[vertex+1];
			for(unsigned int i = firstPredecessor[vertex];i < end; i++)
				n.push_back(predecessorsList[i]);
		}else{
			unsigned int end = firstSuccessor[vertex+1];
			for(unsigned int i = firstSuccessor[vertex];i < end; i++)
				n.push_back(successorsList[i]);
		}
		return n;	
	}
	
	unsigned int BiSparseGraphStruct::degree(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "BiSparseGraphStruct::degree");
		if(directed){
			return innerDegree(vertex)+outerDegree(vertex);
		}
		unsigned int begin = firstSuccessor[vertex];
		unsigned int end = firstSuccessor[vertex+1];
		unsigned int deg = end-begin;
		return deg+std::count(successorsList.begin() + begin, successorsList.begin() + end, vertex);
	}
			
	unsigned int BiSparseGraphStruct::innerDegree(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "BiSparseGraphStruct::innerDegree");
		if(directed)
			return firstPredecessor[vertex+1] - firstPredecessor[vertex];
		return firstSuccessor[vertex+1] - firstSuccessor[vertex];
	}
			
	unsigned int BiSparseGraphStruct::outerDegree(unsigned int vertex)const{
		if(vertex>=size)
			throw GraphException("index out of bound", "BiSparseGraphStruct::outerDegree");
		return firstSuccessor[vertex+1] - firstSuccessor[vertex];
	}
	
	
	bool BiSparseGraphStruct::areLinked(unsigned int vertexA, unsigned int vertexB) const{
		if(vertexA>=size || vertexB>=size)
			throw GraphException("index out of bound", "BiSparseGraphStruct::neighbours");
		unsigned int end = firstSuccessor[vertexA+1];
		for(unsigned int i = firstSuccessor[vertexA];i < end; i++)
			if(successorsList[i] == vertexB) return true;
		return false;
	}
	
	
	bool BiSparseGraphStruct::contains(unsigned int vertex) const{
		return vertex<size;
	}
			
	
	
	
		/*
		 * End of Namespace
		 */
}

