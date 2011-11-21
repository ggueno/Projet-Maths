#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# Makefile created in 03 2009.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-vision.
#
# The OpenKraken-vision is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-vision is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

all : zhang gold imageRectification harris correl ARmarker radialDistortion

zhang :
	@echo "Building zhang_sample"
	@g++ -o zhang_sample ZhangSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -lOpenKN-vision -lOpenKN-vision-opencv -lOpenKN-math -lOpenKN-image -lcv -ljpeg -lpng -lGL -lglut -lGLU

gold :
	@echo "Building gold_sample"
	@g++ -o gold_sample GoldStandardAlgoSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -I/usr/local/include/ -lOpenKN-vision -lOpenKN-vision-opencv -lOpenKN-math -lOpenKN-image -lcv -ljpeg -lpng -lGL -lglut -lGLU

imageRectification :
	@echo "Building imageRectification_sample"
	@g++ -o imageRectification_sample ImageRectificationSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -I/usr/local/include/ -lOpenKN-vision -lOpenKN-image -lOpenKN-math -lcv -ljpeg -lpng -lGL -lglut

harris :
	@echo "Building harris_sample"
	@g++ -o harris_sample HarrisSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -I/usr/local/include/ -lOpenKN-vision -lOpenKN-math -lOpenKN-image -ljpeg -lpng

correl :
	@echo "Building crossCorrelation_sample"
	@g++ -o crossCorrelation_sample CorrelationSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -I/usr/local/include/ -lOpenKN-vision -lOpenKN-math -lOpenKN-image -ljpeg -lpng

ARmarker :
	@echo "Building ARmarkerMaker_sample"
	@g++ -o ARmarkerMaker_sample ARtoolkitMarkerMakerSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -I/usr/local/include/ -lOpenKN-vision  -lOpenKN-math -lOpenKN-image -ljpeg -lpng

radialDistortion :
	@echo "Building radialDistortion_sample"
	@g++ -o radialDistortion_sample RadialDistortionCorrectorSample.cpp -I$(OPEN_KN_DIR)/include -L$(OPEN_KN_DIR)/lib -I/usr/local/include/ -lOpenKN-vision -lOpenKN-math -lOpenKN-image -ljpeg -lpng

clean :
	@echo "Cleaning samples"
	@rm -Rf crossCorrelation_sample zhang_sample gold_sample imageRectification_sample harris_sample ARmarkerMaker_sample *.o
