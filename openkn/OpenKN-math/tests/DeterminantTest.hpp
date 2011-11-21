/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * DeterminantTest.hpp created in 02 2009.
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
#ifndef __OPENKN_MATH__DETERMINANTTEST_HPP__
#define __OPENKN_MATH__DETERMINANTTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Determinant.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/MathIO.hpp>

/*
 * Class definition
 */
class DeterminantTest: public CxxTest::TestSuite{
  public:

    void testDeterminant3x3(void){
      double tabvaluesd[3*3] = {5.0, 3.0, 7.0,
				2.0, 4.0, 9.0,
				3.0, 6.0, 4.0};

      kn::Matrix<double> aDouble(3,3,tabvaluesd);

      TS_ASSERT(kn::determinant3x3(aDouble) == -133.0);

      kn::Matrix3x3d a3x3Double(tabvaluesd);

      TS_ASSERT(kn::determinant3x3(a3x3Double) == -133.0);
    }


    void testDeterminant3x3BadSize(void){
      kn::Matrix<double> a(3,4);
      TS_ASSERT_THROWS(kn::determinant3x3(a),
		       kn::MathException);
    }


    void testDeterminant(void){
      kn::Matrix<double> A4x4;
      kn::loadMatrix(A4x4,"input/matrix_rank3.mat");
      TS_ASSERT_DELTA(fabs(kn::determinant(A4x4)), 0.0, 1.0e-10);

      kn::loadMatrix(A4x4,"input/matrix_rank1.mat");
      TS_ASSERT_DELTA(fabs(kn::determinant(A4x4)), 0.0, 1.0e-10);

      kn::loadMatrix(A4x4,"input/matrix_det_77.mat");
      TS_ASSERT_DELTA(fabs(kn::determinant(A4x4)), 77.0, 1.0e-10);
    }

};







/*
 * End of Anti-doublon
 */
#endif
