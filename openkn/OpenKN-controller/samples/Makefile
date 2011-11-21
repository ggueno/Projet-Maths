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

all : v4l2webcam v4l2webcam2 wiimote dvcam

 v4l2webcam :
	@echo "Building lin_v4l2webcam_sample"
	@g++ -o lin_v4l2webcam_sample LIN_V4L2Webcam_sample.cpp -I. -I${OPENKN_DIR}/include -L${OPENKN_DIR}/lib -lOpenKN-controller

 v4l2webcam2 :
	@echo "Building lin_v4l2webcam_sample2"
	@g++ -o lin_v4l2webcam_sample2 LIN_V4L2Webcam_sample2.cpp -I. -I${OPENKN_DIR}/include -L${OPENKN_DIR}/lib -lOpenKN-controller -lGL -lglut

dvcam :
	@echo "Building lin_dvcam_sample"
	@g++ -o lin_dvcam_sample LIN_DVCam_sample.cpp -I. -I${OPENKN_DIR}/include -L${OPENKN_DIR}/lib -lOpenKN-controller -lOpenKN-controller-dvcam -lboost_thread -ldv -liec61883 -lraw1394 -lGL -lglut

wiimote :
	@echo "Building wiimote_sample"
	@g++  -o wiimote_sample Wiimote_sample.cpp -I. -I${OPENKN_DIR}/include -L${OPENKN_DIR}/lib -I${WIIUSE_IDIR} -L${WIIUSE_LDIR} -I${OPENKN_DIR}/include  -lOpenKN-controller -lOpenKN-controller-wiimote -lwiiuse -lboost_thread -lGL -lglut

clean :
	@echo "Cleaning samples"
	@rm -Rf lin_v4l2webcam_sample lin_v4l2webcam_sample2 wiimote_sample lin_dvcam_sample *.o webcamcapture.ppm webcamcapture2.ppm dvcamcapture.ppm
