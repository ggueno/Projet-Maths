/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * GeometryException.cpp created in 3 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-geometry.
 *
 * The OpenKraken-geometry is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-geometry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Internal Includes
 */
#include <GeometryException.hpp>

/*
 * Namespace
 */
namespace kn{

    /*
     * Functions definitions
     */

    GeometryException::GeometryException(const std::string& err, const std::string& funcname){
	if(funcname=="" && err=="")
	    str = "Error : No message"; 
	if(funcname!="" && err!="")
	    str = "(" + funcname + ") Error : " + err;
	if(funcname=="" && err!="")
	    str = "Error : " + err;
	if(funcname!="" && err=="") 
	    str = "(" + funcname + ") Error : No message";
    }

    GeometryException::GeometryException(const GeometryException & e) : std::exception() {
	str = e.errorString();	  
    }

    /*
     * End of Namespace
     */
}
