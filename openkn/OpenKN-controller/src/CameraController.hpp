/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Webcam.hpp created in 10 2008.
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
#ifndef __OPENKN_CONTROLLER__CAMERACONTROLLER_HPP__
#define __OPENKN_CONTROLLER__CAMERACONTROLLER_HPP__

/*
 * Internal Includes
 */
#include "ControllerException.hpp"


/*
 * Namespace
 */
namespace kn{
   


	/**
	 * Default parameters for a camera (size and device's name)
	 */
	struct CameraParams 
	{

        std::string devicename;
        
        size_t width;

        size_t height;

		/**
		 * Default constructor
		 */
		CameraParams(const std::string& dn = "", 
                     const size_t& expectedwidth = 320, 
                     const size_t& expectedheight = 240)
			:devicename(dn),width(expectedwidth),height(expectedheight){}
	 
	};
    

	/**
	 * Abstract class for camera control
	 */
	class CameraController
	{
	  
	protected:

		/**
		 * \brief Name of the device
		 */
		std::string devicename;

		/**
		 * \brief Width of the image captured by the webcam
		 */
		size_t camwidth;

		/**
		 * \brief Height of the image captured by the webcam
		 */
		size_t camheight;

	  
	public:
		/*
		 * Functions definitions
		 */

		/**
		 * \brief Destructor
		 */ 
		virtual ~CameraController(void){}
	  
		/**
		 * \brief Activates the camera
		 */
		virtual void openDevice(void) = 0;

		/**
		 * \brief Disables the webcam
		 */
		virtual void closeDevice(void) = 0;

		/**
		 * \brief Start the capture of the images
		 */
		virtual void start(void) = 0;

		/**
		 * \brief Stop the capture of the images
		 */
		virtual void stop(void) = 0;
	  
		/**
		 * \brief Get the last image captured
		 * 
		 * \return array of RGB24 data
		 */
		virtual unsigned char * getImage(void) = 0;

		/**
		 * \brief Get width of the images captured by the webcam
		 * 
		 * \return width
		 */
		virtual size_t width(void) const = 0;

		/**
		 * \brief Get height of the images captured by the webcam
		 * 
		 * \return height
		 */
		virtual size_t height(void) const = 0;
	  

	};
 
	/*
	 * End of Namespace
	 */
}

#endif
