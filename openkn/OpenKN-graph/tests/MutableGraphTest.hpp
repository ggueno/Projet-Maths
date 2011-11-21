/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MutableGraphTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-MutableGraph.
 *
 * The OpenKraken-MutableGraph is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-MutableGraph is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_GRAPH__MUTABLEGRAPHTEST_HPP__
#define __OPENKN_GRAPH__MUTABLEGRAPHTEST_HPP__

/*
 * External Includes
 */
#include <cxxtest/TestSuite.h>
#include <vector>
#include <utility>
#include <iostream>
/*
 * Internal Includes
 */
#include <OpenKN/graph/MutableGraph.hpp>
/*
 * Class definition
 */

typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class MutableGraphTest : public CxxTest::TestSuite {
public:
	
	void testConstructorWithEdgeList( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraph<int, int> g(size, edges, true);
		TS_ASSERT_EQUALS(g.size(), size);
		for(int v = 0; v < size; v++)
			TS_ASSERT(g.contains(v));
		TS_ASSERT(!g.contains(size));
		TS_ASSERT(g.isDirected());
		TS_ASSERT_EQUALS(g.isMutable(), true);
		TS_ASSERT(g.isAcyclic());
		TS_ASSERT(g.isConnected());
		for(int k = 0; k < size+3; k++){
			if(k >= size) {
				TS_ASSERT_THROWS(g.haveLinkedData(k), kn::GraphException);
				continue;
			}
			TS_ASSERT(!g.haveLinkedData(k));
			for(int j = 0; j < size; j++){
				if(j <= k){
					TS_ASSERT_THROWS(g.haveLinkedData(k,j), kn::GraphException);
				}
				else TS_ASSERT(!g.haveLinkedData(k,j));
			}
		}
		
		kn::MutableGraph<int, int> g2(size, edges, false);
		TS_ASSERT_EQUALS(g2.size(), size);
		for(int v = 0; v < size; v++)
			TS_ASSERT(g2.contains(v));
		TS_ASSERT(!g2.contains(size));
		TS_ASSERT(!g2.isDirected());
		TS_ASSERT_EQUALS(g2.isMutable(), true);
		TS_ASSERT(!g2.isAcyclic());
		TS_ASSERT(g2.isConnected());
		for(int k = 0; k < size+3; k++){
			if(k >= size) {
				TS_ASSERT_THROWS(g2.haveLinkedData(k), kn::GraphException);
				continue;
			}
			TS_ASSERT(!g2.haveLinkedData(k));
			for(int j = 0; j < size; j++){
				if(j == k){
					TS_ASSERT_THROWS(g2.haveLinkedData(k,j), kn::GraphException);
				}
				else TS_ASSERT(!g2.haveLinkedData(k,j));
			}
		}
	}
	
	
	void testConstructorWithEdgeListAndDatas( void ) {
		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			for(int j = i+1; j < size; j++){
				edatas.push_back(i+j);
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraph<int, int> g(size, vdatas, edges, edatas, true);
		TS_ASSERT_EQUALS(g.size(), size);
		for(int v = 0; v < size; v++)
			TS_ASSERT(g.contains(v));
		TS_ASSERT(!g.contains(size));
		TS_ASSERT(g.isDirected());
		TS_ASSERT_EQUALS(g.isMutable(), true);
		TS_ASSERT(g.isAcyclic());
		TS_ASSERT(g.isConnected());
		for(int k = 0; k < size+3; k++){
			if(k >= size) {
				TS_ASSERT_THROWS(g.haveLinkedData(k), kn::GraphException);
				continue;
			}
			TS_ASSERT(g.haveLinkedData(k));
			TS_ASSERT_EQUALS(g.getVertexData(k), k);
			for(int j = 0; j < size; j++){
				if(j <= k){
					TS_ASSERT_THROWS(g.haveLinkedData(k,j), kn::GraphException);
					continue;
				}
				TS_ASSERT(g.haveLinkedData(k,j));
				TS_ASSERT_EQUALS(g.getEdgeData(k,j), k+j);
			}
		}
		
		kn::MutableGraph<int, int> g2(size, vdatas, edges, edatas,  false);
		TS_ASSERT_EQUALS(g2.size(), size);
		for(int v = 0; v < size; v++)
			TS_ASSERT(g2.contains(v));
		TS_ASSERT(!g2.contains(size));
		TS_ASSERT(!g2.isDirected());
		TS_ASSERT_EQUALS(g2.isMutable(), true);
		TS_ASSERT(!g2.isAcyclic());
		TS_ASSERT(g2.isConnected());
		for(int k = 0; k < size+3; k++){
			if(k >= size) {
				TS_ASSERT_THROWS(g2.haveLinkedData(k), kn::GraphException);
				continue;
			}
			TS_ASSERT(g2.haveLinkedData(k));
			TS_ASSERT_EQUALS(g2.getVertexData(k), k);
			for(int j = 0; j < size; j++){
				if(j == k){
					TS_ASSERT_THROWS(g2.haveLinkedData(k,j), kn::GraphException);
					continue;
				}
				TS_ASSERT(g2.haveLinkedData(k,j));
				TS_ASSERT_EQUALS(g2.getEdgeData(k,j), k+j);
			}
		}
	}
	
	
	
	void testConstructorByCopy( void ) {
		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			for(int j = i+1; j < size; j++){
				edatas.push_back(i+j);
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> f(size, edges, d==0);
			kn::MutableGraph<int, int> g(f);
			TS_ASSERT_EQUALS(g.size(), f.size());
			for(int v = 0; v < size+1; v++)
				TS_ASSERT_EQUALS(g.contains(v),f.contains(v));
			TS_ASSERT_EQUALS(g.isDirected(),f.isDirected());
			TS_ASSERT_EQUALS(g.isMutable(), f.isMutable());
			TS_ASSERT_EQUALS(g.isAcyclic(),f.isAcyclic());
			TS_ASSERT_EQUALS(g.isConnected(),f.isConnected());
			for(int k = 0; k < size; k++){
				TS_ASSERT_EQUALS(f.haveLinkedData(k),g.haveLinkedData(k));
				for(int j = k+1; j < size; j++){
					TS_ASSERT_EQUALS(f.haveLinkedData(k,j),g.haveLinkedData(k,j));
				}
			}
			
			kn::MutableGraph<int, int> f2(size, vdatas, edges, edatas, d==0);
			kn::MutableGraph<int, int> g2(f2);
			TS_ASSERT_EQUALS(g2.size(), f2.size());
			for(int v = 0; v < size+1; v++)
				TS_ASSERT_EQUALS(g2.contains(v),f2.contains(v));
			TS_ASSERT_EQUALS(g2.isDirected(),f2.isDirected());
			TS_ASSERT_EQUALS(g2.isMutable(), f2.isMutable());
			TS_ASSERT_EQUALS(g2.isAcyclic(),f2.isAcyclic());
			TS_ASSERT_EQUALS(g2.isConnected(),f2.isConnected());
			for(int k = 0; k < size; k++){
				TS_ASSERT_EQUALS(f2.haveLinkedData(k),g2.haveLinkedData(k));
				TS_ASSERT_EQUALS(f2.getVertexData(k), g2.getVertexData(k));
				for(int j = k+1; j < size; j++){
					TS_ASSERT_EQUALS(f2.haveLinkedData(k,j),g2.haveLinkedData(k,j));
					TS_ASSERT_EQUALS(f2.getEdgeData(k,j), g2.getEdgeData(k,j));
				}
			}
		}
	}
  
  
  
  
 	
  	
  	
  	void testContains( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraph<int, int> g(size, edges, true);
		for(int j = 0; j < size; j++)
			TS_ASSERT(g.contains(j));
		TS_ASSERT(!g.contains(-1));
		TS_ASSERT(!g.contains(size));
		
  	}
  	
  	
  	void testIsMutable( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraph<int, int> g(size, edges, true);
		TS_ASSERT_EQUALS(g.isMutable(), true);
		
  	}
  	
  	
  	void testIsDirected( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, edges, d==0);
			TS_ASSERT_EQUALS(g.isDirected(), d==0);
			
		}		
  	}
  	
  	void testIsConnected( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, edges, d==0);
			TS_ASSERT_EQUALS(g.isConnected(), false);
			
		}		
		edges.push_back(Edge(1,0));
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, edges, d==0);
			TS_ASSERT_EQUALS(g.isConnected(), true);
		}		
		
  	}
  	
  	void testIsAcyclic( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(i-1,i));
		}
		for(int d = 0; d < 2; d++){
				kn::MutableGraph<int, int> g(size, edges, d==0);
				TS_ASSERT_EQUALS(g.isAcyclic(), true);
		}		
		edges.push_back(Edge(1,0));
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, edges, d==0);
			TS_ASSERT_EQUALS(g.isAcyclic(), d!=0);
		}		
		edges.push_back(Edge(size-1,0));
		kn::MutableGraph<int, int> g(size, edges, true);
  		TS_ASSERT_EQUALS(g.isAcyclic(), false);
  	}
  	
  	
  	
  	
  	
  	void testEdgesIterator( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, edges, d==0);
			bool mark[25];
	  		std::fill(mark, mark+25,false); 		
	  		kn::MutableGraph<int,int>::edges_iterator it = g.edges_begin(), end = g.edges_end();
	  		int cpt = 0;
	  		for(; it!=end; it++, cpt++){
	  			TS_ASSERT(!mark[it->first*size+it->second]);
	  			mark[it->first*size+it->second] = true;
	  			if(!g.isDirected()){
	  				TS_ASSERT(!mark[it->second*size+it->first]);
	  				mark[it->second*size+it->first] = true;
	  			}
	  		}
	  		TS_ASSERT_EQUALS(cpt, edges.size());
	  		EdgeSet::iterator it2 = edges.begin(), end2 = edges.end();
	  		for(; it2!=end2; it2++){
	  			TS_ASSERT(mark[it2->first*size+it2->second]);
	  			if(!g.isDirected()){
	  				TS_ASSERT(mark[it2->second*size+it2->first]);
	  			}
	  		}
  		}
  	}
  	
  	
  	void testVerticesIterator(){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, edges, d==0);
			kn::MutableGraph<int,int>::vertices_iterator it = g.vertices_begin(), end = g.vertices_end();
				unsigned int cpt = 0;
  			for(; it!=end; it++, cpt++){
  				TS_ASSERT_EQUALS(cpt,*it);
			}
  		}
  	}
  	
  	void testVerticesAccessors( void ){
  		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			for(int j = i+1; j < size; j++){
				edatas.push_back(i+j);
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, vdatas,edges, edatas, d==0);
			for(int j = 0; j < size; j++)
				TS_ASSERT_EQUALS(g.getVertexData(j),j);
			for(int j = 0; j < size; j++){
				g.setVertexData(j,size-j);
				TS_ASSERT_EQUALS(g.getVertexData(j),size-j);
			}
		}
  	}
  	void testEdgesAccessors( void ){
  		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			for(int j = i+1; j < size; j++){
				edatas.push_back(i+j);
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraph<int, int> g(size, vdatas,edges, edatas, d==0);
			for(int j = 0; j < size; j++)
				for(int k = j+1; k < size; k++)
				TS_ASSERT_EQUALS(g.getEdgeData(j,k),j+k);
			for(int j = 0; j < size; j++)
			for(int k = j+1; k < size; k++){
				g.setEdgeData(j,k,k-j);
				TS_ASSERT_EQUALS(g.getEdgeData(j,k),k-j);
			}
			if(d!=0)
				for(int j = 0; j < size; j++)
				for(int k = j+1; k < size; k++){
				g.setEdgeData(k,j,k*j);
				TS_ASSERT_EQUALS(g.getEdgeData(k,j),k*j);
				TS_ASSERT_EQUALS(g.getEdgeData(j,k),k*j);
			}
		}
  	}
  	
//  	unsigned int addVertex();
//	unsigned int addVertex(V& data);
//	void removeVertex(unsigned int vertex, bool recompact=false);
//	void addEdge(unsigned int vertexA, unsigned int vertexB);
//	void addEdge(unsigned int vertexA, unsigned int vertexB, E& data);
//	void removeEdge(unsigned int vertexA, unsigned int vertexB);
//	void compact();
//  	
};


/*
 * End of Anti-doublon
 */
#endif
