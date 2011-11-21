/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MorphotopoExceptionTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-morphotopo.
 *
 * The OpenKraken-morphotopo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-morphotopo is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_MORPHOTOPO__MORPHOTOPOEXCEPTIONTEST_HPP__
#define __OPENKN_MORPHOTOPO__MORPHOTOPOEXCEPTIONTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/morphotopo/MorphotopoException.hpp>

/*
 * Class definition
 */

class MorphotopoExceptionTest : public CxxTest::TestSuite {
public:
	void testConstructorWithTwoParameters( void ) {
		kn::MorphotopoException e("World!","Hello,");
		TS_ASSERT_EQUALS( e.errorString(), "(Hello,) Error : World!");
	}
  void testOperatorChev( void ) {
	  kn::MorphotopoException e("World!","Hello,");
	  std::stringstream sstr;
	  std::string strref="(Hello,) Error : World!";
	  sstr << e;
	  TS_ASSERT_EQUALS( sstr.str() , strref);
  }
};


/*
 * End of Anti-doublon
 */
#endif
