/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RankTest.hpp created in 02 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__RANKTEST_HPP__
#define __OPENKN_MATH__RANKTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Rank.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/MathIO.hpp>

/*
 * Class definition
 */
class RankTest: public CxxTest::TestSuite{
  public:

    void testRank(void){
      kn::Matrix<double> A4x4;
      kn::loadMatrix(A4x4,"input/matrix_rank1.mat");
      TS_ASSERT_EQUALS(kn::rank(A4x4),(int)1);

      kn::loadMatrix(A4x4,"input/matrix_rank2.mat");
      TS_ASSERT_EQUALS(kn::rank(A4x4),(int)2);

      kn::loadMatrix(A4x4,"input/matrix_rank3.mat");
      TS_ASSERT_EQUALS(kn::rank(A4x4),(int)3);

      kn::loadMatrix(A4x4,"input/matrix_rank4.mat");
      TS_ASSERT_EQUALS(kn::rank(A4x4),(int)4);

      kn::Matrix<double> A10x5;
      kn::loadMatrix(A10x5,"input/matrix_rank5.mat");
      TS_ASSERT_EQUALS(kn::rank(A10x5),(int)5);

      kn::Matrix<double> A6x10;
      kn::loadMatrix(A6x10,"input/matrix_rank6.mat");
      TS_ASSERT_EQUALS(kn::rank(A6x10),(int)6);
    }

};


/*
 * End of Anti-doublon
 */
#endif
