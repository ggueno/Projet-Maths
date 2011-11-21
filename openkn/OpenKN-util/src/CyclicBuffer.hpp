/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * CyclicBuffer.hpp created in 07 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-util.
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
#ifndef __OPENKN_UTIL__CYCLICBUFFER_HPP__
#define __OPENKN_UTIL__CYCLICBUFFER_HPP__

/*
 * External Includes
 */

/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn {

  /*
   * Class definition
   */

  /**
   * \brief class to manipulate a cyclic buffer
   */
  template<class T> class CyclicBuffer {

  protected:
  public:
    
    /*
     * Constructor
       */
    CyclicBuffer (){}
    /*
       * Destructor
       */
    
    /**
     * \brief Destructor
       */
    virtual ~(void);
  };
  
  template<typename T>
  CyclicBuffer<T>::CyclicBuffer(){}
  
  template<typename T>
  CyclicBuffer<T>::~CyclicBuffer(){}
  
  /*
 * End of Anti-doublon
 */
#endif
