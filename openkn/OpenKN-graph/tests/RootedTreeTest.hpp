/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * GraphTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__ROOTEDTREETEST_HPP__
#define __OPENKN_GRAPH__ROOTEDTREETEST_HPP__

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
#include <OpenKN/graph/RootedTree.hpp>
/*
 * Class definition
 */

typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class RootedTreeTest : public CxxTest::TestSuite {
public:
	
	void testConstructorWithEdgeList( void ) {
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> g(size, edges, type[i]);
			TS_ASSERT_EQUALS(g.size(), size);
			for(int v = 0; v < size; v++)
				TS_ASSERT(g.contains(v));
			TS_ASSERT(!g.contains(size));
			TS_ASSERT(g.isDirected());
			TS_ASSERT_EQUALS(g.isMutable(), type[i]==kn::MUTABLE);
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
		}
	}
	
	
	void testConstructorWithEdgeListAndDatas( void ) {
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
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
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> g(size, vdatas, edges, edatas, type[i]);
			TS_ASSERT_EQUALS(g.size(), size);
			for(int v = 0; v < size; v++)
				TS_ASSERT(g.contains(v));
			TS_ASSERT(!g.contains(size));
			TS_ASSERT(g.isDirected());
			TS_ASSERT_EQUALS(g.isMutable(), type[i]==kn::MUTABLE);
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
		}
	}
	
	
	
	void testConstructorByCopy( void ) {
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
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
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> f(size, edges, type[i]);
			kn::RootedTree<int, int> g(f);
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
			
			kn::RootedTree<int, int> f2(size, vdatas, edges, edatas, type[i]);
			kn::RootedTree<int, int> g2(f2);
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
  
  
  
  
 	 void testConstructorByCopyAndType( void ) {
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
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
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> f(size, edges, type[i]);
			kn::RootedTree<int, int> f2(size, vdatas, edges, edatas, type[i]);
			
			for(int i2 = 0; i2 < 4; i2++){
				kn::RootedTree<int, int> g(f,type[i2]);
				TS_ASSERT_EQUALS(g.size(), f.size());
				for(int v = 0; v < size+1; v++)
					TS_ASSERT_EQUALS(g.contains(v),f.contains(v));
				TS_ASSERT_EQUALS(g.isDirected(),f.isDirected());
				TS_ASSERT_EQUALS(g.isMutable(), type[i2]==kn::MUTABLE);
				TS_ASSERT_EQUALS(g.isAcyclic(),f.isAcyclic());
				TS_ASSERT_EQUALS(g.isConnected(),f.isConnected());
				for(int k = 0; k < size; k++){
					TS_ASSERT_EQUALS(f.haveLinkedData(k),g.haveLinkedData(k));
					for(int j = k+1; j < size; j++){
						TS_ASSERT_EQUALS(f.haveLinkedData(k,j),g.haveLinkedData(k,j));
					}
				}
				kn::RootedTree<int, int> g2(f2,type[i2]);
				TS_ASSERT_EQUALS(g2.size(), f2.size());
				for(int v = 0; v < size+1; v++)
					TS_ASSERT_EQUALS(g2.contains(v),f2.contains(v));
				TS_ASSERT_EQUALS(g2.isDirected(),f2.isDirected());
				TS_ASSERT_EQUALS(g2.isMutable(), type[i2]==kn::MUTABLE);
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
	}
  	
  	
  	
  	
  	void testContains( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> g(size, edges, type[i]);
			for(int j = 0; j < size; j++)
				TS_ASSERT(g.contains(j));
			TS_ASSERT(!g.contains(-1));
  			TS_ASSERT(!g.contains(size));
  		}
  	}
  	
  	
  	void testIsMutable( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			TS_ASSERT_EQUALS(g.isMutable(), type[j]==kn::MUTABLE);
		}
		
  	}
  	
  	
  	void testIsDirected( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			TS_ASSERT_EQUALS(g.isDirected(), true);
		}
				
  	}
  	
  	void testIsConnected( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			TS_ASSERT_EQUALS(g.isConnected(), true);
		}		
  	}
  	
  	  	
  	void testEdgesIterator( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			bool mark[25];
	  		std::fill(mark, mark+25,false);
	  		
	  		kn::RootedTree<int,int>::edges_iterator it = g.edges_begin(), end = g.edges_end();
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
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			kn::RootedTree<int,int>::vertices_iterator it = g.vertices_begin(), end = g.vertices_end();
			unsigned int cpt = 0;
  			for(; it!=end; it++, cpt++){
  				TS_ASSERT_EQUALS(cpt,*it);
			}
		}
  	}
  	
  	void testVerticesAccessors( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
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
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> g(size, vdatas,edges, edatas,type[i]);
			for(int j = 0; j < size; j++)
				TS_ASSERT_EQUALS(g.getVertexData(j),j);
			for(int j = 0; j < size; j++){
				g.setVertexData(j,size-j);
				TS_ASSERT_EQUALS(g.getVertexData(j),size-j);
			}
		}
  	}
  	
  	void testEdgesAccessors( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
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
		for(int i = 0; i < 4; i++){
			kn::RootedTree<int, int> g(size, vdatas,edges, edatas,type[i]);
			for(int j = 0; j < size; j++)
				for(int k = j+1; k < size; k++)
				TS_ASSERT_EQUALS(g.getEdgeData(j,k),j+k);
			for(int j = 0; j < size; j++)
			for(int k = j+1; k < size; k++){
				g.setEdgeData(j,k,k-j);
				TS_ASSERT_EQUALS(g.getEdgeData(j,k),k-j);
			}
		}
  	}
  
  
  	void testSuccessors( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 0; i < size; i++){
		  		std::vector<unsigned int> successors = g.successors(i);
				for(int j = i+1; j < size; j++){
	  				TS_ASSERT_EQUALS(std::count(successors.begin(), successors.end(), j), 1);
	  			}
	  		}
  		}
  	}
  	
  	void testPredecessors( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 0; i < size; i++){
		  		std::vector<unsigned int> predecessors = g.predecessors(i);
				for(int j = 0; j < i; j++){
	  				TS_ASSERT_EQUALS(std::count(predecessors.begin(), predecessors.end(), j), 1);
	  			}
	  		}
  		}
  	}
  	
  
  	void testInnerDegree( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
	  		for(int i = 0; i < size; i++){
				TS_ASSERT_EQUALS(g.innerDegree(i), i);
	  		}
  		}
  	}
  
  	void testMaxInnerDegree( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			TS_ASSERT_EQUALS(g.maxInnerDegree(), 1);
		}
  	}
  
  	
 	 void testOuterDegree( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
  			for(int i = 0; i < size; i++){
				TS_ASSERT_EQUALS(g.outerDegree(i), size-i-1);
  			}
  		}
  	}
  
  	void testMaxOuterDegree( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			TS_ASSERT_EQUALS(g.maxOuterDegree(), size-1);
		}
  	}
  	
  
  	void testAccessTo( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges,type[j]);
	  		for(int i = 1; i < size; i++){
				TS_ASSERT(g.accessTo(0,i));
  				TS_ASSERT(!g.accessTo(i,0));
	  		}
  		}
  	}
  	
  	void testChildren( void ){
  		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 0; i < size; i++){
		  		std::vector<unsigned int> successors = g.children(i);
				for(int j = i+1; j < size; j++){
	  				TS_ASSERT_EQUALS(std::count(successors.begin(), successors.end(), j), 1);
	  			}
	  		}
  		}
	}
	
	void testParent( void ){
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(i-1,i));
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 1; i < size; i++){
		  		TS_ASSERT_EQUALS(g.parent(i), i-1);
	  		}
  		}
	}
	
	void testAncestors( void ){
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(i-1,i));
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 1; i < size; i++){
				std::vector<unsigned int> anc = g.ancestors(i);
				for(int j = 0; j < i; j++)
		  			TS_ASSERT_EQUALS(anc[j], i-j-1);
	  		}
  		}
	}
	
	void testSiblings( void ){
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 1; i < size; i++){
				std::vector<unsigned int> sib = g.siblings(i);
				TS_ASSERT_EQUALS(sib.size(), 3);
				for(int j = 1; j < size; j++){
					if(i!=j){
						TS_ASSERT_EQUALS(std::count(sib.begin(), sib.end(), j), 1);
					}else{
						TS_ASSERT_EQUALS(std::count(sib.begin(), sib.end(), j), 0);
					}
				}
			}
		}					
	}
	
	void testHeightWithParameter( void ){
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(i-1,i));
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			for(int i = 0; i < size; i++){
		  		TS_ASSERT_EQUALS(g.height(i), i);
	  		}
  		}
	}
	
	void testHeight( void ){
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(i-1,i));
		}
		for(int k = 0; k < 4; k++){
			kn::RootedTree<int, int> g(size, edges, type[k]);
			TS_ASSERT_EQUALS(g.height(), 4);
		}
	}	
	
	void testChildrenDegree(){	
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 0; i < size; i++){
			for(int j = i+1; j < size; j++){
				edges.push_back(Edge(i,j));
			}
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
  			for(int i = 0; i < size; i++){
				TS_ASSERT_EQUALS(g.childrenDegree(i), size-i-1);
  			}
  		}
	}
	
	void testMaxChildrenDegree( void ){
		kn::GraphType type[4] = {kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
			edges.push_back(Edge(0,i));
		}
		for(int j = 0; j < 4; j++){
			kn::RootedTree<int, int> g(size, edges, type[j]);
			TS_ASSERT_EQUALS(g.maxChildrenDegree(), size-1);
		}
	}
  	
};


/*
 * End of Anti-doublon
 */
#endif
