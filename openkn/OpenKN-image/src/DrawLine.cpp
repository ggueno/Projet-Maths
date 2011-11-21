/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * DrawLine.cpp created in 10 2009.
 * Mail : biri@univ-mlv.fr 
 *
 * This file is part of the OpenKraken-image.
 *
 * The OpenKraken-image is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-image is distributed in the hope that it will be useful,
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
#include <cmath>

/*
 * Internal Includes
 */
#include "DrawLine.hpp"

/*
 * Namespace
 */
namespace kn{
    /*
     * End of Namespace
     */


	void drawLine(ImageRGB8u &image,
        	      const int x1, const int y1,
                      const int x2, const int y2,
                      const unsigned char r,
                      const unsigned char g,
                      const unsigned char b){
		// axis variation
		int dx = std::abs(x2 - x1);
		int dy = std::abs(y2 - y1);

		// select the main direction
		if(dy>dx) drawLineY(image, x1, y1, x2, y2, r, g, b);
		else drawLineX(image, x1, y1, x2, y2, r, g, b);
	}


	void drawLine(ImageGS8u &image,
        	      const int x1, const int y1,
                      const int x2, const int y2,
                      const unsigned char greyLevel){
		// axis variation
		int dx = std::abs(x2 - x1);
		int dy = std::abs(y2 - y1);

		// select the main direction
		if(dy>dx) drawLineY(image, x1, y1, x2, y2, greyLevel);
		else drawLineX(image, x1, y1, x2, y2, greyLevel);
	}


	void drawLine(ImageRGB8u &image,
		      const double line[3],
                      const unsigned char r,
                      const unsigned char g,
                      const unsigned char b){

		// find the min and max bounds
		unsigned int x1,x2,y1,y2;

		if(fabs(line[0])*1.0e5 < line[1]){ // vertical line (this test should be improved)
			x1 = x2 = (unsigned int)(-line[2]/line[0]);
			y1 = 0;
			y2 = image.height();
		}
		else{
			x1 = 0;
			y1 = (unsigned int)(-line[2]/line[1]);
			x2 = image.width();
			y2 = (unsigned int)(-(line[2]+line[0]*image.width())/line[1]);
		}

		// draw the line
		drawLine(image, x1, y1, x2, y2, r, g, b);
	}


	void drawLine(ImageGS8u &image,
		      const double line[3],
                      const unsigned char greyLevel){

		// find the min and max bounds
		unsigned int x1,x2,y1,y2;

		if(fabs(line[0])*1.0e5 < line[1]){ // vertical line (this test should be improved)
			x1 = x2 = (unsigned int)(-line[2]/line[0]);
			y1 = 0;
			y2 = image.height();
		}
		else{
			x1 = 0;
			y1 = (unsigned int)(-line[2]/line[1]);
			x2 = image.width();
			y2 = (unsigned int)(-(line[2]+line[0]*image.width())/line[1]);
		}

		// draw the line
		drawLine(image, x1, y1, x2, y2, greyLevel);
	}


	void drawLineY(ImageRGB8u &image,
		       const int x1, const int y1,
                       const int x2, const int y2,
                       const unsigned char r,
                       const unsigned char g,
                       const unsigned char b){
		// if nothing to draw
		if(y1-y2 == 0) return;

		// floating point notation
		int xf1 = int2FloatingInt(x1);
		int yf1 = int2FloatingInt(y1);
		int xf2 = int2FloatingInt(x2);
		int yf2 = int2FloatingInt(y2);

		// starting point
		if(yf1>yf2){
			std::swap(xf1,xf2);
			std::swap(yf1,yf2);
		}

		// direction
		int a = (int)( (xf1-xf2)/(double)(yf1-yf2) * ( ((int)1)<<16) );

		// draw the line
		while(yf1 < yf2){
			drawPixel(image, xf1, yf1, r, g, b);
			xf1 += a;
			yf1 += int2FloatingInt(1);
		}
	}



	void drawLineY(ImageGS8u &image,
		       const int x1, const int y1,
                       const int x2, const int y2,
                       const unsigned char greyLevel){
		// if nothing to draw
		if(y1-y2 == 0) return;

		// floating point notation
		int xf1 = int2FloatingInt(x1);
		int yf1 = int2FloatingInt(y1);
		int xf2 = int2FloatingInt(x2);
		int yf2 = int2FloatingInt(y2);

		// starting point
		if(yf1>yf2){
			std::swap(xf1,xf2);
			std::swap(yf1,yf2);
		}

		// direction
		int a = (int)( (xf1-xf2)/(double)(yf1-yf2) * ( ((int)1)<<16) );

		// draw the line
		while(yf1 < yf2){
			drawPixel(image, xf1, yf1, greyLevel);
			xf1 += a;
			yf1 += int2FloatingInt(1);
		}
	}


