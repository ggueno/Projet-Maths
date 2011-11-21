/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MathTools.hpp created in 10 2008.
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
#ifndef __OPENKN_MATH__MATHTOOLS_HPP__
#define __OPENKN_MATH__MATHTOOLS_HPP__

namespace kn{

  /**
   * \brief PI
   */
  static const double PI = 3.14159265358979323846;

  /**
   * \brief 2*PI
   */
  static const double TWO_PI = 6.28318530717958647692;

  /**
   * \brief PI/2
   */
  static const double PI_TWO = 1.57079632679489661923;

  /**
   * \brief PI/4
   */
  static const double PI_FOUR = 0.78539816339744830962;

  /**
   * \brief Convertion factor from degrees to radians
   */
  static const double DEG2RAD = 0.01745329251994329576;

  /**
   * \brief Convertion factor from radians to degrees
   */
  static const double RAD2DEG = 57.2957795130823208767;

  /**
   * \brief The golden number (1+sqrt(5))/2
   */
  static const double GOLDEN_NUMBER = 1.61803398874989484820;

  /**
   * \brief Convert degrees to radians
   * \param deg value in degrees
   * \return value in radians
   */
  static double degToRad(const double& deg) { return deg*DEG2RAD; }

  /**
   * \brief Convert radians to degrees
   * \param rad value in radians
   * \return value in degrees
   */
  static double radToDeg(const double& rad) { return rad*RAD2DEG; }


  /**
   * \brief Computes (a^2 + b^2)^1/2 without destructive underflow or overflow
   * Algorithm from Numerical Recipes Second Edition (1992)
   * \param a first value
   * \param b second value
   * \return (a^2 + b^2)^1/2
   */
  static double pythag(const double &a, const double &b) {
    double absa,absb;

    absa = std::fabs(a);
    absb = std::fabs(b);

    if(absa > absb) return	absa*std::sqrt(1.0+(absb/absa)*(absb/absa));
    else return (absb == 0.0 ? 0.0 :absb*std::sqrt(1.0+(absa/absb)*(absa/absb)));
  }

  /**
   * \brief set a with the same sign than b
   * \param a the value which the sign will be modified to the sign of b
   * \param b the value which we get the sign
   * \return the value b with the modified sign
   */
  template<class T> static T setSign(const T& a, const T& b){
    return b>=T(0)?T(std::fabs(a)):-T(std::fabs(a));
  }

  /**
   * \brief Return the sign of a
   * \param a the value from which we need the sign
   * \return the sign
   */
  template<class T> static T getSign(const T& a){
    if(a==T(0))return a;
    return a>T(0)?T(1):T(-1);
  }

  /**
   * \brief check if n is a power of two or not
   * \param n the tested value
   * \return true if n is a power of two, false otherwise
   */
  static inline bool isPowerOfTwo(const unsigned int& n){
    return (n & (n - 1)) == 0 && n > 0;
  }


  /**
   * \brief Return the highest power of two value close to n
   * \param n the reference value
   * \return the closest highest power of two value
   */
  static inline unsigned int ceilPowerOfTwo(const unsigned int& n)
  {
    int tmpn = n;
    --tmpn;
    tmpn |= tmpn >> 1;
    tmpn |= tmpn >> 2;
    tmpn |= tmpn >> 4;
    tmpn |= tmpn >> 8;
    tmpn |= tmpn >> 16;
    ++tmpn;
    return tmpn;
  }

  /**
   * \brief Return the lowest power of two value close to n
   * \param n the reference value
   * \return the closest lowest power of two value
   */
  static inline unsigned int floorPowerOfTwo(const unsigned int& n){
    return ceilPowerOfTwo(n) >> 1;
  }
}

#endif
