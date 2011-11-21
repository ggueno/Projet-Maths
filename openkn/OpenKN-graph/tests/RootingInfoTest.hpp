/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * RootingInfoTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__ROOTINGINFOTEST_HPP__
#define __OPENKN_GRAPH__ROOTINGINFOTEST_HPP__

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
#include <OpenKN/graph/RootingInfo.hpp>
#include <OpenKN/graph/DenseGraphStruct.hpp>
#include <OpenKN/graph/SparseGraphStruct.hpp>
#include <OpenKN/graph/BiSparseGraphStruct.hpp>
#include <OpenKN/graph/MutableGraphStruct.hpp>

/*
 * Class definition
 */

typedef std::pair<unsigned int, unsigned int> Edge;
typedef std::vector<Edge> EdgeSet;


class RootingInfoTest : public CxxTest::TestSuite {
public:
	
	void testParent( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			for(int r = 0; r < size; r++)
				for(int v = 0; v < size; v++){
					if(v == r){
						TS_ASSERT_EQUALS(rt.parent(v,r), v);
					}else if(r == 0){
						TS_ASSERT_EQUALS(rt.parent(v,r), 0);	
					}else if(v == 0){
						TS_ASSERT_EQUALS(rt.parent(v,r), r);
					}else{
						TS_ASSERT_EQUALS(rt.parent(v,r), 0);
					}
				}
		}
	}
	
	
  	void testAncestors( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			for(int r = 0; r < size; r++)
				for(int v = 0; v < size; v++){
					std::vector<unsigned int> anc = rt.ancestors(v,r);
					if(v == r){
						TS_ASSERT_EQUALS(anc.size(), 0);
					}else if(r == 0 || v == 0){
						TS_ASSERT_EQUALS(anc.size(), 1);
						TS_ASSERT_EQUALS(anc[0],r);	
					}else{
						TS_ASSERT_EQUALS(anc.size(), 2);
						TS_ASSERT_EQUALS(anc[0], 0);
						TS_ASSERT_EQUALS(anc[1], r);
					}
				}
		}
	}
	
	
	
	void testChildren( void ) {
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			for(int r = 0; r < size; r++)
				for(int v = 0; v < size; v++){
					std::vector<unsigned int> ch = rt.children(v,r);
					if(v == 0){
						for(int c = 1; c < size; c++){
							if(c == r){
								TS_ASSERT_EQUALS(std::count(ch.begin(),ch.end(),c),0);
							}else{
								TS_ASSERT_EQUALS(std::count(ch.begin(),ch.end(),c),1);
							}
						}
					}else if(v == r){
						TS_ASSERT_EQUALS(ch.size(),1);
						TS_ASSERT_EQUALS(ch[0], 0);
					}else{
						TS_ASSERT_EQUALS(ch.size(),0);
					}
				}
		}
	}
	
	
	void testHeightWithOneParameter( void ){
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			TS_ASSERT_EQUALS(rt.height(0),1);
			for(int j = 1; j < size; j++){
				TS_ASSERT_EQUALS(rt.height(j),2);
			}
		}
	}	
	
	void testHeightWithTwoParameters( void ){
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			
			TS_ASSERT_EQUALS(rt.height(0,0),0);
			for(int v = 1; v < size; v++)
				TS_ASSERT_EQUALS(rt.height(v,0),1);
			
			for(int r = 1; r < size; r++){
				TS_ASSERT_EQUALS(rt.height(0,r),1);
				for(int v = 1; v < size; v++){
					if(v == r){
						TS_ASSERT_EQUALS(rt.height(v,r),0);	
					}else{
						TS_ASSERT_EQUALS(rt.height(v,r),2);
					}
				}
			}
		}
	}	


	void testChildrenDegree( void ){
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			TS_ASSERT_EQUALS(rt.childrenDegree(0,0), size-1);
			for(int v = 1; v < size; v++)
				TS_ASSERT_EQUALS(rt.childrenDegree(v,0),0);
			
			for(int r = 1; r < size; r++){
				TS_ASSERT_EQUALS(rt.childrenDegree(0,r),size-2);
				for(int v = 1; v < size; v++){
					if(v == r){
						TS_ASSERT_EQUALS(rt.childrenDegree(v,r),1);	
					}else{
						TS_ASSERT_EQUALS(rt.childrenDegree(v,r),0);
					}
				}
			}
		}
	}

	void testMaxChildrenDegree( void ){
		int size = 5;
		EdgeSet edges;
		for(int i = 1; i < size; i++){
				edges.push_back(Edge(0,i));
		}
		kn::GraphStruct* g[4] = {new kn::DenseGraphStruct(size, edges,false), 
					new kn::SparseGraphStruct(size, edges,false),
					new kn::BiSparseGraphStruct(size, edges,false),
					new kn::MutableGraphStruct(size, edges,false)};
		
		for(int i = 0; i < 4; i++){
			kn::RootingInfo rt = kn::RootingInfo(g[i]);
			TS_ASSERT_EQUALS(rt.maxChildrenDegree(), size-1);
		}
	}
};



/*
 * End of Anti-doublon
 */
#endif
