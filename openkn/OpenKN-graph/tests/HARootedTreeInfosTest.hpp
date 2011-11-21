/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HARootedTreeInfosTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HAROOTEDTREEINFOSTEST_HPP__
#define __OPENKN_GRAPH__HAROOTEDTREEINFOSTEST_HPP__

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
#include <OpenKN/graph/HARootedTreeInfos.hpp>
#include <OpenKN/graph/DenseGraphStruct.hpp>
#include <OpenKN/graph/SparseGraphStruct.hpp>
#include <OpenKN/graph/BiSparseGraphStruct.hpp>
#include <OpenKN/graph/MutableGraphStruct.hpp>

/*
 * Class definition
 */

typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class HARootedTreeInfosTest : public CxxTest::TestSuite {
public:
	
	void testConstructorAndWeights( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT(ti.isRooted());
			for(int i = 1; i < 2; i++){
				TS_ASSERT_EQUALS(ti.pathWeight(0,i), 1);
			}
			for(int i = 3; i < size; i++){
				TS_ASSERT_EQUALS(ti.pathWeight(0,i),2);
				TS_ASSERT_EQUALS(ti.pathWeight(i%2==0?2:1,i),1);
			}
		}
	}
	
	
	void testParent( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT_EQUALS(ti.parent(0,0), 0);
			for(int i = 1; i < 2; i++){
				TS_ASSERT_EQUALS(ti.parent(i,0), 0);
			}
			for(int i = 3; i < size; i++){
				TS_ASSERT_EQUALS(ti.parent(i,0),i%2==0?2:1);
			}
		}
	}
	
	void testAncestors( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT_EQUALS(ti.ancestors(0,0).size(), 0);
			for(int i = 1; i < 2; i++){
				std::vector<unsigned int> anc = ti.ancestors(i,0);
				TS_ASSERT_EQUALS(anc.size(),1);
				TS_ASSERT_EQUALS(anc[0], 0);
			}
			for(int i = 3; i < size; i++){
				std::vector<unsigned int> anc = ti.ancestors(i,0);
				TS_ASSERT_EQUALS(anc.size(),2);
				TS_ASSERT_EQUALS(anc[0], i%2==0?2:1);
				TS_ASSERT_EQUALS(anc[1], 0);
			}
		}
	}
  	
  	void testChildren( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			std::vector<unsigned int> ch = ti.children(0,0);
			TS_ASSERT_EQUALS(ch.size(), 2);
			for(int i = 1; i < 2; i++){
				std::vector<unsigned int> ch = ti.children(i,0);
				for(int j = 3; j < size; j++){
					if(j%2!=i-1){
						TS_ASSERT(std::binary_search(ch.begin(),ch.end(),j));
					}else{
						TS_ASSERT(!std::binary_search(ch.begin(),ch.end(),j));
					}
				}
			}
			for(int i = 3; i < size; i++){
				std::vector<unsigned int> ch = ti.children(i,0);
				TS_ASSERT_EQUALS(ch.size(),0);
			}
		}
	}
	
	void testSize( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT_EQUALS(ti.size(),size);
		}
	}
	
	void testHeight( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT_EQUALS(ti.height(),2);
		}
	}
	
	void testDegree( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		int degree = (size-3);
		if(degree%2==1)degree=degree/2+1;
		else degree/=2;
		
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT_EQUALS(ti.degree(),degree);
		}
	}
		
		
	void testNavigationOrder( void ) {
		kn::GraphType type[4]={kn::DENSE, kn::SPARSE, kn::BISPARSE, kn::MUTABLE};
		int size = 10;
		EdgeSet edges;
		std::vector<int> edatas(size-1,1);
		std::vector<bool> vdatas(size,false);
		for(int i = 1; i < 3; i++){
			edges.push_back(Edge(0,i));
		}
		for(int i = 3; i < size; i++){
			edges.push_back(Edge(i%2==0?2:1,i));
		}
		int degree = (size-3);
		if(degree%2==1)degree=degree/2+1;
		else degree/=2;
		
		
		for(int i = 0; i < 4; i++){
			kn::RootedTree<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HARootedTreeInfos<bool, int> ti(&rt);
			std::vector<std::pair<unsigned int, unsigned int> > order = ti.navigationOrder();
			std::vector<std::pair<unsigned int, unsigned int> >::iterator pos;
					
			for(unsigned int l = 3; l < size; l++){
				unsigned int par = ti.parent(l,0);
				unsigned int gpar = ti.parent(par, 0);
				pos = std::find(order.begin(), order.end(), std::make_pair(l, par));
				while(par != gpar){
					pos = std::find(pos, order.end(), std::make_pair(par, gpar));
					TS_ASSERT_DIFFERS(pos, order.end());
					par = gpar;
					gpar = ti.parent(par, 0);
				}
			}
		}
	}
};



/*
 * End of Anti-doublon
 */
#endif
