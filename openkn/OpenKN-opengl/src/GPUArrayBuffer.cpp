/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * GPUArrayBuffer.cpp created in 4 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-opengl.
 *
 * The OpenKraken-opengl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-opengl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * External Includes
 */

/*
 * Internal Includes
 */
#include "GPUArrayBuffer.hpp"

/* Removing some warnings on Microsoft Visual C++ */
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif
/*
 * static variables
 */

/*
 * Namespace
 */
namespace kn{

		/*
		 * function definition
		 */
		GPUArrayBuffer::GPUArrayBuffer(bool deleteGeometry, GLenum dataUsage, GLenum dataType) {
			this->dataUsage = dataUsage;
			this->dataType = dataType;
			this->deleteGeometry = deleteGeometry;
			deleteVBO = false;
			nbPrimitives = 0;
		}

		GPUArrayBuffer::~GPUArrayBuffer() {
			if (deleteVBO) 
				glDeleteBuffers(1,&bufferId);
		}

		void GPUArrayBuffer::initGL() {
			/* Create VBO */
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(GLfloat), NULL, dataUsage);
			deleteVBO = true;

			/* Data copy */
			void * dataptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			std::copy(data.begin(),data.end(),(float*)dataptr);
			glUnmapBuffer(GL_ARRAY_BUFFER);
	
			glBindBuffer(GL_ARRAY_BUFFER,0);

			if (deleteGeometry) data.clear();
		}

		void GPUArrayBuffer::enableGL() {
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);

			switch (dataType) {
				case GL_VERTEX_ARRAY : glVertexPointer(3, GL_FLOAT, 0, 0); break;
				case GL_COLOR_ARRAY :  glColorPointer(3, GL_FLOAT, 0, 0); break;
				case GL_NORMAL_ARRAY : glNormalPointer(GL_FLOAT, 0, 0); break;
				case GL_TEXTURE_COORD_ARRAY : glTexCoordPointer(3,GL_FLOAT, 0, 0); break;
			}
			glEnableClientState(dataType);
		}

		void GPUArrayBuffer::drawGL(GLenum primitivesType, int first, size_t count) {
			glDrawArrays(primitivesType, first, count);
		}

		void GPUArrayBuffer::disableGL() {
			glDisableClientState(dataType);

		}


	 /*
		* End of Namespace
		*/
}
