/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_DVCam.cpp created in 03 2009.
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
 * Internal Includes
 */
#include "LIN_DVCam.hpp"

/*
 * External Includes
 */
#include <cstdio>
#include <sys/poll.h>
#include <signal.h>
#include <cstring>
#include <cstdlib>
#include <boost/bind.hpp>
#include <errno.h>

/*
 * Namespace
 */
namespace kn{

	int DVCam::callbackReadFrame( unsigned char *data, 
								  int length, 
								  int complete, 
								  void *callback_data)
	{
		if(complete && length > 0){ // check for a full frame
			DVCam * self = static_cast<DVCam *>( callback_data );
			return self->ReadFrame(data);
		}
        usleep(500);
		return 0;
	}

	int DVCam::ReadFrame(unsigned char *data)
	{
		if( dv_parse_header(td, data) < 0 ){ std::cerr << " DVCam::Handler : Error in header of data" << std::endl; return -1;}
		boost::mutex::scoped_lock lock(dvmutex);
		unsigned int tmpindice = (currentframe+1)%maxframe;
		// decode and save a frame
		dv_decode_full_frame(td, data, e_dv_color_rgb, pixels[tmpindice], pitches);
		currentframe = tmpindice;
        usleep(200);
		return 0;
	}

    void DVCam::ResetHandler( void )
    {
    }
 
    int DVCam::ResetHandlerProxy( raw1394handle_t handle, unsigned int generation )
    {
        iec61883_dv_t dv = static_cast< iec61883_dv_t >( raw1394_get_userdata( handle ) );
        iec61883_dv_fb_t dvfb = static_cast< iec61883_dv_fb_t >( iec61883_dv_get_callback_data( dv ) );
        DVCam *self = static_cast< DVCam* >( iec61883_dv_fb_get_callback_data( dvfb ) );
        raw1394_update_generation( handle, generation );
        if ( self )
            self->ResetHandler();
        return 0;
    }


	void DVCam::openDevice(const DVCamParams& params)
	{

        this->camwidth = 720;
        this->camheight = 576;

		if(isenable)
			closeDevice();
			
		if(params.port < 0)
			throw ControllerException("Channel is not valid","DVCam::openDevice");

		/* Create handle based on a port number*/
		handle = raw1394_new_handle_on_port(params.port);
		if(!handle)
			throw ControllerException("Failed to get handle","DVCam::openDevice");

		// Create a decoder
		td = dv_decoder_new(FALSE,FALSE,FALSE);
		td->quality=DV_QUALITY_BEST;

        raw1394_set_bus_reset_handler( handle, this->ResetHandlerProxy );


		// init callback for raw1394
		frame = iec61883_dv_fb_init(handle,DVCam::callbackReadFrame, this);

		if(!frame)
			throw ControllerException("Failed to init DV","DVCam::openDevice");

		isenable=true;
			
	}

	void DVCam::closeDevice(void)
	{
		stop();
		if(handle) raw1394_destroy_handle(handle);
		handle = 0;
		isenable=false;
		isgrabbing=false;
		td=0;
		isenable = false;
		frame = 0;

	}

	void DVCam::start(void)
	{
		// Start only if frame exist 
		if (frame){
			if(!isgrabbing){ // Don't start again
				isgrabbing = true;
				if(iec61883_dv_fb_start (frame, 63)<0)
					throw ControllerException("start error","DVCam::start");
				thrd = new boost::thread(boost::bind(&DVCam::Handler, this)); // Launch a thread for grabbing images
			}
		}else{
			throw ControllerException("DVCam not opened","DVCam::start");
		}
			
		// Wait a little bit before starting (hack to skip black images)
		usleep(120000);
	}

	void DVCam::stop(void)
	{
		if(isgrabbing){ // stop only if grabbing
			isgrabbing = false;
			thrd->join();
			delete thrd;
			thrd = 0;
			iec61883_dv_fb_close(frame);
			frame = 0;
		}
	}


	unsigned char* DVCam::getImage(void)
	{
		if(!isgrabbing){start();}
		boost::mutex::scoped_lock lock(dvmutex);
		return pixels[currentframe][0];
	}

	void DVCam::Handler(void)
	{
		struct pollfd raw1394_poll;
		raw1394_poll.fd = raw1394_get_fd( handle );
		raw1394_poll.events = POLLIN | POLLERR | POLLHUP | POLLPRI;
			
		int result = 0;
		while ( isgrabbing ){
			while ( ( result = poll( &raw1394_poll, 1, 300 ) ) < 0 )
			{
				if ( !( errno == EAGAIN || errno == EINTR ) )
				{
					perror( "error: raw1394 poll" );
					break;
				}
			}
			if ( result > 0 && ( ( raw1394_poll.revents & POLLIN )
								 || ( raw1394_poll.revents & POLLPRI ) ) ){
				result = raw1394_loop_iterate( handle );
			}
            usleep(10);
		}
			
	}
}
