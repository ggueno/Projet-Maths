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
 * External Includes
 */
#include <vector>
#include <utility>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
/*
 * Internal Includes
 */
#include <GraphStruct.hpp>
/*
 * Namespace
 */
namespace kn{

	GraphStruct::edges_iterator GraphStruct::edges_begin()const{
		return edges_iterator(this);
	}
			
	GraphStruct::edges_iterator GraphStruct::edges_end()const{
		return edges_iterator(this, true);
	}		
	
	GraphStruct::vertices_iterator GraphStruct::vertices_begin()const{
		return vertices_iterator(this);
	}
			
	GraphStruct::vertices_iterator GraphStruct::vertices_end()const{
		return vertices_iterator(this, true);
	}		
	
	unsigned int GraphStruct::beginVertexIndex()const{
	 	return 0;
	 }
	 
	 unsigned int GraphStruct::nextVertexIndex(int cur)const{
	 	return cur+1;
	 }
	 
	 unsigned int GraphStruct::endVertexIndex()const{
	 	return size;
	 }
	 
	
		
	void GraphStruct::testAcyclic(){
		std::stack<int> lifo;
		std::map<unsigned int, bool> marker;
		vertices_iterator vi = vertices_begin(), ve = vertices_end();
		for(;vi!=ve; ++vi)
			marker[*vi] = false;
			
		for(vi = vertices_begin();vi!=ve; ++vi){
			unsigned int i = *vi;
					
			lifo.push(i);
			while(!lifo.empty()){
				if(lifo.top() == -1){
					lifo.pop();
					marker[lifo.top()] = false;
					lifo.pop();
				}else{
					std::vector<unsigned int> nb = successors(lifo.top());
					std::vector<unsigned int>::iterator it = nb.begin(), end = nb.end();
					marker[lifo.top()] = true;
					lifo.push(-1);
					unsigned int count = 0;
					while(it!=end){
						if(marker[*it])count++;
						else lifo.push(*it);
						it++;
					}
					if(count > (directed?0:1)){
						acyclic = T_False;
						return;
					}
				}			
			}	
		}
		acyclic = T_True;
	}



	 void GraphStruct::testConnected(){
		std::stack<int> lifo;
		std::map<unsigned int, bool> marker;
		vertices_iterator vi = vertices_begin(), ve = vertices_end();
		for(;vi!=ve; ++vi)
			marker[*vi] = false;
		lifo.push(*(vertices_begin()));
		while(!lifo.empty()){
			unsigned int i = lifo.top();
			lifo.pop();
			if(!marker[i]){
				marker[i] = true;
				std::vector<unsigned int> succ = neighbours(i);
				std::vector<unsigned int>::iterator it = succ.begin(), end = succ.end();
				while(it!=end){
					if(!marker[*it])
						lifo.push(*it);
					it++;
				}
			}
		}
		vi = vertices_begin();
		for(;vi!=ve; ++vi)
			if(!marker[*vi]){
				connected = T_False;
				return;
			}
		
		connected = T_True;
	 }

	

	/*
	 * End of Namespace
	 */
}

