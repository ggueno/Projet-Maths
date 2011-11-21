/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MorphotopoException.hpp created in 9 2009.
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
#ifndef __OPENKN_MORPHOTOPO__MORPHOTOPOEXCEPTION_HPP__
#define __OPENKN_MORPHOTOPO__MORPHOTOPOEXCEPTION_HPP__

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

	/** \brief Exception thrown in case of morphotopo error
	 *
	 */
	class MorphotopoException : std::exception {

		/*
		 * Constructor & destructors
		 */		 
	public:
		/** \brief Constructor with error string and calling function name
		 *	\param err Error string
		 *	\param funcname calling function name
		 */
		MorphotopoException(const std::string& err="", const std::string& funcname="");
		/** \brief Copy Constructor
		 *	\param e Error to clone
		 */
		MorphotopoException(const MorphotopoException & e);
		/** \brief Exception destructor
		 */
		~MorphotopoException() throw() {}
	  
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

	/** \brief Operator << for MorphotopoException
	 *	\param stream output stream
	 *	\err MorphotopoException to print
	 *	\return output stream
	 */
	inline std::ostream& operator <<(std::ostream& stream, const MorphotopoException & err){
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
