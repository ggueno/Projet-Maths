/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_DVCam.hpp created in 03 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-controller.
 *
 * The OpenKraken-controller is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-controller is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_CONTROLLER__LIN_DVCAM_HPP__
#define __OPENKN_CONTROLLER__LIN_DVCAM_HPP__

/*
 * Internal Includes
 */
#include "CameraController.hpp"

/*
 * External Includes
 */
#include <libiec61883/iec61883.h>
#include <boost/thread.hpp>

#include <libdv/dv_types.h>
#include <libdv/dv.h>

/*
 * Namespace
 */
namespace kn{

	/**
	 * Default parameters for a DV Camera
     *
     * As a DV camera only works with a port number, devicename is useless and is set to ""
     * \author Frankoi
	 */
    struct DVCamParams : CameraParams
	{
        
        int port;

		/**
		 * Default constructor
		 */
		DVCamParams(const int& p = 0,
                    const std::string& dn = "", 
                    const size_t& expectedwidth = 720, 
                    const size_t& expectedheight = 576)
			:CameraParams(dn,expectedwidth,expectedheight),port(p) {}
        
	};



/**
 * \brief Class for DV cameras managing
 * 
 * Typical DV resolution is 720x576.
 *
 * This class manages only video not sound
 *
 * libiec61883 is used for firewire communication and libdv to decode a dv frame.
 *
 * The DVcam manager uses a buffer of size 4 to store the grabbed images. This means that each fourth capture images will be replaced.
 *
 * Special recommandations :
 * If your program reports an error caused by the firewire port then you will have to check if files in /dev/dv1394/ and file /dev/raw1394 have permission level for everyone. Otherwise you will have to do :
 *
 * - sudo chmod -R 777 /dev/dv1394* 
 *
 * - sudo chmod 777 /dev/raw1394
 *
 * The class have been tested with :
 *
 * - SONY Digital Video Camera Recorder DCR-TRV60E
 *
 * \author Frankoi
 *
 */


	class DVCam :CameraController
	{
	private:

		/**
		 * \brief Object to grad a dv frame
		 */
		iec61883_dv_fb_t frame;

		/**
		 * \brief Handle attached to a dv device
		 */
		raw1394handle_t handle;

		/**
		 * \brief Decoder to transform a DV frame to RGB data
		 */ 
		dv_decoder_t *td;

		/**
		 * \brief Position in a array of the last available RGB frame
		 */	  
		unsigned int currentframe;

		/**
		 * \brief Size of the RGB frame Array (Image buffering)
		 */	 
		static const size_t maxframe = 10;

		/**
		 * \brief Specifies how data have to be saved
		 */
		int pitches[1];

		/**
		 * \brief Array where RGB data will be saved
		 */
		unsigned char ***pixels;
			
		/**
		 * \brief Define if the dvcam is grabbing images or not 
		 */
		bool isgrabbing;	

		/**
		 * \brief check if the the dvcam have been enabled
		 */
		bool isenable;

		/**
		 * \brief Thread object
		 */
		boost::thread *thrd;
			
		/**
		 * \brief Mutex 
		 */
		boost::mutex dvmutex;

		/**
		 * \brief Function to capture data over the raw1394 device
		 *
		 * Have to be used with a thread.
		 * \author Frankoi
		 */
		void Handler(void);

		/**
		 * \brief Read a DV frame and convert it in RGB data 
		 *
		 * \param data array of data from DV
		 * \return 0 if success otherwise -1
		 * \author Frankoi
		 */
		int ReadFrame(unsigned char *data);

		/**
		 * \brief Static function called as a thread
		 *
		 * \param data array of data from DV
		 * \param length size of the data
		 * \param complete specify if the frame is complete or not
		 * \param callback_data is a DVCam object
		 * \return 0 if success otherwise -1
		 * \author Frankoi
		 */
		static int callbackReadFrame(unsigned char *data, 
									 int length, 
									 int complete, 
									 void *callback_data);

        void ResetHandler( void );
 
        static int ResetHandlerProxy( raw1394handle_t handle, unsigned int generation );

	public:

			
		/**
		 * \brief Default constructor for a DVCam
		 * \author Frankoi
		 */
		DVCam(void):CameraController(){
			handle = 0;
			isenable=false;
			isgrabbing=false;
			td=0;
			pitches[0]=720*3;
			pitches[1]=pitches[2]=0;
			pixels = new unsigned char** [maxframe];
			for(unsigned int i = 0; i < maxframe; ++i){
				pixels[i] = new unsigned char* [3];
				pixels[i][0] = new unsigned char [720*576*3];
			}
			thrd=0;
			currentframe = 0;
		}

		/**
		 * \brief Destructor
		 *
		 * The destructor also closes the device
		 *
		 * \author Frankoi
		 */
		~DVCam(void){
			closeDevice();
			if(pixels){
				for(unsigned int i = 0; i < maxframe; ++i){
					if(pixels[i]){
						if(pixels[i][0])
							delete[] pixels[i][0];
						delete[] pixels[i];
					}
				}
				delete[] pixels;
			}
		}

		/**
		 * \brief open a DV device according to a port number
		 *
		 * Port for the first DVcam should be 0, then 1 for the second one, etc...
		 *
		 * \param params DVCam parameters
		 * \see closeDevice
		 * \author Frankoi
		 */
		void openDevice(const DVCamParams& params);

		void openDevice(void){openDevice(DVCamParams());}

		/**
		 * \brief close a DV device
		 *
		 * If the device hasn't be openened then nothing happened.
		 * The function stops the DV capture.
		 *
		 * \see openDevice
		 * \author Frankoi
		 */
		void closeDevice(void);

		/**
		 * \brief Start DV capture
		 *
		 * Images grabbing starts until a call to stop or closeDevice methods.
		 *
		 * \see stop
		 * \author Frankoi
		 */
		void start(void);

		/**
		 * \brief Stop DV capture
		 *
		 * Images grabbing is stopped for the moment.
		 *
		 * \see start
		 * \author Frankoi
		 */
		void stop();

		/**
		 * \brief Returns a	 pointer on the last image captured
		 *
		 * Since it returns a pointer, this means that the dvcam manager can change the data without warnings. So if you want to use these data during a long time, tou will have to make a copy.
		 *
		 * ! Don't try to delete the returned pointer
		 *
		 * It starts capture if necessary.
		 * 
		 * \return pointer to an array of RGB24 data
		 * \author Frankoi
		 */
		unsigned char* getImage(void);

		/**
		 * \brief Returns width of the images captured by the camera
		 * 
		 * Should be 720.
		 *
		 * \return width
		 * \author Frankoi
		 */
		inline size_t width(void) const {return this->camwidth;}

		/**
		 * \brief Returns height of the images captured by the camera
		 * 
		 * Should be 576.
		 *
		 * \return height
		 * \author Frankoi
		 */
		inline size_t height(void) const {return this->camheight;}

		/**
		 * \brief Returns if camera have been started
		 * 
		 * \return true if the camera has the start flag
		 * \author Frankoi
		 */
		inline bool isStarted(void) const {return isgrabbing;}

		/**
		 * \brief Returns if the device have been opened
		 * 
		 * \return true if the device is opened
		 * \author Frankoi
		 */
		inline bool isOpen(void) const {return isenable;}


	};
}

#endif
