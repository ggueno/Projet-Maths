/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * GPUArrayBuffer.hpp created in 4 2009.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_OPENGL__GPUARRAYBUFFER_HPP__
#define __OPENKN_OPENGL__GPUARRAYBUFFER_HPP__

/*
 * External Includes
 */
#include <GL/glew.h>
#include <vector>

/*
 * Internal Includes
 */


/*
 * Namespace
 */
namespace kn{
	/**
	 * \brief Container for CPU to GPU VBO
	 * This class handles any mesh used in GL as VBO. It can be seen as a container of geometry for a Mesh
	 */
	class GPUArrayBuffer {
		/*
			* Constructors & Destructors
			*/
	public:
		/**
		 * \brief Constructor from GPU Array Buffer
		 * This function create an object handling in CPU a GPU Array Buffer
		 * \param deleteGeometry 
		 * \param dataUsage indicates ... Must be choosen in GL_STATIC_DRAW (the default) or GL_STREAM_DRAW, GL_STREAM_READ,
		 *									GL_STREAM_COPY, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
		 * \param dataType indicates the kind of data we want to store. Must be choosen in GL_VERTEX_ARRAY (the default),
		 *								 GL_COLOR_ARRAY, GL_NORMAL_ARRAY, or GL_TEXTURE_COORD_ARRAY
		 */
		GPUArrayBuffer(bool deleteGeometry=true, GLenum dataUsage=GL_STATIC_DRAW, GLenum dataType=GL_VERTEX_ARRAY);
		/** Destructor
			*/
		~GPUArrayBuffer();


		/*
			* Geometry
			*/
	private :
		std::vector<float> data;		///< Geometry data : Coordinates
		unsigned int nbPrimitives;	///< Number of primitives
		bool deleteGeometry;				///< Flag for geometry deletion after loading in GPU
	public :
		/**
		 * \brief Toggle deleteGeometry member
		 */
		inline void toogleGeometryDeletion() {(deleteGeometry)?deleteGeometry=false:deleteGeometry=true;}
		/**
		 * \brief Getter for data
		 */
		inline const std::vector<float> & getData() const {return data;}
		/**
		 * \brief Getter for data
		 */
		inline std::vector<float> & getData()  {return data;}
		/**
		 * \brief Getter for nbPrimitives
		 */
		inline unsigned int getNbPrimitives() {return nbPrimitives;}
		/**
		 * \brief Setter for nbPrimitives
		 */
		inline void setNbPrimitives(unsigned int nb) {nbPrimitives = nb;}
	/*
	 * GL
	 */
	private :
		GLuint bufferId;		// Id, in GL driver, of the VBO
		bool deleteVBO;			// Flag for VBO deletion
		GLenum dataUsage;		// ???
		GLenum dataType;		// Data type determines the king of data we want to store : coordinates, normals, color, texcoord...
	public :
		/**
		 * \brief Toggle the deletion of the VBO
		 */
		inline void toogleVBODeletion() {(deleteVBO)?deleteVBO=false:deleteVBO=true;}
		/**
		 * \brief Get the internal id (in OpenGL driver) of the VBO
		 */
		inline GLuint getBufferId() {return bufferId;}
		/**
		 * \brief Setter for bufferId !!!
		 */
		inline void setBufferId(GLuint id) {bufferId = id;}
		/**
		 * \brief Setter for dataUsage.
		 * \param usage To choose in GL_STATIC_DRAW (the default) or GL_STREAM_DRAW, GL_STREAM_READ,
		 *							GL_STREAM_COPY, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
		 */
		inline void setDataUsage(GLenum usage) {dataUsage = usage;}
		/**
		 * \brief Setter for dataType.
		 * \param type To choose in GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_NORMAL_ARRAY, or GL_TEXTURE_COORD_ARRAY
		 */
		inline void setDataType(GLenum type) {dataType = type;}
		
		/**
		 * \brief Initializes (creates) the VBO
		 * This method create in GL the VBO and populate the buffer with the data stored in the object
		 */
		void initGL();
		/**
		 * \brief Activates the VBO
		 * Activates the VBO what is essential for rendering.
		 */
		void enableGL();
		/**
		 * \brief Desactivates the VBO
		 */
		void disableGL();
		/**
		 * \brief Draw the VBO
		 * \param primitivesType Primitive type to be rendered. Must be choosen in GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
		 *											GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, and GL_POLYGON
		 * \param first Specifies the starting index in the enabled arrays.
		 * \param count Specifies the number of indices to be rendered
		 */
		static void drawGL(GLenum primitivesType, int first, size_t count);
	};

	/*
	 * End of Namespace
	 */
}

/*
 * End Anti-doublon
 */
#endif

