/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * VideoStream.hpp created in 08 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-video.
 *
 * The OpenKraken-video is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-video is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_VIDEO__VIDEO_STREAM_HPP__
#define __OPENKN_VIDEO__VIDEO_STREAM_HPP__

#include <iostream>
#include <string>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

/**
 * \brief Class to manage or create a video stream
 * \author Frankoi
 */

class VideoStream {

private:

	/**
	 * \brief Contain information about the format of the stream
	 * \author Frankoi
	 */
	AVFormatContext *pFormatCtx;

	/**
	 * \brief Contain information about the codecs to use with the format
	 * \author Frankoi
	 */
	AVCodecContext	*pCodecCtx;

	/**
	 * \brief Raw frame that need to be converted
	 * \author Frankoi
	 */
	AVFrame *pFrame;

	/**
	 * \brief RBG frame that will contain the result of a raw frame convertion
	 * \author Frankoi
	 */
	AVFrame *pFrameRGB;

	/**
	 * \brief Id of the videostream
	 * \author Frankoi
	 */
	int videoStream;

	/**
	 * \brief structure that maintains information about how to convert the stream into a specific format
	 * \author Frankoi
	 */
	struct SwsContext *img_convert_ctx;

	/**
	 * \brief Filename of the video stream
	 * \author Frankoi
	 */
	std::string filename;

	/**
	 * \brief Buffers used during the conversion process
	 * \author Frankoi
	 */
	uint8_t *conversionbuffer;

	/**
	 *
	 * \brief Number of frames of the stream
	 * \author Frankoi
	 */
	unsigned int numberofframe;

	/**
	 *
	 * \brief Framerate
	 * \author Frankoi
	 */
	float framerate;

	/**
	 *
	 * \brief End Of Stream
	 * \author Frankoi
	 */
	bool eos;

	/**
	 *
	 * \brief Id of the current frame in the stream
	 * \author Frankoi
	 */
	unsigned int currentframe;


public:

	/**
	 *
	 * \brief Create a video stream
	 * \param filename name of the file containing the video stream
	 * \throw many exceptions
	 * \author Frankoi
	 */
	VideoStream( const std::string& filename );

	/**
	 *
	 * \brief Destructor
	 * \author Frankoi
	 */
	~VideoStream( void );

	/**
	 *
	 * \brief Return a frame from the video stream
	 *
	 * Currently there is no way to move forward or backward in the stream. This function simply return consecutive frames
	 *
	 * \return a frame of the video stream in RGB24
	 * \author Frankoi
	 */
	unsigned char * getFrame( void );

	/**
	 *
	 * \brief Return the width of the stream
	 *
	 * \return the width
	 * \author Frankoi
	 */
	unsigned int getWidth( void ) const { return this->pCodecCtx->width; }

	/**
	 *
	 * \brief Return the height of the stream
	 *
	 * \return the height
	 * \author Frankoi
	 */
	unsigned int getHeight( void ) const { return this->pCodecCtx->height; }

	/**
	 *
	 * \brief Return the number of images per second
	 *
	 * \return the frame rate
	 * \author Frankoi
	 */
	float getFrameRate( void ) const { return framerate; }

	/**
	 *
	 * \brief Return the total number of frame contained in the stream
	 *
	 * \return the number of frames
	 * \author Frankoi
	 */
	unsigned int getNumberOfFrame( void ) const { return numberofframe; }

	/**
	 *
	 * \brief Return the current frame id
	 *
	 * \return the current frame Id
	 * \author Frankoi
	 */
	unsigned int getCurrentFrameId( void ) const { return this->currentframe; }


	/**
	 *
	 * \brief Return if the stream is finished or not
	 *
	 * \return true if the stream is finished, false otherwise
	 * \author Frankoi
	 */
	bool getEndOfStreamStatus( void ) const { return this->eos; }

	/**
	 *
	 * \brief Move the stream to a specific frame
	 *
	 * WARNING : This function works only with AVI stream and only for n = 0
	 *
	 * \param the frame where to go in the stream
	 * \author Frankoi
	 */
	void goToFrameId(unsigned int n);

	/**
	 *
	 * \brief Encode a set of RGB24 image into a video stream
	 *
	 * \param filename the output filename
	 * \param frames the set of images
	 * \param nbframes the number of frame in the set of images
	 * \param width the width of the images
	 * \param height the height of the images
	 * \author Frankoi
	 */
	static void encode(const std::string& filename, unsigned char ** frames, const unsigned int& nbframes, const unsigned int& width, const unsigned& height);

};




#endif
