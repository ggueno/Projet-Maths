#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# Makefile created in 10 2008.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the libIMAC-controller.
#
# The libIMAC-controller is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The libIMAC-controller is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

all : glsl

 glsl :
	@echo "Building glslSample"
	@g++ -o glslSample glslSample.cpp -I. -lOpenKN-opengl -lGLEW -lglut -ljpeg

clean :
	@echo "Cleaning samples"
	@rm -Rf glslSample *.o