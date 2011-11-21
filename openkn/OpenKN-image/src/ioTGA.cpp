/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ioTGA.cpp created in 11 2008.
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
 * External Includes
 */
#include <sstream>
#include <fstream>
#include "iostream"

/*
 * Internal Includes
 */
#include "ioTGA.hpp"
#include "ImageException.hpp"
#include "Image.hpp"

/*
 * Namespace
 */
namespace kn {
		typedef struct str_TGA_Header_loader
		{
			unsigned char size_id_file;
			unsigned char as_color_map;
			unsigned char image_type;
			unsigned char color_map_spec[5]; // We should add information here
			size_t width;
			size_t height;
			int xorigine;
			int yorigine;
			unsigned int depth_per_pixel;
			unsigned char size_alpha_per_pixel; // Unusued
			bool vertical_flip;
			bool horizont_flip;
		} TGA_Header_loader;
		
		/*
		 * Functions definitions
		 */
		void readingError(std::ifstream& is,unsigned char* tab) {
			if (!is.good()) {
				if (tab != NULL) delete[](tab);
				is.close();
				throw ImageException("TGA Loader : Data corruption. Could not read file data","loadFile");
			}
		}

		unsigned char* readColorTGANoCompress(std::ifstream& is,TGA_Header_loader* tgaheader,
																					int& nb_component_per_pixel) {
			unsigned int cswap;
			unsigned char* tabRVB;
			nb_component_per_pixel = 3;
			int d = tgaheader->depth_per_pixel;
			size_t w = tgaheader->width;
			size_t h = tgaheader->height;

			if( (d != 24) && (d !=32) ) {
				is.close();
				throw ImageException("TGA Data file corrupted : color image (no compress) should  have depth 24 or 32","readColorTGANoCompress");
			}

			// TODO : We have a problem for 32 bits encoded pixels. The format is ARGB
			//				so we need to pass ABGR to RGBA
			//std::cerr<<"Here we have depth = "<<d<<std::endl;
			if(d == 32) {
				nb_component_per_pixel = 4;
				is.close();
				throw ImageException("Impossible to read TGA with transparency. Maybe in future release","readColorTGANoCompress");
			}

			size_t size = nb_component_per_pixel * w * h;

			tabRVB = new unsigned char[size];
			if(tabRVB == NULL) {
				is.close();
				throw ImageException("Unable to fetch memory in loading TGA","readColorTGANoCompress");
			}

			is.read((char*)tabRVB,size);
			readingError(is,tabRVB);

			// SWAPING FOR BGR => RGB
			//unsigned char r = 255; // = tab[2] / tab [0] = 255
			//unsigned char b = 255; // = tab[2] / tab [0] = 255
			//unsigned char tab[3];
			//tab[0] = tab[1] = tab[2] = 255;
			/*
			r ^= b; // r = r^b
			std::cerr<<"test : r="<<(int)r<<" b="<<(int)b<<std::endl;
			b ^= r; // b = b^r
			std::cerr<<"test : r="<<(int)r<<" b="<<(int)b<<std::endl;
			r ^= b; // r = r^b
			std::cerr<<"test : r="<<(int)r<<" b="<<(int)b<<std::endl;
			*/
			//r ^= b ^= r ^= b;
			//std::cerr<<"Final test : r="<<(int)r<<" b="<<(int)b<<std::endl;
			//tab[0] ^= (tab[0+2]) ^= (tab[0]) ^= (tab[0+2]);
			//std::cerr<<"Final test : r="<<(int)tab[0]<<" b="<<(int)tab[2]<<std::endl;
			//std::cerr<<"NB comp per pixel : "<<nb_component_per_pixel<<std::endl;
			unsigned char tmp;
			for(cswap = 0; cswap < size; cswap += nb_component_per_pixel) {
				tmp = tabRVB[cswap];
				tabRVB[cswap] = tabRVB[cswap+2];
				tabRVB[cswap+2] = tmp;
				//std::cerr<<"On a "<<(int)tabRVB[cswap]<<"/"<<(int)tabRVB[cswap+1]<<"/"<<(int)tabRVB[cswap+2]<<std::endl;
				//tabRVB[cswap] ^= tabRVB[cswap+2] ^= tabRVB[cswap] ^= tabRVB[cswap+2];
				//std::cerr<<"On a "<<(int)tabRVB[cswap]<<"/"<<(int)tabRVB[cswap+1]<<"/"<<(int)tabRVB[cswap+2]<<std::endl;
			}
			//std::cerr<<"End Swaping"<<std::endl;
			return tabRVB;
		}

