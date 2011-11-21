/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * StringEnumerator.hpp created in 03 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-util.
 *
 * The OpenKraken-util is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-util is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_EXPORTER_STRING_ENUMERATOR__HPP__
#define __OPENKN_EXPORTER_STRING_ENUMERATOR__HPP__

/*
 * External Includes
 */
#include <string>
#include <cassert>
#include <sstream> 
#include <iomanip>


/*
 * Namespace
 */
namespace kn{

    /**
     * \brief generate a string designed for filenames that includes a number coded on a specified digit number. To sumarize, this fuction builds : "filename" + number (on x digit) + "extension". For example : "output"+24(5)+".jpg" => "output00024.jpg". 
     * \param filename: prefix of the resulting string.
     * \param number : number to be read on the resulting string.
     * \param digit : number of digit to code number.
     * \param extension : optional extension (the user should specify the caracter '.')
     * \return  : "filename" + number (digit) + "extension"
     */
    inline std::string stringEnumerator(const std::string &filename, const unsigned int number, const unsigned int digitCard, const std::string extension = ""){
	std::ostringstream oss;
	oss << filename;
	oss << std::setfill('0') << std::setw(digitCard) << number ;
	oss << extension;

	return oss.str(); 
    }
}
/*
 * End of Anti-doublon
 */
#endif
