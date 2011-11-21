/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * OpenglException.cpp created in 2 2009.
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
 * Internal Includes
 */
#include <OpenglException.hpp>

/*
 * Namespace
 */
namespace kn {

/*
 * Functions definitions
 */
	OpenglException::OpenglException(const std::string& err, const std::string& funcname){
		if(funcname=="" && err=="")
			str = "Error : No message";
		if(funcname!="" && err!="")
			str = "(" + funcname + ") Error : " + err;
		if(funcname=="" && err!="")
			str = "Error : " + err;
		if(funcname!="" && err=="")
			str = "(" + funcname + ") Error : No message";
	}
    
	OpenglException::OpenglException(const OpenglException & e) : std::exception(){
		str = e.errorString();
	}

	/*
	* End of Namespace
	*/
}
