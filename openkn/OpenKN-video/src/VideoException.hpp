/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * VideoException.hpp created in 8 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-video.
 *
 * The OpenKraken-video is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-video is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_VIDEO__VIDEOEXCEPTION_HPP__
#define __OPENKN_VIDEO__VIDEOEXCEPTION_HPP__

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

	/** \brief Exception thrown in case of video error
	 *
	 */
	class VideoException : std::exception {

		/*
		 * Constructor & destructors
		 */		 
	public:
		/** \brief Constructor with error string and calling function name
		 *	\param err Error string
		 *	\param funcname calling function name
		 */
		VideoException(const std::string& err="", const std::string& funcname="");
		/** \brief Copy Constructor
		 *	\param e Error to clone
		 */
		VideoException(const VideoException & e);
		/** \brief Exception destructor
		 */
		~VideoException() throw() {}
	  
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

	/** \brief Operator << for VideoException
	 *	\param stream output stream
	 *	\err VideoException to print
	 *	\return output stream
	 */
	inline std::ostream& operator <<(std::ostream& stream, const VideoException & err){
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
