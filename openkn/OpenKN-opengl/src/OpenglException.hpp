/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * OpenglException.hpp created in 2 2009.
 * Mail : biri@univ-mlv.fr                    
 *                                                     
 * This file is part of the OpenKN-opengl.
 *
 * The OpenKN-opengl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKN-opengl is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_OPENGL__OPENGLEXCEPTION_HPP__
#define __OPENKN_OPENGL__OPENGLEXCEPTION_HPP__

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
namespace kn {
	/*
	 * Class definition
	 */
	/** \brief Exception thrown in case of opengl error
	 *
	 */
	class OpenglException : std::exception {

		/*
			* Constructor & destructors
			*/
	public:
		/** \brief Constructor with error string and calling function name
			*  \param err Error string
			*  \param funcname calling function name
			*/
		OpenglException(const std::string& err="", const std::string& funcname="");
		/** \brief Copy Constructor
			*  \param e Error to clone
			*/
		OpenglException(const OpenglException & e);
		/** \brief Exception destructor
		 */
		~OpenglException() throw() {}			

      
	private :
		/** \brief Concatenated error string
			*/
		std::string str;
	public :
		/** \brief Getter for str
			*  \return Concatenated error string
			*/
		inline std::string errorString() const {return str;}
		/** \brief Standard exception function overrinding
		 *	\return Concatenated error string
		 */
		virtual const char* what() const throw() {return str.c_str();}
	};

	/** \brief Operator << for OpenglException
	 *  \param stream output stream
	 *  \err OpenglException to print
	 *  \return output stream
	 */
	inline std::ostream& operator <<(std::ostream& stream, const OpenglException & err){
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
