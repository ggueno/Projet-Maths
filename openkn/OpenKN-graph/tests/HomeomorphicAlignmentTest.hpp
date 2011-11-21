/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HomeomorphicAlignmentTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HomeomorphicAlignmentTEST_HPP__
#define __OPENKN_GRAPH__HomeomorphicAlignmentTEST_HPP__

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
#include <OpenKN/graph/HomeomorphicAlignment.hpp>
#include <OpenKN/graph/RootedTree.hpp>
#include <OpenKN/graph/HAClassicOperators.hpp>
#include <OpenKN/graph/UndirectedGraph.hpp>

/*
 * Class definition
 */
typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class HomeomorphicAlignmentTest : public CxxTest::TestSuite {
public:
	
	
  	void testComputeRR( void ){
  		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j);
				edges.push_back(Edge(0,j));
		}
		
		kn::RootedTree<int, int> g(size, vdatas, edges,edatas, kn::BISPARSE);
		kn::HAClassicOperators<int,int> op;
		kn::HomeomorphicAlignment<int,int> ha(&g,&g,&op);
  		TS_ASSERT_EQUALS(ha.compute(), 0.0);
  		
  		int cpt = size;
  		for(int j = 1; j < size; j++){
  			for(int v = 0; v < 4; v++){
  				vdatas.push_back(1);
				edatas.push_back(1);
				edges.push_back(Edge(j,cpt++));
			}
		}
		kn::RootedTree<int, int> g2(size+4*(size-1), vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> ha2(&g,&g2,&op);
  		TS_ASSERT_EQUALS(ha2.compute(), 0.0);
  		
  		kn::HAClassicOperators<int,int> op2(false, false);
  		kn::HomeomorphicAlignment<int,int> ha3(&g,&g2,&op2);
  		TS_ASSERT_EQUALS(ha3.compute(), 4*(size-1));
  		
  		
  		kn::HAClassicOperators<int,int> op3(true, false);
  		kn::HomeomorphicAlignment<int,int> ha4(&g2,&g,&op3);
  		TS_ASSERT_EQUALS(ha4.compute(), 0.0);
  		
  		vdatas.clear();
		edatas.clear();
		edges.clear();
		for(int i = 0; i < size*2-1; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j-1);
				edges.push_back(Edge(0,j));
				edatas.push_back(1);
				edges.push_back(Edge(j,j+size-1));	
		}
  		kn::RootedTree<int, int> gh(size*2-1, vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> hah(&g,&gh,&op2);
  		TS_ASSERT_EQUALS(hah.compute(), 0.0);
  		
  	}
  	
  	void testComputeUU( void ){
  		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j);
				edges.push_back(Edge(0,j));
		}
		
		kn::UndirectedGraph<int, int> g(size, vdatas, edges,edatas, kn::BISPARSE);
		kn::HAClassicOperators<int,int> op;
		kn::HomeomorphicAlignment<int,int> ha(&g,&g,&op);
  		TS_ASSERT_EQUALS(ha.compute(), 0.0);
  		
  		int cpt = size;
  		for(int j = 1; j < size; j++){
  			for(int v = 0; v < 4; v++){
  				vdatas.push_back(1);
				edatas.push_back(1);
				edges.push_back(Edge(j,cpt++));
			}
		}
		kn::UndirectedGraph<int, int> g2(size+4*(size-1), vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> ha2(&g,&g2,&op);
  		TS_ASSERT_EQUALS(ha2.compute(), 0.0);
  		
  		kn::HAClassicOperators<int,int> op2(false, false);
  		kn::HomeomorphicAlignment<int,int> ha3(&g,&g2,&op2);
  		TS_ASSERT_EQUALS(ha3.compute(), 4*(size-1));
  		
  		
  		kn::HAClassicOperators<int,int> op3(true, false);
  		kn::HomeomorphicAlignment<int,int> ha4(&g2,&g,&op3);
  		TS_ASSERT_EQUALS(ha4.compute(), 0.0);
  		
  		vdatas.clear();
		edatas.clear();
		edges.clear();
		for(int i = 0; i < size*2-1; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j-1);
				edges.push_back(Edge(0,j));
				edatas.push_back(1);
				edges.push_back(Edge(j,j+size-1));	
		}
  		kn::UndirectedGraph<int, int> gh(size*2-1, vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> hah(&g,&gh,&op2);
  		TS_ASSERT_EQUALS(hah.compute(), 0.0);
  	}
  	
  	
  	void testComputeUR( void ){
  		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j);
				edges.push_back(Edge(0,j));
		}
		
		kn::UndirectedGraph<int, int> g(size, vdatas, edges,edatas, kn::BISPARSE);
		kn::RootedTree<int, int> g2(size, vdatas, edges,edatas, kn::BISPARSE);
		kn::HAClassicOperators<int,int> op;
		kn::HomeomorphicAlignment<int,int> ha(&g,&g2,&op);
  		TS_ASSERT_EQUALS(ha.compute(), 0.0);
  		
  		int cpt = size;
  		for(int j = 1; j < size; j++){
  			for(int v = 0; v < 4; v++){
  				vdatas.push_back(1);
				edatas.push_back(1);
				edges.push_back(Edge(j,cpt++));
			}
		}
		
		kn::RootedTree<int, int> g3(size+4*(size-1), vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> ha2(&g,&g3,&op);
  		TS_ASSERT_EQUALS(ha2.compute(), 0.0);
  		
  		kn::HAClassicOperators<int,int> op2(false, false);
  		kn::HomeomorphicAlignment<int,int> ha3(&g,&g3,&op2);
  		TS_ASSERT_EQUALS(ha3.compute(), 4*(size-1));
  		
  		kn::UndirectedGraph<int, int> g4(size+4*(size-1), vdatas, edges,edatas, kn::BISPARSE);
  		kn::HAClassicOperators<int,int> op3(true, false);
  		kn::HomeomorphicAlignment<int,int> ha4(&g4,&g2,&op3);
  		TS_ASSERT_EQUALS(ha4.compute(), 0.0);
  		
  		vdatas.clear();
		edatas.clear();
		edges.clear();
		for(int i = 0; i < size*2-1; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j-1);
				edges.push_back(Edge(0,j));
				edatas.push_back(1);
				edges.push_back(Edge(j,j+size-1));	
		}
  		kn::RootedTree<int, int> gh(size*2-1, vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> hah(&g,&gh,&op2);
  		TS_ASSERT_EQUALS(hah.compute(), 0.0);
  	}
  	
  	void testComputeRU( void ){
  		int size = 5;
		EdgeSet edges;
		std::vector<int> vdatas;
		std::vector<int> edatas;
		for(int i = 0; i < size; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j);
				edges.push_back(Edge(0,j));
		}
		
		kn::UndirectedGraph<int, int> g(size, vdatas, edges,edatas, kn::BISPARSE);
		kn::RootedTree<int, int> g2(size, vdatas, edges,edatas, kn::BISPARSE);
		kn::HAClassicOperators<int,int> op;
		kn::HomeomorphicAlignment<int,int> ha(&g2,&g,&op);
  		TS_ASSERT_EQUALS(ha.compute(), 0.0);
  		
  		int cpt = size;
  		for(int j = 1; j < size; j++){
  			for(int v = 0; v < 4; v++){
  				vdatas.push_back(1);
				edatas.push_back(1);
				edges.push_back(Edge(j,cpt++));
			}
		}
  		kn::UndirectedGraph<int, int> g3(size+4*(size-1), vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> ha2(&g,&g3,&op);
  		TS_ASSERT_EQUALS(ha2.compute(), 0.0);
  		
  		kn::HAClassicOperators<int,int> op2(false, false);
  		kn::HomeomorphicAlignment<int,int> ha3(&g,&g3,&op2);
  		TS_ASSERT_EQUALS(ha3.compute(), 4*(size-1));
  		
  		kn::RootedTree<int, int> g4(size+4*(size-1), vdatas, edges,edatas, kn::BISPARSE);
  		kn::HAClassicOperators<int,int> op3(true, false);
  		kn::HomeomorphicAlignment<int,int> ha4(&g4,&g2,&op3);
  		TS_ASSERT_EQUALS(ha4.compute(), 0.0);
  		
  		vdatas.clear();
		edatas.clear();
		edges.clear();
		for(int i = 0; i < size*2-1; i++){
			vdatas.push_back(i);
			
		}
		for(int j = 1; j < size; j++){
				edatas.push_back(j-1);
				edges.push_back(Edge(0,j));
				edatas.push_back(1);
				edges.push_back(Edge(j,j+size-1));	
		}
  		kn::UndirectedGraph<int, int> gh(size*2-1, vdatas, edges,edatas, kn::BISPARSE);
		kn::HomeomorphicAlignment<int,int> hah(&g,&gh,&op2);
  		TS_ASSERT_EQUALS(hah.compute(), 0.0);
  	}
  	
};


/*
 * End of Anti-doublon
 */
#endif