	void drawLineX(ImageRGB8u &image,
        	       const int x1, const int y1,
        	       const int x2, const int y2,
        	       const unsigned char r,
        	       const unsigned char g,
        	       const unsigned char b){
		// if nothing to draw
		if(x1-x2 == 0) return;

		// floating point notation
		int xf1 = int2FloatingInt(x1);
		int yf1 = int2FloatingInt(y1);
		int xf2 = int2FloatingInt(x2);
		int yf2 = int2FloatingInt(y2);

		// starting point
		if(xf1>xf2){
			std::swap(xf1,xf2);
			std::swap(yf1,yf2);
		}

		// direction
		int a = (int)( (yf1-yf2)/(double)(xf1-xf2) * ( ((int)1)<<16) );

		// draw the line
		while(xf1 < xf2){
			drawPixel(image, xf1, yf1, r, g, b);
			xf1 += int2FloatingInt(1);
			yf1 += a;
		}
	}


	void drawLineX(ImageGS8u &image,
        	       const int x1, const int y1,
        	       const int x2, const int y2,
        	       const unsigned char greyLevel){
		// if nothing to draw
		if(x1-x2 == 0) return;

		// floating point notation
		int xf1 = int2FloatingInt(x1);
		int yf1 = int2FloatingInt(y1);
		int xf2 = int2FloatingInt(x2);
		int yf2 = int2FloatingInt(y2);

		// starting point
		if(xf1>xf2){
			std::swap(xf1,xf2);
			std::swap(yf1,yf2);
		}

		// direction
		int a = (int)( (yf1-yf2)/(double)(xf1-xf2) * ( ((int)1)<<16) );

		// draw the line
		while(xf1 < xf2){
			drawPixel(image, xf1, yf1, greyLevel);
			xf1 += int2FloatingInt(1);
			yf1 += a;
		}
	}


	void drawPixel(ImageRGB8u &image,
		       int x0, int y0,
		       const unsigned char r,
		       const unsigned char g,
		       const unsigned char b){
		int y1 = y0 >> 16;
		int y2 = y1+1;

		double val = static_cast<double>(y0 & 0xFFFF) / static_cast<double> (0xFFFF);

		x0 = x0 >> 16;

		if(x0>=0 && x0<(int)image.width() && y1>=0 && y1<(int)image.height()){
			image(x0,y1)[0] = (unsigned char)((1.0-val)*((int)r)) + (unsigned char)(val*((int)image(x0,y1)[0]));
			image(x0,y1)[1] = (unsigned char)((1.0-val)*((int)g)) + (unsigned char)(val*((int)image(x0,y1)[1]));
			image(x0,y1)[2] = (unsigned char)((1.0-val)*((int)b)) + (unsigned char)(val*((int)image(x0,y1)[2]));
   		}

		if(x0>=0 && x0<(int)image.width() && y2>=0 && y2<(int)image.height()){
			image(x0,y2)[0] = (unsigned char)(val*((int)r)) + (unsigned char)((1.0-val)*image(x0,y2)[0]);
			image(x0,y2)[1] = (unsigned char)(val*((int)g)) + (unsigned char)((1.0-val)*image(x0,y2)[1]);
			image(x0,y2)[2] = (unsigned char)(val*((int)b)) + (unsigned char)((1.0-val)*image(x0,y2)[2]);
		}
	}


	void drawPixel(ImageGS8u &image,
		       int x0, int y0,
		       const unsigned char greyLevel){
		int y1 = y0 >> 16;
		int y2 = y1+1;

		double val = static_cast<double>(y0 & 0xFFFF) / static_cast<double> (0xFFFF);

		x0 = x0 >> 16;

		if(x0>=0 && x0<(int)image.width() && y1>=0 && y1<(int)image.height())
			image(x0,y1) = (unsigned char)((1.0-val)*greyLevel);

		if(x0>=0 && x0<(int)image.width() && y2>=0 && y2<(int)image.height())
			image(x0,y2) = (unsigned char)(val*greyLevel);
	}




    /*
     * End of Namespace
     */
}
