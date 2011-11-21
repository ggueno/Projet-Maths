/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team   
 * FBO.cpp created in 10 2009.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU LessOpenKNer General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/
		
#include "FBO.hpp"
#include <GL/glew.h>

namespace kn{

    bool fboCheckAvailability(void){
	
        if (glewIsSupported("GL_VERSION_2_0 GL_EXT_framebuffer_object")){
            return true;
        }
		
        return false;
    }


    unsigned int fboGetError(void){

        GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        switch(status) {
            
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            return 0;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            return 1;
            break;
            
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            return 2;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            return 3;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            return 4;
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            return 5;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            return 6;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            return 7;
            break;

        default:
            return 8;

        }
    }

    std::string fboGetErrorString(const unsigned int error){
        switch(error) {
        case 0:
            return std::string("No error");
            break;
            
        case 1:
            return std::string("Incomplete attachment");
            break;
            
        case 2:
            return std::string("Unsupported, some internal formats violate an implementation-dependent set of restrictions");
            break;
            
        case 3:
            return std::string("Incomplete missing attachment, there is no image attached to the framebuffer");
            break;
            
        case 4:
            return std::string("Incomplete dimensions, all attached images have the same width and height");
            break;

        case 5:
            return std::string("Incomplete formats, all color attachments, must have the same internal format");
            break;
            
        case 6:
            return std::string("Incomplete draw buffer, a write buffer need to be specified");
            break;
            
        case 7:
            return std::string("Incomplete read buffer, a read buffer need to be specified");
            break;

        default:
            return std::string("Unknown error");
      
        }
    }

  

}
