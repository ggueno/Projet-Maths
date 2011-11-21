/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team   
 * GLSLShader.cpp created in 2 2009.
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

#include "GLSLShader.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace kn{

    static const int MAX_LOG_STRING = 2048;
    static char logstring[MAX_LOG_STRING];


    bool glslCheckAvailability(void){

        if (glewIsSupported("GL_VERSION_2_0 GL_ARB_fragment_program GL_ARB_fragment_shader GL_ARB_shader_objects GL_ARB_shading_language_100 GL_ARB_vertex_program GL_ARB_vertex_shader")){
            return true;
        }

        return false;
    }


    void glslCompile(GLuint object,bool debug){

        if(object==0)
            throw OpenglException("Shader object is undefined.","glsl::compile");

        glCompileShader(object);

        int status = 0;
        glGetShaderiv(object, GL_COMPILE_STATUS, &status);
        if(status==0){
            if(debug){
                int length = 0;
                glGetShaderiv(object, GL_INFO_LOG_LENGTH, &length);
                if(length>0){
                    GLsizei minlength = std::min(MAX_LOG_STRING,length);
                    glGetShaderInfoLog(object, minlength, 0, logstring);
                    std::cerr << logstring << std::endl;
                }
            }
            throw OpenglException(" Compilation of shader object has failed","glsl::compile");
        }
    }

    void glslCompile(GLuint *objects,const size_t& nbobjects,bool debug){

        if(objects==0)
            throw OpenglException("Array of shader objects is NULL.","glsl::compile");

        bool failure = false;
        std::string errmsg = "undefined";
        std::ostringstream out;
        for(unsigned int i = 0; i < nbobjects; ++i){
            out << i;
            if(objects!=0){

                glCompileShader(objects[i]);

                int status=0;
                glGetShaderiv(objects[i], GL_COMPILE_STATUS, &status);

                if(status==0) {
                    errmsg = "Compilation of shader object " + out.str() + " has failed.";
                    failure = true;
                    if(debug){
                        int length = 0;
                        glGetShaderiv(objects[i], GL_INFO_LOG_LENGTH, &length);
                        if(length>0){
                            GLsizei minlength = std::min(MAX_LOG_STRING,length);
                            glGetShaderInfoLog(objects[i], minlength, 0, logstring);
                            std::cerr << logstring << std::endl;
                        }
                    }
                }
            }
            else {
                errmsg = "Shader object " + out.str() + " is undefined.";
                failure = true;
            }
        }
        if(failure)
            throw(errmsg.c_str(),"glsl::compile");
    }

    void glslCompile(const std::list<GLuint>& objects,bool debug){

        if(objects.size()==0)
            throw OpenglException("List of shader objects is empty.","glsl::compile");

        bool failure = false;
        std::string errmsg = "undefined";
        std::ostringstream out;
        std::list<GLuint>::const_iterator it = objects.begin();
        int i = 0;
        while(it != objects.end()){
            out << i;
            if(*it!=0){
                glCompileShader(*it);

                int status;
                glGetShaderiv(*it, GL_COMPILE_STATUS, &status);
                if(status==0){
                    errmsg = "Compilation of shader object " + out.str() + " has failed.";
                    failure = true;
                    if(debug){
                        int length = 0;
                        glGetShaderiv(*it, GL_INFO_LOG_LENGTH, &length);
                        if(length>0){
                            GLsizei minlength = std::min(MAX_LOG_STRING,length);
                            glGetShaderInfoLog(*it, minlength, 0, logstring);
                            std::cerr << logstring << std::endl;
                        }
                    }
                }
            }
            else{
                errmsg = "Shader object " + out.str() + " is undefined.";
                failure = true;
            }
            ++it;
            ++i;
        }
        if(failure)
            throw(errmsg.c_str(),"glsl::compile");
    }

    GLuint glslLink(GLuint* objects,const unsigned int& nb,bool debug){

        if(objects==0){
            throw OpenglException("Array of shader objects is NULL.","glsl::link");
            return 0;
        }

        GLuint po = glCreateProgram();
        if(po==0){
            throw OpenglException("The creation of the program object has failed.","glsl::link");
            return 0;
        }

        for(unsigned int i = 0; i < nb; ++i){
            if(objects[i]>0){
                glAttachShader(po,objects[i]);
                GLenum err = glGetError();
                if(err != GL_NO_ERROR){
                    std::cerr << "glsl::link : " << gluErrorString(err) << std::endl;
                }
            }else{
                if(debug)
                    std::cerr << "glsl::link : Shader object " << i << " is undefined." << std::endl;
            }
        }

        glLinkProgram(po);

        int status;
        glGetProgramiv(po, GL_VALIDATE_STATUS, &status);
        if(status==0){
            if(debug){
                int length = 0;
                glGetProgramiv(po, GL_INFO_LOG_LENGTH, &length);
                if(length>0){
                    GLsizei minlength = std::min(MAX_LOG_STRING,length);
                    glGetProgramInfoLog(po, minlength, 0, logstring);
                    std::cerr << logstring << std::endl;
                }
            }
            throw OpenglException("Link of shader objects has failed.","glsl::link");
            return 0;
        }
        return po;
    }


		GLuint glslLink(const GLuint& object1, const GLuint& object2, bool debug){

				if(object1==0 || object2 ==0){
						throw OpenglException("One of the shaders is NULL.","glsl::link");
						return 0;
				}

				GLuint po = glCreateProgram();
				if(po==0){
						throw OpenglException("The creation of the program object has failed.","glsl::link");
						return 0;
				}

				glAttachShader(po,object1);
				GLenum err = glGetError();
				if(err != GL_NO_ERROR){
						std::cerr << "glsl::link : " << gluErrorString(err) << std::endl;
						return 0;
				}

				glAttachShader(po,object2);
				err = glGetError();
				if(err != GL_NO_ERROR){
						std::cerr << "glsl::link : " << gluErrorString(err) << std::endl;
						return 0;
				}

				glLinkProgram(po);

				int status;
				glGetProgramiv(po, GL_VALIDATE_STATUS, &status);
				if(status==0){
						if(debug){
								int length = 0;
								glGetProgramiv(po, GL_INFO_LOG_LENGTH, &length);
								if(length>0){
										GLsizei minlength = std::min(MAX_LOG_STRING,length);
										glGetProgramInfoLog(po, minlength, 0, logstring);
										std::cerr << logstring << std::endl;
								}
						}
						throw OpenglException("Link of shader objects has failed.","glsl::link");
						return 0;
				}
				return po;
		}


		bool glslLink(const GLuint& object1, const GLuint& object2, const GLuint& objectprg, bool debug) {

			if(object1==0 || object2 ==0){
				throw OpenglException("One of the shaders is NULL.","glsl::link");
				return false;
			}

			glAttachShader(objectprg,object1);
			GLenum err = glGetError();
			std::ostringstream oss;
			if(err != GL_NO_ERROR){
				oss << "Can't attach shader to program shader " << gluErrorString(err);
				throw OpenglException(oss.str());
				return false;
			}

			glAttachShader(objectprg,object2);
			err = glGetError();
			if(err != GL_NO_ERROR){
				oss << "Can't attach shader to program shader " << gluErrorString(err);
				throw OpenglException(oss.str());
				return false;
			}

			glLinkProgram(objectprg);

			int status;
			glGetProgramiv(objectprg, GL_VALIDATE_STATUS, &status);
			if(status==0){
				if(debug){
					int length = 0;
					glGetProgramiv(objectprg, GL_INFO_LOG_LENGTH, &length);
					if(length>0){
						GLsizei minlength = std::min(MAX_LOG_STRING,length);
						glGetProgramInfoLog(objectprg, minlength, 0, logstring);
						std::cerr << logstring << std::endl;
					}
				}
				throw OpenglException("Link of shader objects has failed.","glsl::link");
				return false;
			}
			return true;
		}


		GLuint glslLink(const std::list<GLuint>& objects,bool debug){

				if(objects.size()==0){
						throw OpenglException("List of shader objects is NULL.","glsl::link");
						return 0;
				}

				GLuint po = glCreateProgram();
				if(po==0){
						throw OpenglException("The creation of the program object has failed.","glsl::link");
						return 0;
				}

				std::list<GLuint>::const_iterator it = objects.begin();
				int i = 0;
				while(it != objects.end()){
						if(*it>0){
								glAttachShader(po,*it);
								GLenum err = glGetError();
								if(err != GL_NO_ERROR){
										std::cerr << "glsl::link : " << gluErrorString(err) << std::endl;
								}
						}else{
								if(debug)
										std::cerr << "Warning : glsl::link : Shader object " << i << " is undefined." << std::endl;
						}
						++it;
						++i;
				}

				glLinkProgram(po);

				int status;
				glGetProgramiv(po, GL_VALIDATE_STATUS, &status);
				if(status==0){
						if(debug){
								int length = 0;
								glGetProgramiv(po, GL_INFO_LOG_LENGTH, &length);
								if(length>0){
										GLsizei minlength = std::min(MAX_LOG_STRING,length);
										glGetProgramInfoLog(po, minlength, 0, logstring);
										std::cerr << logstring << std::endl;
								}
						}
						throw OpenglException("Link of shader objects has failed.","glsl::link");
						return 0;
				}
				return po;
		}


		GLuint glslLoadShaderProgram(const char * vxshadername,const char* fgshadername,bool debug) {
			GLuint vxobject;
			GLuint fgobject;
			
			// Shader program creation
			GLhandleARB programObject = glCreateProgramObjectARB();
			if(!programObject){
				throw OpenglException("Creation of shader program has failed.","glslLoadShaderProgram");
			}

			// Loading vertex and fragment shaders
			vxobject = glslLoadShader(vxshadername,debug);
			if (vxobject == 0) throw OpenglException("Loading of vertex shader has failed.","glslLoadShaderProgram");
			fgobject = glslLoadShader(fgshadername,debug);
			if (fgobject == 0) throw OpenglException("Loading of fragment shader has failed.","glslLoadShaderProgram");

			// Compiling vertex and fragment shaders
			glslCompile(vxobject,debug);
			glslCompile(fgobject,debug);

			// Linking
			glslLink(vxobject,fgobject,programObject,debug);

			return programObject;
		}



		GLuint glslLoadShader(const char * filename,bool debug){
				if(filename==0){
						if (debug) std::cerr << "loadShader : Filename is required." << std::endl;
						return 0;
				}

				std::string filestr(filename);
				std::transform(filestr.begin(), filestr.end(), filestr.begin(), ::tolower);

				if(filestr.find("vert") != std::string::npos || filestr.find("vertex") != std::string::npos){
					return glslLoadVertexShader(filename);
				}
				else {
					if(filestr.find("frag") != std::string::npos ||
						 filestr.find("fragment") != std::string::npos ||
						 filestr.find("pixel") != std::string::npos) {
						return glslLoadFragmentShader(filename);
					}
					else {
						if (filestr.find("geom") != std::string::npos ||
								filestr.find("geometry") != std::string::npos) {
#ifdef GL_ARB_geometry_shader4
							return glslLoadGeometryShader(filename,debug);
#else
							if (debug) std::cerr << "Sorry, geometry shaders are not supported" << std::endl;
							return 0;
#endif
						}
						else{
							if (debug) {
								std::cerr << "loadShader : Unable to define if the shader's type is vertex, geometry or fragment shader." << std::endl;
							}
							return 0;
						}
					}
				}
		}

		GLchar * readGLSLFile(const char * filename){
				if(filename==0){
						throw OpenglException("Filename is required.","glsl::readGLSLFile");
				}
				std::ifstream file(filename);
				if(!file){
						throw OpenglException("Unable to open file " + std::string(filename) + ".","glsl::readGLSLFile");
				}

				std::stringstream buffer;
				buffer << file.rdbuf();
				file.close();

				std::string s = buffer.str();

				// Required to avoid some memory corruptions
				GLchar * source = new GLchar[4*(buffer.str().size()/4+1)];

				unsigned int i;
				for(i =0; i < buffer.str().size(); ++i){
						if(s[i]!='\0')
								source[i] = s[i];
						else
								source[i] = ' ';
				}
				source[i] = '\0';
				return source;
		}

		GLuint glslLoadVertexShader(const char * filename){

				GLchar * source = readGLSLFile(filename);
				if(source == 0)
						return 0;

				GLuint so = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(so, 1,(const GLchar**) &source, 0);

				delete[] source;

				return so;
		}

		GLuint glslLoadFragmentShader(const char * filename){

				GLchar * source = readGLSLFile(filename);
				if(source == 0) return 0;

				GLuint so = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(so, 1,(const GLchar**) &source, 0);

				delete[] source;

				return so;
		}

#ifdef GL_ARB_geometry_shader4
		GLuint glslLoadGeometryShader(const char * filename,bool debug) {

				if(!GLEW_EXT_geometry_shader4){
						if (debug) {
							std::cerr << "loadGeometryShader : OpenGL extension GL_EXT_geometry_shader4 is required." << std::endl;
						}
						return 0;
				}

				GLchar * source = readGLSLFile(filename);
				if(source == 0) return 0;

				GLuint so = glCreateShader(GL_GEOMETRY_SHADER_EXT);
				glShaderSource(so, 1,(const GLchar**) &source, 0);

				delete[] source;

				return so;
		}
#endif

}
