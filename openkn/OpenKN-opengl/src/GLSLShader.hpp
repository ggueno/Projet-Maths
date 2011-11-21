/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * GLSLShader.hpp created in 2 2009.
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
#ifndef __OPENKN_GLSL_SHADER_HPP__
#define __OPENKN_GLSL_SHADER_HPP__


/*
 * External Includes
 */
#include <GL/glew.h>
#include <list>

/*
 * Internal Includes
 */
#include "OpenglException.hpp"

/*
 * Namespace
 */
namespace kn {

		/**
			* \brief check if shaders are available
			*
			* \author Frankoi
			* \return true if shaders are available, false otherwise
			*/
		bool glslCheckAvailability(void);

		/**
			* \brief Compile a shader object
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			* \author Frankoi
			* \param object a shader object
			* \param debug toggle display of debugging messages
			* \param filename the filename of the file containing the vertex shader code
			*/
		void glslCompile(GLuint object,bool debug = true);


		/** \brief Compile an array of shader objects
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			* \author Frankoi
			* \param objects array of shader objects
			* \param nb number of shader objects
			* \param debug toggle display of debugging messages
			* \param filename the filename of the file containing the vertex shader code
			*/
		void glslCompile(GLuint * objects,const size_t& nbobjects,bool debug = true);

		/**
			* \brief Compile a list of shader objects
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			* \author Frankoi
			* \param objects list of shader objects
			* \param debug toggle display of debugging messages
			*/
		void glslCompile(const std::list<GLuint>& objects,bool debug = true);

		/**
			* \brief Link an array of compiled shader objects
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			* \author Frankoi
			* \param objects array of compiled shader objects
			* \param nb number of shader objects
			* \param debug toggle display of debugging messages
			* \return a program object linked with compiled shader objects
			*/
		GLuint glslLink(GLuint* objects,const unsigned int& nb,bool debug = true);

		/**
			* \brief Link two compiled shader objects
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			* \author Frankoi
			* \param object1 a compiled shader object
			* \param object2 a compiled shader object
			* \param debug toggle display of debugging messages
			* \return a program object linked with compiled shader objects
			*/
		GLuint glslLink(const GLuint& object1, const GLuint& object2, bool debug = true);

		/**
		 * \brief Link two compiled shader objects to an existing shader program
		 *
		 * The function requieres the ARB_shading_language_100 OpenGL extension.
		 *
		 * \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
		 * \author Biri
		 * \param object1 a compiled shader object
		 * \param object2 a compiled shader object
		 * \param objectprg a shader program object
		 * \param debug toggle display of debugging messages
		 * \return succes of operation
		 */
		bool glslLink(const GLuint& object1, const GLuint& object2, const GLuint& objectprg, bool debug = true);

		/**
			* \brief Link a list of compiled shader objects
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \warning Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			* \author Frankoi
			* \param objects list of compiled shader objects
			* \param debug toggle display of debugging messages
			* \return a program object linked with compiled shader objects
			*/
		GLuint glslLink(const std::list<GLuint>& objects,bool debug = true);

		/**
			* \brief Load a GLSL file and create the related shader object. It can be a vertex, geometry or fragment shader.
			*
			* A vertex file has the extension ".vert" or contains the word "vertex".
			* A fragment file has the extension ".frag" or contains the word "fragment" or "pixel".
			* A fragment file has the extension ".geom" or contains the word "geometry".
			*
			* The function return 0 if the loading have failed
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			* The function requieres the ARB_geometry_shader4 OpenGL extension to load geometry shader files.
			*
			* Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			*
			* \param filename the filename of the file containing the GLSL code
			* \return GLhandleARB the shader object created
			*/
		GLuint glslLoadShader(const char * filename,bool debug = true);

		/**
		 * \brief Load both vertex and fragment GLSL file and create the related shader program
		 *
		 * A vertex file has the extension ".vert" or contains the word "vertex".
		 * A fragment file has the extension ".frag" or contains the word "fragment" or "pixel".
		 *
		 * The function return 0 if the shader program creation have failed
		 *
		 * The function requieres the ARB_shading_language_100 OpenGL extension.
		 *
		 * Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
		 *
		 * \param vxshadername the filename of the file containing the vertex shader GLSL code
		 * \param fgshadername the filename of the file containing the vertex shader GLSL code
		 * \return GLhandleARB the shader program object created
		 */
		GLuint glslLoadShaderProgram(const char * vxshadername,const char* fgshadername,bool debug = true);

		/**
			* \brief Load a vertex shader file and create the vertex shader object.
			*
			* The function return 0 if the loading have failed
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			*
			* \param filename the filename of the file containing the vertex shader code
			* \return GLhandleARB the vertex shader object created
			*/
		GLuint glslLoadVertexShader(const char * filename);

		/**
			* \brief \brief Load a fragment shader file and create the fragment shader object.
			*
			* The function return 0 if the loading have failed
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			*
			* \param filename the filename of the file containing the fragment shader code
			* \return GLhandleARB the fragment shader object created
			*/
		GLuint glslLoadFragmentShader(const char * filename);


#ifdef GL_ARB_geometry_shader4
		/**
			* \brief Load a geometry shader file and create the geometry shader object.
			*
			* The function return 0 if the loading have failed
			*
			* The function requieres the ARB_shading_language_100 OpenGL extension.
			* The function requieres the ARB_geometry_shader4 OpenGL extension.
			*
			* Don't forget to create a valid OpenGL context and to call the function glewInit() before using this function.
			*
			* \param filename the filename of the file containing the geometry shader code
			* \return GLhandleARB the geometry shader object created
			*/
		GLuint glslLoadGeometryShader(const char * filename,bool debug = true);
#endif

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
