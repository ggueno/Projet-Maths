/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * OpencvCalibrationTools.cpp created in 03 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-vision.
 *
 * The OpenKraken-vision is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-vision is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Internal Includes
 */
#include "OpencvCalibrationTools.hpp"
#include <opencv/cv.h>

/*
 * Namespace
 */
namespace kn{

       /*
	* Detect an openCV chessboard and return a set of 2d correspondances (vector of pair of Vector3).
	*/
	void opencvChessboardDetection(kn::ImageRGB8u &inputImage,
				       std::vector< std::pair<kn::Vector3d,kn::Vector3d> > &myList,
				       const unsigned int markerNbColumns,
				       const unsigned int markerNbLines,
				       const double markerSquareSize,
				       const bool drawDetectionOn) {

			// image data structure
			CvSize imageSize = cvSize(inputImage.width(),inputImage.height());
			IplImage *ocvImage = cvCreateImage(imageSize,8,3);
			memcpy(ocvImage->imageData, inputImage.begin(), 3 * inputImage.width() * inputImage.height());

			// detected points data structure
			int nbPointsDetected = 0;
			int nbMaxPoints = markerNbColumns * markerNbLines;
			CvPoint2D32f *detectedPoints = new CvPoint2D32f[nbMaxPoints];
			
			// opencv chessboard detection
		  if(cvFindChessboardCorners(ocvImage,         // image
						cvSize(markerNbLines,markerNbColumns), // The number of inner corners of the chessboard
						detectedPoints,                        // (output) list of the detected points
						&nbPointsDetected,                     // (output) number of corners detected
						CV_CALIB_CB_ADAPTIVE_THRESH /* | CV_CALIB_CB_NORMALIZE_IMAGE*/)) // options
			{			
				// subpixel operation
				if(nbPointsDetected == nbMaxPoints)
				{
					// grey scale image required for this operation
					IplImage *tmpImg = cvCreateImage(imageSize,IPL_DEPTH_8U, 1);
					cvCvtColor(ocvImage, tmpImg, CV_BGR2GRAY);
					CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10, 0.01f);
					cvFindCornerSubPix(tmpImg, detectedPoints, nbPointsDetected, cvSize(5,5), cvSize(-1,-1),criteria);
					cvReleaseImage(&tmpImg);
				}

				// draw the detected chessboard on the input image
				if(drawDetectionOn)
				{
					cvDrawChessboardCorners(ocvImage, cvSize(markerNbColumns,markerNbLines), detectedPoints, nbPointsDetected,1);
					memcpy(inputImage.begin(), ocvImage->imageData, 3 * inputImage.width() * inputImage.height());
				}

				// extract the detected point to build the 2d-2d correspondace list
				for(int i=0; i<nbPointsDetected; ++i)
					{
						kn::Vector3d pix;
						pix[0] = detectedPoints[i].x;
						pix[1] = detectedPoints[i].y;
						pix[2] = 1.0;

						kn::Vector3d pt;
						pt[0] = (i/markerNbColumns) * markerSquareSize;
						pt[1] = (i%markerNbColumns) * markerSquareSize;
						pt[2] = 1.0;

						myList.push_back(std::pair<kn::Vector3d,kn::Vector3d >(pt,pix));
					}
			}
			cvReleaseImage(&ocvImage);
			delete[] detectedPoints;
		}

    /*
     * End of Namespace
     */
}


