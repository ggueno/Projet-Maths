/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MutableGraphStructTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__MutableGRAPHSTRUCTTEST_HPP__
#define __OPENKN_GRAPH__MutableGRAPHSTRUCTTEST_HPP__

/*
 * External Includes
 */
#include <cxxtest/TestSuite.h>
#include <vector>
#include <utility>
/*
 * Internal Includes
 */
#include <OpenKN/graph/MutableGraphStruct.hpp>
/*
 * Class definition
 */

typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class MutableGraphStructTest : public CxxTest::TestSuite {
public:
	
	void testConstructorWithEdgeList( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
		TS_ASSERT_EQUALS( g.getSize(), size);
		for(unsigned int i = 0; i < size; i++)
			TS_ASSERT(g.contains(i));
		TS_ASSERT(!g.contains(size));
		TS_ASSERT(g.isDirected());
		TS_ASSERT(g.isMutable());	
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				TS_ASSERT(g.areLinked(i,j));
				TS_ASSERT(!g.areLinked(j,i));
			}
		}
		
		kn::MutableGraphStruct g2(size, edges, false);
		
		TS_ASSERT_EQUALS(g2.getSize(), size);
		for(unsigned int i = 0; i < size; i++)
			TS_ASSERT(g2.contains(i));
		TS_ASSERT(!g2.contains(size));
		TS_ASSERT(!g2.isDirected());
		TS_ASSERT(g2.isMutable());
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				TS_ASSERT(g2.areLinked(i,j));
				TS_ASSERT(g2.areLinked(j,i));
			}
		}
		
			
		TS_ASSERT(g.isConnected());
		TS_ASSERT(g.isAcyclic());	
		TS_ASSERT(g2.isConnected());
		TS_ASSERT(!g2.isAcyclic());	
	}
  
  
  	void testConstructorByCopy( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		
		kn::MutableGraphStruct g(size, edges, true);
		kn::MutableGraphStruct g2(&g);
		TS_ASSERT_EQUALS(g2.getSize(),g.getSize());
		for(unsigned int i = 0; i < size+2; i++)
			TS_ASSERT_EQUALS(g2.contains(i),g.contains(i));
	
		TS_ASSERT_EQUALS(g2.isDirected(),g.isDirected());
		TS_ASSERT_EQUALS(g2.isMutable(),g.isMutable());
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				TS_ASSERT_EQUALS(g2.areLinked(i,j),g.areLinked(i,j));
			}
		}
	}
  
  	void testClone( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		
		kn::MutableGraphStruct g(size, edges, true);
		kn::GraphStruct* g2 = g.clone();
		TS_ASSERT_EQUALS(g2->getSize(),g.getSize());
		for(unsigned int i = 0; i < size+2; i++)
			TS_ASSERT_EQUALS(g2->contains(i),g.contains(i));
	
		TS_ASSERT_EQUALS(g2->isDirected(),g.isDirected());
		TS_ASSERT_EQUALS(g2->isMutable(),g.isMutable());
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				TS_ASSERT_EQUALS(g2->areLinked(i,j),g.areLinked(i,j));
			}
		}
		delete g2;
	}
  
  	
  	void testDegree( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
  		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g.degree(i), size+1);
  		}
  		
  		kn::MutableGraphStruct g2(size, edges, false);
  		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g2.degree(i), size+1);
  		}
  	}
  
  	void testMaxDegree( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			edges.push_back(Edge(2,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
		TS_ASSERT_EQUALS(g.maxDegree(), size+1);
  		
  		kn::MutableGraphStruct g2(size, edges, false);
  		TS_ASSERT_EQUALS(g2.maxDegree(), size+1);
  	}
  
  	
  	void testInnerDegree( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
  		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g.innerDegree(i), i+1);
  		}
  		
  		kn::MutableGraphStruct g2(size, edges, false);
  		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g2.innerDegree(i), size);
  		}
  	}
  
  	void testMaxInnerDegree( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			edges.push_back(Edge(2,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
		TS_ASSERT_EQUALS(g.maxInnerDegree(), 1);
  		
  		kn::MutableGraphStruct g2(size, edges, false);
  		TS_ASSERT_EQUALS(g2.maxInnerDegree(), size);
  	}
  
  	
 	 void testOuterDegree( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
  		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g.outerDegree(i), size-i);
  		}
  		
  		kn::MutableGraphStruct g2(size, edges, false);
  		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g2.outerDegree(i), size);
  		}
  	}
  
  	void testMaxOuterDegree( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			edges.push_back(Edge(2,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
		TS_ASSERT_EQUALS(g.maxOuterDegree(), size);
  		
  		kn::MutableGraphStruct g2(size, edges, false);
  		TS_ASSERT_EQUALS(g2.maxOuterDegree(), size);
  	}
  	
  	
  	void testAreLinked( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			edges.push_back(Edge(2,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
  		for(int i = 0; i < size; i++){
			TS_ASSERT(g.areLinked(2,i));
			if(i!=2)
  				TS_ASSERT(!g.areLinked(i,2));
  		}
  		kn::MutableGraphStruct g2(size, edges, false);
  		for(int i = 0; i < size; i++){
			TS_ASSERT(g2.areLinked(2,i));
			TS_ASSERT(g2.areLinked(i,2));
  		}
  	}
  	
  	void testSuccessors( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
		for(int i = 0; i < size; i++){
	  		std::vector<unsigned int> successors = g.successors(i);
			for(int j = i+1; j < size; j++){
  				TS_ASSERT_EQUALS(std::count(successors.begin(), successors.end(), j), 1);
  			}
  		}
  		kn::MutableGraphStruct g2(size, edges, false);
		for(int i = 0; i < size; i++){
	  		std::vector<unsigned int> successors = g2.successors(i);
			for(int j = 0; j < size; j++){
  				TS_ASSERT_EQUALS(std::count(successors.begin(), successors.end(), j), i!=j?1:0);
  			}
  		}
  	}
  	
  	void testPredecessors( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
		for(int i = 0; i < size; i++){
	  		std::vector<unsigned int> predecessors = g.predecessors(i);
			for(int j = 0; j < i; j++){
  				TS_ASSERT_EQUALS(std::count(predecessors.begin(), predecessors.end(), j), 1);
  			}
  		}
  		kn::MutableGraphStruct g2(size, edges, false);
		for(int i = 0; i < size; i++){
	  		std::vector<unsigned int> predecessors = g2.predecessors(i);
			for(int j = 0; j < size; j++){
  				TS_ASSERT_EQUALS(std::count(predecessors.begin(), predecessors.end(), j), i!=j?1:0);
  			}
  		}
  	}
  	
  	
  	void testNeighbours( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraphStruct g(size, edges, d==0);
			for(int i = 0; i < size; i++){
		  		std::vector<unsigned int> neighbours = g.neighbours(i);
				for(int j = 0; j < size; j++){
	  				TS_ASSERT_EQUALS(std::count(neighbours.begin(), neighbours.end(), j), i!=j?1:0);
	  			}
	  		}
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
				kn::MutableGraphStruct g(size, edges, d==0);
  				TS_ASSERT_EQUALS(g.isConnected(), false);
		}		
		edges.push_back(Edge(1,0));
		for(int d = 0; d < 2; d++){
			kn::MutableGraphStruct g(size, edges, d==0);
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
				kn::MutableGraphStruct g(size, edges, d==0);
  				TS_ASSERT_EQUALS(g.isAcyclic(), true);
		}		
		edges.push_back(Edge(0,size-1));
		for(int d = 0; d < 2; d++){
				kn::MutableGraphStruct g(size, edges, d==0);
  				TS_ASSERT_EQUALS(g.isAcyclic(), d==0);
		}
		edges.push_back(Edge(size-1,0));
		kn::MutableGraphStruct g(size, edges, true);
  		TS_ASSERT_EQUALS(g.isAcyclic(), false);
  	}
  	
  	
  	
  	void testContains( void ){
  		int size = 5;
		EdgeSet edges;
		kn::MutableGraphStruct g(size, edges, true);
  		for(int i = 0; i < size; i++)
			TS_ASSERT(g.contains(i));
		TS_ASSERT(!g.contains(-1));
  		TS_ASSERT(!g.contains(size));
  	}
  	
  	
  	void testIsMutable( void ){
  		int size = 5;
		EdgeSet edges;
  		kn::MutableGraphStruct g(size, edges, true);
  		TS_ASSERT(g.isMutable());
  	}
  	
  	void testIsCompact( void ){
  		int size = 10;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(true);
		TS_ASSERT(g.isCompact());
		kn::MutableGraphStruct g2(size, edges, true);
  		TS_ASSERT(g2.isCompact());
		g2.removeVertex(9);
		TS_ASSERT(g2.isCompact());
  		g2.removeVertex(8);
		TS_ASSERT(g2.isCompact());
		g2.removeVertex(0);
		TS_ASSERT(!g2.isCompact());
  		g2.compact();
		TS_ASSERT(g2.isCompact());
  		g2.removeVertex(4,true);
		TS_ASSERT(g2.isCompact()); 	
		
		kn::MutableGraphStruct g3(size, edges, false);
  		TS_ASSERT(g3.isCompact());
		g3.removeVertex(9);
		TS_ASSERT(g3.isCompact());
  		g3.removeVertex(8);
		TS_ASSERT(g3.isCompact());
		g3.removeVertex(0);
		TS_ASSERT(!g3.isCompact());
  		g3.compact();
		TS_ASSERT(g3.isCompact());
  		g3.removeVertex(4,true);
		TS_ASSERT(g3.isCompact()); 		
 	}
	
	void testAddVertex( void ){
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
		for(int i = 0; i < size; i++){
			TS_ASSERT_EQUALS(g.addVertex(),size+i);
			TS_ASSERT(g.contains(size+i));
		}
	}
	
	void testRemoveVertex( void ){		
		int size = 15;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		kn::MutableGraphStruct g(size, edges, true);
		for(int i = 8; i < 12; i++){
			g.removeVertex(i);
			TS_ASSERT(!g.contains(i));
		}
	}
	
	void testAddEdge( void ){
		int size = 10;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
		for(int i = 1; i < size; i++){
			TS_ASSERT(!g.areLinked(i,0));
			g.addEdge(i,0);
			TS_ASSERT(g.areLinked(i,0));
		}
	
		kn::MutableGraphStruct g2(false);
		g2.addVertex();
		for(int i = 1; i < size; i++){
			g2.addVertex();
			TS_ASSERT(!g2.areLinked(i,0));
			g2.addEdge(i,0);
			TS_ASSERT(g2.areLinked(i,0));
		}
	
	}
	
	void testRemoveEdge( void ){
		int size = 10;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
		for(int i = 1; i < size; i++){
			TS_ASSERT(g.areLinked(0,i));
			g.removeEdge(0,i);
			TS_ASSERT(!g.areLinked(0,i));
		}
		kn::MutableGraphStruct g2(size, edges,false);
		for(int i = 1; i < size; i++){
			TS_ASSERT(g2.areLinked(0,i));
			TS_ASSERT(g2.areLinked(i,0));
			g2.removeEdge(0,i);
			TS_ASSERT(!g2.areLinked(0,i));
			TS_ASSERT(!g2.areLinked(i,0));
		}
	}
	
	void testCompact( void ){
		int size = 15;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		kn::MutableGraphStruct g(size, edges, true);
		TS_ASSERT(g.isCompact());
		g.removeVertex(6);
		g.removeVertex(9);
		TS_ASSERT(!g.isCompact());
		std::map<unsigned int, unsigned int> corresp = g.compact();
		for(int i = 0; i < 6; i++)
			TS_ASSERT_EQUALS(corresp[i],0);
		for(int i = 6; i < 9; i++)
			TS_ASSERT_EQUALS(corresp[i],1);
		for(int i = 9; i < size; i++)
			TS_ASSERT_EQUALS(corresp[i],2);
	}
	
  	void testEdgesIterator( void ){
  		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		for(int d = 0; d < 2; d++){
			kn::MutableGraphStruct g(size, edges, d==0);
			bool mark[25];
	  		std::fill(mark, mark+25,false);
	  		
	  		kn::MutableGraphStruct::edges_iterator it = g.edges_begin(), end = g.edges_end();
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
	  		std::fill(mark, mark+25,false);
	  		g.removeVertex(2);
	  		cpt = 0;
	  		 it = g.edges_begin(), end = g.edges_end();
	  		for(; it!=end; it++, cpt++){
	  			TS_ASSERT(!mark[it->first*size+it->second]);
	  			mark[it->first*size+it->second] = true;
	  			if(!g.isDirected()){
	  				TS_ASSERT(!mark[it->second*size+it->first]);
	  				mark[it->second*size+it->first] = true;
	  			}
	  		}
	  		TS_ASSERT_EQUALS(cpt, edges.size()-1);
	  		it2 = edges.begin(), end2 = edges.end();
	  		for(; it2!=end2; it2++){
	  			TS_ASSERT_EQUALS(mark[it2->first*size+it2->second],it2->first!=2&&it2->second!=2);
	  			if(!g.isDirected()){
	  				TS_ASSERT_EQUALS(mark[it2->second*size+it2->first],it2->first!=2&&it2->second!=2);
	  			
	  			}
	  		}
	  		
  		}
  	}
  	
  	
  	void testVerticesIterator(){
  		int size = 5;
		EdgeSet edges;
		kn::MutableGraphStruct g(size, edges, false);
		kn::MutableGraphStruct::vertices_iterator it = g.vertices_begin(), end = g.vertices_end();
  		unsigned int cpt = 0;
	  	for(; it!=end; it++, cpt++){
	  		TS_ASSERT_EQUALS(cpt,*it);
  		}
  		
  	}
  	
  	
  	
  	
};


/*
 * End of Anti-doublon
 */
#endif
