/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * SubsetTest.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__SUBSETTEST_HPP__
#define __OPENKN_GRAPH__SUBSETTEST_HPP__

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
#include <OpenKN/graph/Subset.hpp>
/*
 * Class definition
 */


class SubsetTest : public CxxTest::TestSuite {
public:
	
	
  	void testIsSubset( void ){
  		kn::Subset subset(0);
  		TS_ASSERT(subset.isSubset(1, 3));
  		TS_ASSERT(!subset.isSubset(1, 4));
  		TS_ASSERT(subset.isSubset(1, 5));
  		TS_ASSERT(subset.isSubset(5, 7));
  	}
  	void testNextSubsetIndex( void ){
  		kn::Subset subset(0);
  		unsigned int s = subset.nextSubsetIndex(0,9);
  		TS_ASSERT_EQUALS(s,1);
  		s = subset.nextSubsetIndex(s,9);
  		TS_ASSERT_EQUALS(s,8);
  		s = subset.nextSubsetIndex(0,14);
  		TS_ASSERT_EQUALS(s,2);
  		s = subset.nextSubsetIndex(s,14);
  		TS_ASSERT_EQUALS(s,4);
  		s = subset.nextSubsetIndex(s,14);
  		TS_ASSERT_EQUALS(s,6);
  	}
  
  	void testGetSubset( void ){
		kn::Subset subset(3);
  		std::vector<unsigned char> s = subset.getSubset(14);
  		TS_ASSERT_EQUALS(s.size(),3);
  		TS_ASSERT_EQUALS(s[0], 1);
  		TS_ASSERT_EQUALS(s[1], 2);
  		TS_ASSERT_EQUALS(s[2], 3);
  		s = subset.getSubset(13);
  		TS_ASSERT_EQUALS(s.size(),3);
  		TS_ASSERT_EQUALS(s[0], 0);
  		TS_ASSERT_EQUALS(s[1], 2);
  		TS_ASSERT_EQUALS(s[2], 3);
  	}
  	
  	void testComplement( void ){
  		kn::Subset subset(0);
  		TS_ASSERT_EQUALS(subset.complement(4,14), 10);
  		TS_ASSERT_EQUALS(subset.complement(0,14), 14);
  		TS_ASSERT_EQUALS(subset.complement(14,14), 0);
  		TS_ASSERT_EQUALS(subset.complement(4,15), 11);
  		
	}
	void testSet( void ){
		kn::Subset subset(0);
  		TS_ASSERT_EQUALS(subset.set(4),15);
  		TS_ASSERT_EQUALS(subset.set(2),3); 
	}
  	
  	void testSetWithoutParia( void ){
		kn::Subset subset(0);
  		TS_ASSERT_EQUALS(subset.setWithoutParia(15, 2),11);
  		TS_ASSERT_EQUALS(subset.setWithoutParia(15, 0),14);
  		TS_ASSERT_EQUALS(subset.setWithoutParia(15, 3),7);
	}
	
	
	void testGetNextElement( void ){
		kn::Subset subset(0);
		TS_ASSERT_EQUALS(subset.getNextElement(-1, 14), 1);
		TS_ASSERT_EQUALS(subset.getNextElement(1, 14), 2);
		TS_ASSERT_EQUALS(subset.getNextElement(2, 14), 3);
		TS_ASSERT_EQUALS(subset.getNextElement(3, 14), -1);
	}
  	
};


/*
 * End of Anti-doublon
 */
#endif
