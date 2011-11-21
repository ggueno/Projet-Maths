#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# Makefile created in 10 2008.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the OpenKraken-controller.
#
# The OpenKraken-controller is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-controller is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

all : decodevideo encodevideo

 decodevideo :
	@echo "Building decodevideo"
	@g++ -o decodevideo decodevideo.cpp -I. -I${OPENKN_DIR}/include -L${OPENKN_DIR}/lib -lOpenKN-video -lavutil -lavformat -lavcodec -lswscale


 encodevideo :
	@echo "Building encodevideo"
	@g++ -o encodevideo encodevideo.cpp -I. -I${OPENKN_DIR}/include -L${OPENKN_DIR}/lib -lOpenKN-video -lavutil -lavformat -lavcodec -lswscale

clean :
	@echo "Cleaning samples"
	@rm -Rf decodevideo encodevideo picture-test.ppm test.mpeg
