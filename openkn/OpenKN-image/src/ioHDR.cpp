/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ioHDR.cpp created in 11 2008.
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
#include "ioHDR.hpp"
#include "ImageException.hpp"

/*
 * External Includes
 */
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstdlib>//#include <malloc.h> 
#include <string.h>
#include <ctype.h>

/* flags indicating which fields in an rgbe_header_info are valid */
#define RGBE_VALID_PROGRAMTYPE 0x01
#define RGBE_VALID_GAMMA       0x02
#define RGBE_VALID_EXPOSURE    0x04

/* return codes for rgbe routines */
#define RGBE_RETURN_SUCCESS 0
#define RGBE_RETURN_FAILURE -1
/* offsets to red, green, and blue components in a data (float) pixel */
#define RGBE_DATA_RED    0
#define RGBE_DATA_GREEN  1
#define RGBE_DATA_BLUE   2
/* number of floats per pixel */
#define RGBE_DATA_SIZE   3


/*
 * Namespace
 */
namespace kn{

	typedef struct {
		int valid;            /* indicate which fields are valid */
		char programtype[16]; /* listed at beginning of file to identify it 
													 * after "#?".  defaults to "RGBE" */ 
		float gamma;          /* image has already been gamma corrected with 
													 * given gamma.  defaults to 1.0 (no correction) */
		float exposure;       /* a value of 1.0 in an image corresponds to
													 * <exposure> watts/steradian/m^2. 
													 * defaults to 1.0 */
	} rgbe_header_info;



	enum rgbe_error_codes {
		rgbe_read_error,
		rgbe_write_error,
		rgbe_format_error,
		rgbe_memory_error
	};


	/* standard conversion from float pixels to rgbe pixels */
	/* note: you can remove the "inline"s if your compiler complains about it */
	inline void float2rgbe(unsigned char rgbe[4], float red, float green, float blue)
	{
		float v;
		int e;

		v = red;
		if (green > v) v = green;
		if (blue > v) v = blue;
		if (v < 1e-32) {
			rgbe[0] = rgbe[1] = rgbe[2] = rgbe[3] = 0;
		}
		else {
			v = (float)frexp(v,&e) * 256.0f/v;
			rgbe[0] = (unsigned char) (red * v);
			rgbe[1] = (unsigned char) (green * v);
			rgbe[2] = (unsigned char) (blue * v);
			rgbe[3] = (unsigned char) (e + 128);
		}
	}

	/* standard conversion from rgbe to float pixels */
	/* note: Ward uses ldexp(col+0.5,exp-(128+8)).  However we wanted pixels */
	/*       in the range [0,1] to map back into the range [0,1].            */
	inline void rgbe2float(float *red, float *green, float *blue, unsigned char rgbe[4])
	{
		double f;

		if (rgbe[3]) {   /*nonzero pixel*/
			f = ldexp(1.0f,(int)rgbe[3]-(int)(128+8));
			*red = (float)((rgbe[0]+0.5) * f);
			*green = (float)((rgbe[1]+0.5) * f);
			*blue = (float)((rgbe[2]+0.5) * f);
		}
		else
			*red = *green = *blue = 0.0;
	}


	/* default error routine.  change this to change error handling */
	static ImageException rgbe_error(int rgbe_error_code, char *msg) {
		std::stringstream serr;
		switch (rgbe_error_code) {
			case rgbe_read_error:
				return ImageException("RGBE read error","loadImageHDR");
			case rgbe_write_error:
				return ImageException("RGBE write error","loadImageHDR");
			case rgbe_format_error:
				serr<<"RGBE bad file format: "<<msg;
				return ImageException(serr.str(),"loadImageHDR");
				//fprintf(stderr,"RGBE bad file format: "+msg+"\n");
				break;
			default:
			case rgbe_memory_error:
				serr<<"RGBE error: "<<msg;
				return ImageException(serr.str(),"loadImageHDR");
		}
		return ImageException();
	}

	/* minimal header reading.  modify if you want to parse more information */
	int RGBE_ReadHeader(FILE *fp, int *width, int *height, rgbe_header_info *info)
	{
		char buf[128];
		int found_format;
		float tempf;
		unsigned int i;

		found_format = 0;
		if (info) {
			info->valid = 0;
			info->programtype[0] = 0;
			info->gamma = info->exposure = 1.0;
		}
		if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == NULL)
			throw rgbe_error(rgbe_read_error,NULL);