		unsigned char* readColorTGACompress(std::ifstream& is,TGA_Header_loader* tgaheader,
																				int& nb_component_per_pixel) {

			size_t pixelcount = 0;
			size_t currentpixel = 0;
			unsigned char *tabRVB = NULL;
			unsigned int currentbyte = 0;
			unsigned char* colorbuffer = NULL;
			size_t size = 0;
			nb_component_per_pixel = 3;

			//std::cerr<<"STARTING COMPRESS !"<<tgaheader->width * tgaheader->height<<std::endl;
			pixelcount = tgaheader->width * tgaheader->height;
			if((tgaheader->depth_per_pixel != 24) && (tgaheader->depth_per_pixel !=32)) {
				is.close();
				throw ImageException("TGA Data file corrupted : color image (compress) should  have depth 24 or 32","readColorTGANoCompress");
			}
			if(tgaheader->depth_per_pixel == 32) {
				nb_component_per_pixel = 4;
				is.close();
				throw ImageException("Impossible to read TGA with transparency. Maybe in future release","readColorTGANoCompress");
			}
			//std::cerr<<"DEPTH : "<<nb_component_per_pixel<<std::endl;

			size = (nb_component_per_pixel * pixelcount);
			tabRVB = new unsigned char[size];
			if(tabRVB == NULL) {
				is.close();
				throw ImageException("Unable to fetch memory in loading TGA","readColorTGANoCompress");
			}
			colorbuffer = new unsigned char[nb_component_per_pixel];
			if(colorbuffer == NULL) {
				is.close();
				throw ImageException("Unable to fetch memory in loading TGA","readColorTGANoCompress");
			}
			do {
				unsigned char chunkheader = 0;
				is.read((char*)(&chunkheader),1);
				readingError(is,tabRVB);

				if(chunkheader < 128) {
					// We got raw packets ...
					short counter;
					chunkheader++; // The count represent nb pixel - 1 so we need to add 1
					for(counter = 0; counter < chunkheader; counter++) {
						is.read((char*)colorbuffer,nb_component_per_pixel);
						readingError(is,tabRVB);

						// * write to memory * /
						tabRVB[currentbyte     ] = colorbuffer[2];
						tabRVB[currentbyte + 1 ] = colorbuffer[1];
						tabRVB[currentbyte + 2 ] = colorbuffer[0];

						if(nb_component_per_pixel == 4) {
							tabRVB[currentbyte + 3] = colorbuffer[3];
						}

						currentbyte += nb_component_per_pixel;
						currentpixel++;

						if(currentpixel > pixelcount) {
							if (tabRVB != NULL) delete[](tabRVB);
							tabRVB = NULL;
							is.close();
							throw ImageException("TGA Loader : Error too many pixels read","loadFile");
						}
					}
				}
				else {
					// We got Run-Length Packet ...
					short counter;
					chunkheader -= 127;
					is.read((char*)colorbuffer,nb_component_per_pixel);
					readingError(is,tabRVB);

					for(counter = 0; counter < chunkheader; counter++) {
						tabRVB[currentbyte     ] = colorbuffer[2];
						tabRVB[currentbyte + 1 ] = colorbuffer[1];
						tabRVB[currentbyte + 2 ] = colorbuffer[0];
						if(nb_component_per_pixel == 4) tabRVB[currentbyte + 3] = colorbuffer[3];

						currentbyte += nb_component_per_pixel;
						currentpixel++;
						if(currentpixel > pixelcount){
							if (tabRVB != NULL) delete[](tabRVB);
							tabRVB = NULL;
							is.close();
							throw ImageException("TGA Loader : Error too many pixels read","loadFile");
						}
					}
				}
			}
			while(currentpixel < pixelcount);

			return tabRVB;
		}

