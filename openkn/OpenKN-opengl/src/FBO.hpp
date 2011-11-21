/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * FBO.hpp created in 10 2009.
 * Mail : biri@univ-mlv.fr                    
 *                                                     
 * This file is part of the OpenKN-opengl.
 *
 * The OpenKN-opengl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published yb
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
#ifndef __OPENKN_FBO_HPP__
#define __OPENKN_FBO_HPP__


/*
 * External Includes
 */
#include <string>

/*
 * Namespace
 */
namespace kn {

    /**
     * \brief check if fbo are available
     *   
     * \author Frankoi
     * \return true if fbo are available, false otherwise
     */
    bool fboCheckAvailability(void);

    /**
     * \brief Return the status of the current FBO
     * 
     * It returns 0 if everything is ok
     * \author Frankoi
     * \return the value of the current error
     */
    unsigned int fboGetError(void);

    /**
     * \brief Return the string corresponding to the current FBO error
     * 
     * \param error the value of the current error
     * \author Frankoi
     * \sa fboGetError
     * \return the string corresponding to the error
     */
    std::string fboGetErrorString(const unsigned int error);

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
