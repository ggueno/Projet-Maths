/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * LIN_V4L2Webcam.hpp created in 10 2008.
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
#ifndef __OPENKN_CONTROLLER__LIN_V4L2WEBCAM_HPP__
#define __OPENKN_CONTROLLER__LIN_V4L2WEBCAM_HPP__


/*
 * Internal Includes
 */
#include "CameraController.hpp"
#include "webcamstools/uvcvideo.h"

/*
 * External Includes
 */
#include <linux/videodev2.h>

/*
 * Namespace
 */
namespace kn{

	enum WebcamControl { WEBCAM_BRIGHTNESS = V4L2_CID_BRIGHTNESS,
						 WEBCAM_CONTRAST = V4L2_CID_CONTRAST,
						 WEBCAM_SATURATION = V4L2_CID_SATURATION,
						 WEBCAM_GAIN = V4L2_CID_GAIN,
						 WEBCAM_SHARPNESS = V4L2_CID_SHARPNESS,
						 WEBCAM_GAMMA = V4L2_CID_GAMMA,
						 WEBCAM_EXPOSURE = V4L2_CID_EXPOSURE_ABSOLUTE,
						 WEBCAM_EXPOSURE_AUTO = V4L2_CID_EXPOSURE_AUTO,
						 WEBCAM_WB_AUTO = V4L2_CID_WHITE_BALANCE_TEMPERATURE_AUTO,
						 WEBCAM_WB = V4L2_CID_WHITE_BALANCE_TEMPERATURE};

	enum WebcamToggleControl {WEBCAM_EXPOSURE_ON = 3, WEBCAM_EXPOSURE_OFF = 2, WEBCAM_WB_ON = 1, WEBCAM_WB_OFF = 0};

	/**
	 * Enumeration of formats available for webcams
	 */
	enum WebcamFormat{FMT_MJPEG,FMT_YUYV};

	/**
	 * Enumeration of grabbing methods available for webcams
	 */
	enum GrabMethod { READ_METHOD, MMAP_METHOD};


	/**
	 * Default parameters for a V4L2 webcam
     *
     * A V4L2 webcam defines capture format, grabbing method and framerate parameters in addition to default parameters
     * \author Frankoi
	 */
	struct V4L2WebcamParams : CameraParams
	{

		/**
		 * Format for webcam captures
		 */
		WebcamFormat fmt;

		/**
		 * Images grabbing method
		 */
		GrabMethod grab;

		/**
		 * Framerate of the webcam
		 */
		unsigned int framerate;

		/**
		 * Force
		 */
		bool force;

		/**
		 * Default constructor
		 */
		V4L2WebcamParams(const std::string& dn = "/dev/video0",
                         const size_t& expectedwidth = 320,
                         const size_t& expectedheight = 240,
                         const WebcamFormat& wf = FMT_YUYV,
                         const GrabMethod& gm = MMAP_METHOD,
                         const unsigned int& fps = 30,
                         const bool& f = false)
			:CameraParams(dn,expectedwidth,expectedheight),fmt(wf),grab(gm),framerate(fps),force(f) {}

	};

	static const V4L2WebcamParams defaultV4L2WebcamParams;

    /*
     * Functions definitions
     */

    /**
     * Class Defining V4L2 webcam
     *
     * This class only works with V4L2 compatible webcams
     *
     * Special recommandations :
     * Sometimes, under Linux, the webcam could turns out of control. You will have to unplug and replug the webcam to get back to normal.
     * If you nocite luminosity problems (dark image, white image, brightness, exposure, etc.), you can also use this method. However, it can be useless due to uvcvideo driver limits so a solution is to restart the driver :
     *
     * - sudo rmmod uvcvideo
     * - sudo modprobe uvcvideo
     *
     *
     * This class have been tested with :
     *
     * - Logitech QuickCam Pro 9000
     * - Logitech QuickCam Fusion
     *
     * Depending on the webcam, some controls are enabled or disabled like auto-exposure, auto-brightness...
     * Please use v4l-info command to check crontrols avaibility.
     *
     * \author Frankoi
     */
    class V4L2Webcam : public CameraController {

    private:

        /// @cond

        struct V4L2_Buffer {
            void * start;
            size_t length;
        };

        /// @endcond

        /**
         * \brief V4L2 structure that contain webcam capabilities
         */
        struct v4l2_capability cap;

        /**
         * \brief V4L2 structure that contain webcam format
         */
        struct v4l2_format fmt;

        /**
         * \brief V4L2 structure that contain webcam buffer
         */
        struct v4l2_buffer buf;

        /**
         * \brief V4L2 structure that contain webcam requested buffers
         */
        struct v4l2_requestbuffers rb;

		/**
		 * \brief Grabbing method used to capture the images and defined by the user
		 */
		GrabMethod gb;

		/**
		 * \brief ID of the descriptor to access to the webcam
		 */
		int filedescriptor;


        /**
         * \brief Array of pointers to arrays that will containt bufferized images
         * This variable is only used with mmap method
         */
        void** buffersmmap;

        /**
         * \brief Buffer wherein grabbed images are copied
         * This variable is only used with read method
         */
        V4L2_Buffer* buffersread;

        // Arrays to reconstruct the image
        /**
         * \brief Temporary buffer used for data conversion
         */
        unsigned char *tmpbuffer;

        /**
         * \brief Buffer that contain the image grabbed with the webcam
         * The image is in a specific format (AFAIK in yuvy format)
         */
        unsigned char *framebuffer;

        /**
         * \brief Buffer that contain the image in rgb24 format
         */
        unsigned char *outputbuffer;

        /**
         * \brief Define if the webcam is grabbing images or not
         */
        bool isgrabbing;

