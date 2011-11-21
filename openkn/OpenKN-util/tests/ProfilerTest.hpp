/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Profiler.hpp created in 03 2009.
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
#ifndef __OPENKN_UTIL__PROFILERTEST_HPP__
#define __OPENKN_UTIL__PROFILERTEST_HPP__

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
#include <OpenKN/util/Profiler.hpp>

/*
 * Class definition
 */
class ProfilerTest: public CxxTest::TestSuite{
	kn::Profiler * p;
public:
	void testStart() {
		p = new kn::Profiler("test.prof");	
		TS_ASSERT(p->fileName() == "test.prof");
	}

	void testTimer() {
		kn::Profiler::start("profile");
		sleep(1);
		kn::Profiler::stop("profile");

		kn::Profiler::Profile pr = p->profile("profile");
		TS_ASSERT(pr.callCount == 1);
	}

	void testSave() {
		kn::Profiler::Profile pr = p->profile("profile");
		TS_ASSERT_DELTA(pr.avTime,1.0,0.001);

		delete p;
		FILE * file = fopen("test.prof","r");
		TS_ASSERT(file);
		if (file)
			fclose(file);
	}

};

/*
 * End of Anti-doublon
 */
#endif
