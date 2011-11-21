/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * DenseGraphStruct.cpp created in 10 2008.
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
#include <utility>
#include <algorithm>
#include <iostream>
/*
 * Internal Includes
 */

#include <DenseGraphStruct.hpp>
#include <GraphException.hpp>
/*
 * Namespace
 */
namespace kn{
		
	int DenseGraphStruct::beginEdgeIndex()const{
		int ind = -1;
		if(directed){
			unsigned int max = size*size;
			for(unsigned int j = 0; j < max; j++){
				if(mat[j]){
					ind = j;
					break;
				}
			}
		}else{
			bool* tab = mat;
			for(unsigned int j = 0; j < size && ind == -1; j++, tab+=size){
				for(unsigned int i = j; i < size; i++){
					if(tab[i]){
						ind = j*size+i;
						break;
					}
				}
			}
		}
		return ind;
	}
			
	int DenseGraphStruct::nextEdgeIndex(int cur)const{
		int ind = -1;
		if(directed){
			unsigned int max = size*size;
			for(unsigned int j = cur+1; j < max; j++){
				if(mat[j]){
					ind = (int)j;
					break;
				}
			}
		}else{
			bool* tab = mat;
			unsigned int i = (unsigned int)cur%size;
			unsigned int j = (unsigned int)cur/size;
			
			tab+=j*size;
			for(i = i+1; i < size; i++){
				if(tab[i]){
					ind = (int)(j*size+i);
					break;
				}
			}
			tab +=size;
			for(j = j+1; j < size && ind == -1; j++, tab+=size){
				for(unsigned int i = j; i < size; i++){
					if(tab[i]){
						ind = (int)(j*size+i);
						break;
					}
				}
			}
		}
		return ind;
	}
			
	std::pair<unsigned int, unsigned int> DenseGraphStruct::getEdge(int index, unsigned int /*lastIn*/) const{
		return std::make_pair(((unsigned int)index)/size, ((unsigned int)index)%size);
	}
		
	DenseGraphStruct::~DenseGraphStruct(){
		if(mat){
			delete[] mat;
			mat = 0;
		}
	}

	DenseGraphStruct::DenseGraphStruct(const GraphStruct* model){
		buildGraph(model->getSize(),model->edges_begin(),model->edges_end(),model->isDirected());
	}

	DenseGraphStruct::DenseGraphStruct(const GraphStruct& model){
		buildGraph(model.getSize(),model.edges_begin(),model.edges_end(),model.isDirected());
	}
	
	DenseGraphStruct::DenseGraphStruct(unsigned int size, const std::vector<std::pair<unsigned int, unsigned int> >& edges, bool directed){
		buildGraph(size,edges.begin(),edges.end(),directed);
	}
	
	template<class InputIterator>
	void DenseGraphStruct::buildGraph(unsigned int size, InputIterator edges_start, InputIterator edges_stop, bool directed){
		this->size = size;
		this->directed = directed;
		mat = new bool[size*size];
		std::fill(mat, mat+size*size, false);
		innerDegrees.resize(size, 0);
		outerDegrees.resize(size, 0);
		while(edges_start != edges_stop){
			std::pair<unsigned int, unsigned int> edge = *edges_start;
			mat[edge.second+edge.first*size]=true;
			outerDegrees[edge.first]++;
			innerDegrees[edge.second]++;
			if(!directed && edge.first!=edge.second){
				mat[edge.first+edge.second*size]=true;
				outerDegrees[edge.second]++;
				innerDegrees[edge.first]++;	
			}
			edges_start++;
		}
		_maxInnerDegree = *std::max_element(innerDegrees.begin(), innerDegrees.end());
		_maxOuterDegree = *std::max_element(outerDegrees.begin(), outerDegrees.end());
		_maxDegree = 0;
		if(directed){
			for(unsigned int i = 0; i < size; i++){
				unsigned int deg =  outerDegrees[i]+innerDegrees[i];
				_maxDegree = std::max(_maxDegree, deg);		
			}
		}else{
			for(unsigned int i = 0; i < size; i++){
				unsigned int deg =  outerDegrees[i]+(mat[(size+1)*i]?1:0);
				_maxDegree = std::max(_maxDegree, deg);		
			}			
		}
	}
	
	DenseGraphStruct* DenseGraphStruct::clone()const{
		return new DenseGraphStruct(this);
	}
	
	
	std::vector<unsigned int> DenseGraphStruct::neighbours(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::neighbours");
		std::vector<unsigned int> n;
		bool* t = mat+vertex*size;
		for(unsigned int i = 0; i < size; i++){
			if(*t)n.push_back(i);
			t++;
		}
		if(directed){
			t = mat+vertex;
			for(unsigned int i = 0; i < size; i++){
				if(*t && !mat[vertex*size+i])n.push_back(i);
				t+=size;
			}
		}
		return n;	
	}
			
	std::vector<unsigned int> DenseGraphStruct::successors(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::successors");
		std::vector<unsigned int> n;
		bool* t = mat+vertex*size;
		for(unsigned int i = 0; i < size; i++){
			if(*t)n.push_back(i);
			t++;
		}
		return n;	
	}
	
	std::vector<unsigned int> DenseGraphStruct::predecessors(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::predecessors");
		std::vector<unsigned int> n;
		bool* t = mat+vertex;
		for(unsigned int i = 0; i < size; i++){
			if(*t)n.push_back(i);
			t+=size;
		}
		return n;	
	}
	
	unsigned int DenseGraphStruct::degree(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::degree");
		if(directed)
			return innerDegree(vertex)+outerDegree(vertex);
		return outerDegrees[vertex]+(mat[(size+1)*vertex]?1:0);
	
	}
			
	unsigned int DenseGraphStruct::innerDegree(unsigned int vertex) const{
		if(vertex>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::innerDegree");
		return innerDegrees[vertex];
	}

	unsigned int DenseGraphStruct::outerDegree(unsigned int vertex)const{
		if(vertex>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::outerDegree");
		return outerDegrees[vertex];		
	}
	
	bool DenseGraphStruct::areLinked(unsigned int vertexA, unsigned int vertexB) const{
		if(vertexA>=size || vertexB>=size)
			throw GraphException("index out of bound", "DenseGraphStruct::areLinked");
		return mat[vertexA*size+vertexB];
	}
	
	bool DenseGraphStruct::contains(unsigned int vertex) const{
		return vertex<size;
	}
	
	
		/*
		 * End of Namespace
		 */
}

