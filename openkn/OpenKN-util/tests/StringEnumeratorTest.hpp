/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * StringEnumerator.hpp created in 03 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-util.
 *
 * The OpenKraken-util is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-util is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_UTIL__STRINGENUMERATORTEST_HPP__
#define __OPENKN_UTIL__STRINGENUMERATORTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/util/StringEnumerator.hpp>

/*
 * Class definition
 */
class StringEnumeratorTest: public CxxTest::TestSuite{
  public:

    void testStringEnumerator(void){
    	int random_digitcard = rand()%8;
    	int number_max_value = pow(10, rand()%random_digitcard);
    	int random_number = rand()%number_max_value;
    	std::string result = kn::stringEnumerator("filename", random_number, random_digitcard, ".ext");
    	
    	std::ostringstream oss;
    	oss<<random_number;
    	int random_number_nb_digits = oss.str().length();
    	int nb_zeros = random_digitcard-random_number_nb_digits;
    	
    	TS_ASSERT(result.length()==8+random_digitcard+4);
    	TS_ASSERT(!result.substr(0, 8).compare("filename"));
    	for(unsigned int pos=8; pos<8+nb_zeros; pos++)
    		TS_ASSERT(result[pos]=='0');
    	TS_ASSERT(!result.substr(8+nb_zeros, random_number_nb_digits).compare(oss.str()));
    	TS_ASSERT(!result.substr(8+nb_zeros+random_number_nb_digits).compare(".ext"));
    }
};

/*
 * End of Anti-doublon
 */
#endif
