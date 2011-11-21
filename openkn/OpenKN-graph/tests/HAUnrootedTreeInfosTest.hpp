/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HAUnrootedTreeInfosTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HAUnrootedTREEINFOSTEST_HPP__
#define __OPENKN_GRAPH__HAUnrootedTREEINFOSTEST_HPP__

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
#include <OpenKN/graph/HAUnrootedTreeInfos.hpp>
#include <OpenKN/graph/DenseGraphStruct.hpp>
#include <OpenKN/graph/SparseGraphStruct.hpp>
#include <OpenKN/graph/BiSparseGraphStruct.hpp>
#include <OpenKN/graph/MutableGraphStruct.hpp>
#include <OpenKN/graph/UndirectedGraph.hpp>

/*
 * Class definition
 */

typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class HAUnrootedTreeInfosTest : public CxxTest::TestSuite {
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT(!ti.isRooted());
			for(int i = 0; i < size; i++){
				for(int j = i+1; j < size; j++){	
					if(i == 0){
						if(j < 3){
							TS_ASSERT_EQUALS(ti.pathWeight(i,j), 1);
							TS_ASSERT_EQUALS(ti.pathWeight(j,i), 1);	
						}else{
							TS_ASSERT_EQUALS(ti.pathWeight(i,j), 2);
							TS_ASSERT_EQUALS(ti.pathWeight(j,i), 2);
						}
										
					}else if(i < 3){
						if(j < 3){
							TS_ASSERT_EQUALS(ti.pathWeight(i,j), 2);
							TS_ASSERT_EQUALS(ti.pathWeight(j,i), 2);
						}else{
							TS_ASSERT_EQUALS(ti.pathWeight(i,j), j%2!=i-1?1:3);
							TS_ASSERT_EQUALS(ti.pathWeight(j,i), j%2!=i-1?1:3);
						}
					}else{
						if(ti.parent(i,0) == ti.parent(j,0)){
							TS_ASSERT_EQUALS(ti.pathWeight(i,j), 2);
							TS_ASSERT_EQUALS(ti.pathWeight(j,i), 2);
						}else{
							TS_ASSERT_EQUALS(ti.pathWeight(i,j), 4);
							TS_ASSERT_EQUALS(ti.pathWeight(j,i), 4);
						}
					}
				}
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
			for(unsigned int r = 0; r < size; r++){
				for(unsigned int v = 0; v < size; v++){
					if(r == v){	
						TS_ASSERT_EQUALS(ti.parent(v,r), v);
					}else if(r == 0){
						if(v < 3){
							TS_ASSERT_EQUALS(ti.parent(v,r), 0);
						}else{
							TS_ASSERT_EQUALS(ti.parent(v,r), v%2==0?2:1);
						}
					}else if(r < 3){
						if(v == 0 || v%2 != r-1){
							TS_ASSERT_EQUALS(ti.parent(v,r), r);
						}else if(v < 3){
							TS_ASSERT_EQUALS(ti.parent(v,r), 0);
						}else{
							TS_ASSERT_EQUALS(ti.parent(v,r), r==1?2:1);
						}		
					}else{
						if(v == 0){
							TS_ASSERT_EQUALS(ti.parent(v,r), r%2==0?2:1);
						}else if(v < 3){
							if(v%2 == r%2){
								TS_ASSERT_EQUALS(ti.parent(v,r), r);
							}else{
								TS_ASSERT_EQUALS(ti.parent(v,r), 0);
							}
						}else{
							if(v%2 == r%2){
								TS_ASSERT_EQUALS(ti.parent(v,r), v%2==0?2:1);
							}else{
								TS_ASSERT_EQUALS(ti.parent(v,r), r%2!=0?2:1);
							}
						}
					}
				}
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
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
			std::vector<unsigned int> anc = ti.ancestors(5,4);
			TS_ASSERT_EQUALS(anc.size(),4);
			TS_ASSERT_EQUALS(anc[0],1);
			TS_ASSERT_EQUALS(anc[1],0);
			TS_ASSERT_EQUALS(anc[2],2);
			TS_ASSERT_EQUALS(anc[3],4);
			anc = ti.ancestors(6,4);
			TS_ASSERT_EQUALS(anc.size(),2);
			TS_ASSERT_EQUALS(anc[0],2);
			TS_ASSERT_EQUALS(anc[1],4);
			
			
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
			TS_ASSERT_EQUALS(ti.height(),4);
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
		if(degree%2==1)degree=degree/2+2;
		else degree=degree/2+1;
		
		for(int i = 0; i < 4; i++){
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
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
			kn::UndirectedGraph<bool, int> rt(size, vdatas, edges, edatas,type[i]);
			kn::HAUnrootedTreeInfos<bool, int> ti(&rt);
			std::vector<std::pair<unsigned int, unsigned int> > order = ti.navigationOrder();
			TS_ASSERT_EQUALS(order.size(), edatas.size()*2+vdatas.size());
			std::vector<std::pair<unsigned int, unsigned int> >::iterator pos;
			for(unsigned int r = 0; r < size; r++){		
				for(unsigned int l = 3; l < size; l++){
					if(l == r) continue;
					unsigned int par = ti.parent(l,r);
					unsigned int gpar = ti.parent(par, r);
					pos = std::find(order.begin(), order.end(), std::make_pair(l, par));
					while(par != gpar){
						pos = std::find(pos, order.end(), std::make_pair(par, gpar));
						TS_ASSERT_DIFFERS(pos, order.end());
						par = gpar;
						gpar = ti.parent(par, r);
					}
				}
			}
		}
	}
};



/*
 * End of Anti-doublon
 */
#endif