		if ((buf[0] != '#')||(buf[1] != '?')) {
			/* if you want to require the magic token then uncomment the next line */
			throw rgbe_error(rgbe_format_error,(char*)"bad initial token");
		}
		else if (info) {
			info->valid |= RGBE_VALID_PROGRAMTYPE;
			for(i=0;i<sizeof(info->programtype)-1;i++) {
				if ((buf[i+2] == 0) || isspace(buf[i+2]))
					break;
				info->programtype[i] = buf[i+2];
			}
			info->programtype[i] = 0;
			if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
				throw rgbe_error(rgbe_read_error,NULL);
		}

		for(;;) {
			if ((buf[0] == 0)||(buf[0] == '\n'))
				throw rgbe_error(rgbe_format_error,(char*)"no FORMAT specifier found");
			else if (strcmp(buf,"FORMAT=32-bit_rle_rgbe\n") == 0)
				break;       /* format found so break out of loop */
			else if (info && (sscanf(buf,"GAMMA=%g",&tempf) == 1)) {
				info->gamma = tempf;
				info->valid |= RGBE_VALID_GAMMA;
			}
			else if (info && (sscanf(buf,"EXPOSURE=%g",&tempf) == 1)) {
				info->exposure = tempf;
				info->valid |= RGBE_VALID_EXPOSURE;
			}
			if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
				throw rgbe_error(rgbe_read_error,NULL);
		}

#if 0
		if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
			throw rgbe_error(rgbe_read_error,NULL);
		if (strcmp(buf,"\n") != 0)
			throw rgbe_error(rgbe_format_error,"missing blank line after FORMAT specifier");
#endif

		for(;;) {
			if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
				throw rgbe_error(rgbe_read_error,NULL);

			if (sscanf(buf,"-Y %d +X %d",height,width) == 2)
				break;
		}