		int loadTGA(Image<unsigned char>& res,const std::string& filename) {
			TGA_Header_loader tgaheader;
			unsigned char Header[18];
			unsigned char* thebuffer;
			std::ifstream is;
			std::stringstream serr;
			//TGA_file_type type_of_this_image;
			bool no_data = false;
			// Storing the header completely
			char descriptor;

			// STEP 0 : WE CHECK THAT THE IMAGE IS NOT ALREADY ALLOCATED
			if (res.size()>0) {
				throw ImageException("Image already allocated. Cannot store TGA image in that image.","loadImage");
			}

			is.open(filename.c_str(),std::ios::in);
			if (is == NULL) {
				throw ImageException("TGA Loader : Error could not read file "+filename,"loadImage");
			}
			
			is.read((char*)Header,18);
			if (is.rdstate() == std::ios_base::failbit) {
				is.close();
				throw ImageException("TGA Loader : Error could not read file header","loadImage");
			}
			tgaheader.size_id_file = Header[0];
			//std::cerr<<"Id file:"<<(int)tgaheader.size_id_file<<std::endl;
			tgaheader.as_color_map = Header[1];
			//std::cerr<<"Type image:"<<(int)tgaheader.as_color_map<<std::endl;
			tgaheader.image_type = Header[2];
			//std::cerr<<"Type image:"<<(int)tgaheader.image_type<<std::endl;

			if (tgaheader.as_color_map == 1) {
				// Header from 3 to 7...
				is.close();
				throw ImageException("TGA Loader : We do not handle TGA with color map","loadImage");
			}

			tgaheader.xorigine = Header[9]*256 + Header[8];
			tgaheader.yorigine = Header[11]*256 + Header[10];
			tgaheader.width = *((unsigned short*) (Header+12));
			tgaheader.height = *((unsigned short*) (Header+14));
			// Header[16] is the depth (pixelcount)
			tgaheader.depth_per_pixel = Header[16];
			descriptor = Header[17];
			tgaheader.size_alpha_per_pixel = (descriptor & 0x0F);
			//std::cerr<<"P"<<(int)(descriptor & 0x20)<<std::endl;
			tgaheader.vertical_flip = false;
			if (descriptor & 0x20) {tgaheader.vertical_flip = true;}
			tgaheader.horizont_flip = false;
			if (descriptor & 0x10) {tgaheader.horizont_flip = true;}
			//std::cerr<<"FLIP : "<<tgaheader.vertical_flip<<" / "<<tgaheader.horizont_flip<<std::endl;

			// Some tests on header data
			if (tgaheader.horizont_flip) {
				is.close();
				throw ImageException("TGA Loader : Not handling horizontaly mirrored image","loadImage");
			}
			if ((tgaheader.width <= 0) || (tgaheader.height <= 0)) {
				is.close();
				throw ImageException("TGA Loader : Not handling negative or null sized image","loadImage");
			}
			if ((tgaheader.xorigine != 0) || (tgaheader.yorigine != 0)) {
				//is.close();
				serr << "TGA Loader : Not handling translated image(";
				serr << tgaheader.xorigine<< "/"<<tgaheader.yorigine<<")";
				//std::cerr<<serr.str()<<std::endl;
				//throw ImageException(serr.str(),"loadImage");
			}
			

			// READING ID OF TGA FILE
			if (tgaheader.size_id_file > 0) {
				std::cerr<<"Reading id file"<<std::endl;
				char *tmp = new char[tgaheader.size_id_file];
				is.read(tmp,tgaheader.size_id_file);
				if (is.rdstate() == std::ios_base::failbit) {
					is.close();
					throw ImageException("TGA Loader : Error could not read id file","loadImage");
				}
			}

			// TODO : DEALING WITH COLOR TABLE WILL BE DONE HERE !

			// READING IMAGE DATA
			//std::cerr<<"STARTING READING"<<std::endl;
			int componentperpixel = 0;
			switch(tgaheader.image_type) {
				case (NONE_TGA) :
					no_data = true;
					break;
				case (COLOR_TGA) :
					thebuffer = readColorTGANoCompress(is,&tgaheader,componentperpixel);
					break;
				case (COLOR_RLE_TGA) :
					thebuffer = readColorTGACompress(is,&tgaheader,componentperpixel);
					break;
				case (INDEXED_TGA) :
				case (INDEXED_RLE_TGA) :
				case (GS_TGA) :
				case (GS_RLE_TGA) :
					is.close();
					serr << "TGA Loader : Not handling this type of image (";
					serr << tgaheader.image_type<< ")";
					throw ImageException(serr.str(),"loadImage");
					break;
				default :
					is.close();
					throw ImageException("TGA Loader : data failure","loadImage");
			}
			//std::cerr<<"STOP READING"<<std::endl;
			//std::cerr<<"TESTING FINAL buffer : ";
			//for(int i=0;i<4*4;i++) {
			//	if (i%4 == 0) std::cerr<<std::endl;
			//	for(int j=0;j<3;j++) std::cerr<<(int)thebuffer[i*3+j]<<" ";
			//	std::cerr<<std::endl;
			//}


			// HANDLING VERTICAL FLIP ...
			if (!tgaheader.vertical_flip) {
				unsigned char* tmp = new unsigned char[tgaheader.width*tgaheader.height*tgaheader.depth_per_pixel/8];
				if (tmp == NULL) {
					is.close();
					throw ImageException("TGA Loader : unable to fetch memory","loadImage");
				}
				size_t sizeoneline = tgaheader.width*tgaheader.depth_per_pixel/8;
				for(size_t i=0;i<tgaheader.height;i++) {
					// La ligne du bas va en haut
					memcpy(tmp+(i*sizeoneline),thebuffer+(tgaheader.height-1-i)*sizeoneline,sizeoneline);
				}
				memcpy(thebuffer,tmp,sizeoneline*tgaheader.height);
				delete[](tmp);
			}

			// Building Image
			try {
				if (no_data) {
					//std::cerr<<"No data..."<<std::endl;
					res.buildImageFromBuffer(tgaheader.width,tgaheader.height,componentperpixel,NULL);
				}
				else {
					//std::cerr<<"With data..."<<tgaheader.width<<" / "<<tgaheader.height;
					//std::cerr<<" / "<<componentperpixel<<std::endl;
					res.buildImageFromBuffer(tgaheader.width,tgaheader.height,
																		componentperpixel,thebuffer);
					if (thebuffer != NULL) delete[](thebuffer);
				}
			}
			catch (ImageException &e) {
				// Should absolutely not happens
				if (thebuffer != NULL) delete[](thebuffer);
				throw ImageException("Exception rising from Image library : "+e.errorString(),"loadFile");
			}

			return tgaheader.image_type;
		}

	/*
	 * End of Namespace
	 */
}
