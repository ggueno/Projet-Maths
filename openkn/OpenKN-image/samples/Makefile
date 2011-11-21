#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# Makefile created in 01 2009.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the OpenKraken-image.
#
# The OpenKraken-image is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-image is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

all : ioEPS image_computing

ioEPS :
	@echo "Building ioEPS sample"
	@g++ -o ioEPS_sample ioEPS_sample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -lOpenKN-image -ljpeg -lpng

image_computing :
	@echo "Building image_computing sample"
	@g++ -o imageComputing imageComputingSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -lOpenKN-image -ljpeg -lpng
   
clean :
	@echo "Cleaning samples"
	@rm -Rf imageComputing ioEPS *.o
#	@rm -Rf lin_v4l2webcam_sample wiimote_sample *.o webcamcapture.ppm

bigclean :
	@echo "Cleaning samples"
	@rm -Rf imageComputing ioEPS_sample *.o *~ ImageComputingData/export.ppm ImageComputingData/export_2.ppm outputData/*