        /**
         * \brief check if the the webcam have been enabled
         */
        bool isenable;

        /**
         * \brief Local structure to set controls
         */
        struct v4l2_control control_s;

        /**
         * \brief Local structure to query controls
         */
        struct v4l2_queryctrl queryctrl;

    public:

        /**
         * \brief Default constructor for a V4L2 Webcam
         *
         * It doesn't open the device.
         *
         * \author Frankoi
         */
        V4L2Webcam(void):CameraController(){
            outputbuffer = 0;
            framebuffer = 0;
            tmpbuffer = 0;
            buffersread = 0;
            buffersmmap = 0;
            isenable = false;
            isgrabbing = false;
            filedescriptor = -1;
        };

        /**
         * /brief Destructor
         *
         * The destructor closes the device.
         *
         * \author Frankoi
         */
        ~V4L2Webcam(void){closeDevice();};

    private:
        /**
         * \brief Checks if format and grabbing method is available for this webcam
         * \param message that can contain an error message
         *
         * \author Frankoi
         */
        bool checkAvailability(std::string& message);

        /**
         * \brief Inits webcam for mmap method
         *
         * \author Frankoi
         */
        void initMMAP(void);

        /**
         * \brief Init webcam for read method
         *
         * \author Frankoi
         */
        void initREAD(void);

        /**
         * \brief Checks if the control is supported by the webcam and set the control query result in queryctrl argument
         *
         * \param control the id of the control
         * \
         * \return if control is supported
         *
         * \author Frankoi
         */
        bool isControlSupportedQuery(const WebcamControl& control, struct v4l2_queryctrl* queryctrl);


    public:

        /**
         * \brief Enables the webcam
         *
         * It doesn't start the capture
         *
         * \param params parameters for the webcam (devicename, size, grabbing method, format, framerate, force)
         *
         * \author Frankoi
         */
        void openDevice(const V4L2WebcamParams& params);

		void openDevice(void){openDevice(V4L2WebcamParams());}

        /**
         * \brief Disables the webcam
         *
         * It stops the capture
         *
         * \author Frankoi
         */
        void closeDevice(void);

        /**
         * \brief Starts the capture of the images
         *
         * It starts the capture if necessary
         *
         * \author Frankoi
         */
        void start(void);

        /**
         * \brief Stops the capture of the images
         */
        void stop(void);

        /**
         * \brief Returns if capture has been started
         *
         * \author Frankoi
         */
        bool isStarted(void) const {return isgrabbing;}

        /**
         * \brief returns if device has been opened
         *
         * \author Frankoi
         */
        bool isOpened(void) const {return isenable;}

        /**
         * \brief Get the last image captured
         *
         * Since it returns a pointer, this means that the webcam manager can change the data without warnings.
         * So if you want to use these data during a long time, tou will have to make a copy.
         *
         * ! Don't try to delete the returned pointer
         *
         * \return array of RGB24 data
         *
         * \author Frankoi
         */
        unsigned char* getImage(void);

        /**
         * \brief Returns the width of the images captured by the webcam
         *
         * \return width
         *
         * \author Frankoi
         */
        size_t width(void) const;

        /**
         * \brief Returns the height of the images captured by the webcam
         *
         * \return height
         *
         * \author Frankoi
         */
        size_t height(void) const;

        /**
         * \brief Checks if the control is supported by the webcam
         *
         * \param control the id of the control
         * \return if control is supported
         *
         * \author Frankoi
         */
        bool isControlSupported(const WebcamControl& control);

        /**
         * \brief Returns the current value related to the control
         *
         * \param control the id of the control
         * \return the value of the control
         *
         * \author Frankoi
         */
        int getControlValue(const WebcamControl& control);

        /**
         * \brief Sets control's value to default value
         *
         * \param control the id of the control
         * \return true if operation was a success, false otherwise
         *
         * \author Frankoi
         */
        bool resetControlValue(const WebcamControl& control);

        /**
         * \brief Returns the minimal value allowed for the control
         *
         * \param control the id of the control
         * \return the min value of the control
         *
         * \author Frankoi
         */
        int getControlMinValue(const WebcamControl& control);

        /**
         * \brief Returns the maximal value allowed for the control
         *
         * \param control the id of the control
         * \return the max value of the control
         *
         * \author Frankoi
         */
        int getControlMaxValue(const WebcamControl& control);

        /**
         * \brief Returns the step between two values of the control
         *
         * \param control the id of the control
         * \return the values step of the control
         *
         * \author Frankoi
         */
        int getControlStepValue(const WebcamControl& control);

        /**
         * \brief Increases the value of the control of one step
         *
         * \param control the id of the control
         * \return true if operation was a success, false otherwise
         *
         * \author Frankoi
         */
        bool setControlUpValue(const WebcamControl& control);

        /**
         * \brief Decreases the value of the control of one step
         *
         * \param control the id of the control
         * \return true if operation was a success, false otherwise
         *
         * \author Frankoi
         */
        bool setControlDownValue(const WebcamControl& control);

        /**
         * \brief Sets control's value to the one's in argument
         *
         * \param control the id of the control
         * \param value the value used to set the control
         * \return true if operation was a success, false otherwise
         *
         * \author Frankoi
         */
        bool setControlValue(const WebcamControl& control, const int& value);

        /**
         * \brief Switches to ON/OFF the control based on the value given in argument
         *
         * \param control the id of the control
         * \param value the value used to set the control
         * \return true if operation was a success, false otherwise
         *
         * \author Frankoi
         */
        bool toggleControlValue(const WebcamControl& control, const WebcamToggleControl& value);
    };

    /*
     * End of Namespace
     */
}

#endif