		return RGBE_RETURN_SUCCESS;
	}

	/* simple read routine.  will not correctly handle run length encoding */
	int RGBE_ReadPixels(FILE *fp, float *data, int numpixels)
	{
		unsigned char rgbe[4];

		while(numpixels-- > 0) {
			if (fread(rgbe, sizeof(rgbe), 1, fp) < 1)
				throw rgbe_error(rgbe_read_error,NULL);
			//std::cerr<<"We have : "<<(int)rgbe[0]<<" / "<<(int)rgbe[1]<<" / "<<(int)rgbe[2]<<" / "<<(int)rgbe[3]<<std::endl;
			rgbe2float(&data[RGBE_DATA_RED],&data[RGBE_DATA_GREEN],&data[RGBE_DATA_BLUE],rgbe);
			//std::cerr<<"S=>WE GOT : "<<data[0]<<" / "<<data[1]<<" / "<<data[2]<<std::endl;
			data += RGBE_DATA_SIZE;
		}
		return RGBE_RETURN_SUCCESS;
	}


	int RGBE_ReadPixels_Raw(FILE *fp, unsigned char *data, int numpixels)
	{
		if ((int)fread(data, 4, numpixels, fp) < numpixels)
			throw rgbe_error(rgbe_read_error,NULL);

		return RGBE_RETURN_SUCCESS;
	}

	int RGBE_ReadPixels_RLE(FILE *fp, float *data, int scanline_width,int num_scanlines)
	{
		unsigned char rgbe[4], *scanline_buffer, *ptr, *ptr_end;
		int i, count;
		unsigned char buf[2];

		if ((scanline_width < 8)||(scanline_width > 0x7fff))
			/* run length encoding is not allowed so read flat*/
			return RGBE_ReadPixels(fp,data,scanline_width*num_scanlines);

		scanline_buffer = NULL;
		/* read in each successive scanline */
		while(num_scanlines > 0) {
			if (fread(rgbe,sizeof(rgbe),1,fp) < 1) {
				free(scanline_buffer);
				throw rgbe_error(rgbe_read_error,NULL);
			}
			if ((rgbe[0] != 2)||(rgbe[1] != 2)||(rgbe[2] & 0x80)) {
				/* this file is not run length encoded */
				rgbe2float(&data[0],&data[1],&data[2],rgbe);
				//std::cerr<<"WE GOT : "<<data[0]<<" / "<<data[1]<<" / "<<data[2]<<std::endl;
				data += RGBE_DATA_SIZE;
				free(scanline_buffer);
				return RGBE_ReadPixels(fp,data,scanline_width*num_scanlines-1);
			}
			if ((((int)rgbe[2])<<8 | rgbe[3]) != scanline_width) {
				free(scanline_buffer);
				throw rgbe_error(rgbe_format_error,(char*)("wrong scanline width"));
			}
			if (scanline_buffer == NULL)
				scanline_buffer = (unsigned char *) malloc(sizeof(unsigned char)*4*scanline_width);
			if (scanline_buffer == NULL) 
				throw rgbe_error(rgbe_memory_error,(char*)("unable to allocate buffer space"));
	    
			ptr = &scanline_buffer[0];
			/* read each of the four channels for the scanline into the buffer */
			for(i=0;i<4;i++) {
				ptr_end = &scanline_buffer[(i+1)*scanline_width];
				while(ptr < ptr_end) {
		if (fread(buf,sizeof(buf[0])*2,1,fp) < 1) {
			free(scanline_buffer);
			throw rgbe_error(rgbe_read_error,NULL);
		}
		if (buf[0] > 128) {
			/* a run of the same value */
			count = buf[0]-128;
			if ((count == 0)||(count > ptr_end - ptr)) {
				free(scanline_buffer);
				throw rgbe_error(rgbe_format_error,(char*)("bad scanline data"));
			}
			while(count-- > 0)
				*ptr++ = buf[1];
		}
		else {
			/* a non-run */
			count = buf[0];
			if ((count == 0)||(count > ptr_end - ptr)) {
				free(scanline_buffer);
				throw rgbe_error(rgbe_format_error,(char*)("bad scanline data"));
			}
			*ptr++ = buf[1];
			if (--count > 0) {
				if (fread(ptr,sizeof(*ptr)*count,1,fp) < 1) {
					free(scanline_buffer);
					throw rgbe_error(rgbe_read_error,NULL);
				}
				ptr += count;
			}
		}
				}
			}
			/* now convert data from buffer into floats */
			for(i=0;i<scanline_width;i++) {
				rgbe[0] = scanline_buffer[i];
				rgbe[1] = scanline_buffer[i+scanline_width];
				rgbe[2] = scanline_buffer[i+2*scanline_width];
				rgbe[3] = scanline_buffer[i+3*scanline_width];
				rgbe2float(&data[RGBE_DATA_RED],&data[RGBE_DATA_GREEN],&data[RGBE_DATA_BLUE],rgbe);
				//std::cerr<<"=WE GOT : "<<data[0]<<" / "<<data[1]<<" / "<<data[2]<<std::endl;
				data += RGBE_DATA_SIZE;
			}
			num_scanlines--;
		}
		free(scanline_buffer);
		return RGBE_RETURN_SUCCESS;
	}

	/*
		* Functions definitions
		*/
	int loadHDR(Image<float>& res,const std::string& filename) {
		float* thebuffer;
		size_t w_size,h_size;
		//unsigned int nb_component;
		std::ifstream is;
		std::stringstream serr;
		rgbe_header_info header_stock;

		FILE * infile;			/* source file */

		// STEP 0 : WE CHECK THAT THE IMAGE IS NOT ALREADY ALLOCATED AND OPEN THE FILE (IF IT EXISTS)
		if (res.size()>0) {
			throw ImageException("Image already allocated. Cannot store HDR image in that image.","loadImage");
		}
		//std::cerr<<"Charge fichier "<<filename<<std::endl;
		infile = fopen(filename.c_str(),"rb");
		if (infile == NULL) {
			throw ImageException("Error could not read file "+filename,"loadImageHDR");
		}

		// STEP 1 : READING HEADER ...
		int succes;
		int i_width=-1,i_height=-1;
		succes = RGBE_ReadHeader(infile,&i_width,&i_height,&header_stock);
		if (i_width == -1 || i_height == -1) {
			serr << "Image size was impossible to fetch from header ("<<i_width<<"/"<<i_height<<")";
			throw ImageException(serr.str(),"loadImageHDR");
		}
		if (succes!= RGBE_RETURN_SUCCESS) {
			throw ImageException("Something was wrong and no throw by reader function","loadImageHDR");
		}
		w_size = i_width;
		h_size = i_height;
		//std::cerr<<"expo : "<<header_stock.exposure<<std::endl;
		//std::cerr<<"gama : "<<header_stock.gamma<<std::endl;
		//std::cerr<<"Size : "<<w_size<<" / "<<h_size<<std::endl;

		// STEP 2 : BUILDING THE BUFFER
		thebuffer = new float[3*w_size*h_size];
		if (thebuffer == NULL) {
			throw ImageException("Unable to get memory when loading HDR","loadImageHDR");
		}

		// STEP 3 : READING IMAGE DATA ...
		try {
			succes = RGBE_ReadPixels_RLE(infile,thebuffer,i_width,i_height);
			res.buildImageFromBuffer(w_size,h_size,3,thebuffer);
		}
		catch (ImageException &e) {
			// Should absolutely not happens
			if (thebuffer != NULL) delete[](thebuffer);
			throw e;
		}
		if (thebuffer != NULL) delete[](thebuffer);
		fclose(infile);

		return 1;
	}

	/*
	 * End of Namespace
	 */
}
