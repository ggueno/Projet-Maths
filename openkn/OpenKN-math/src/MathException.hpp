/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MathException.hpp created in 09 2008.
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
#ifndef __OPENKN_MATH__MATHEXCEPTION_HPP__
#define __OPENKN_MATH__MATHEXCEPTION_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <exception>

/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{


  /*
   * Class definition
   */

  /** \brief Exception thrown in case of math error
   *
   */
  class MathException : public std::exception {

    /*
     * Constructor & destructors
     */
    public:
      /** \brief Constructor with error string and calling function name
       *	\param err Error string
       *	\param funcname calling function name
       */
      MathException(const std::string& err="", const std::string& funcname="");
      /** \brief Copy Constructor
       *	\param e Error to clone
       */
      MathException(const MathException & e);
      /** \brief Exception destructor
      */
      ~MathException() throw() {}

    private :
      /** \brief Concatenated error string
      */
      std::string str;
    public :
      /** \brief Getter for str
       *	\return Concatenated error string
       */
      inline std::string errorString() const {return str;}
      /** \brief Standard exception function overrinding
       *	\return Concatenated error string
       */
      virtual const char* what() const throw() {return str.c_str();}

  };

  /** \brief Operator << for MathException
   *	\param stream output stream
   *	\param err MathException to print
   *	\return output stream
   */
  inline std::ostream& operator <<(std::ostream& stream, const MathException & err){
    return stream << err.errorString();
  }


  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif
