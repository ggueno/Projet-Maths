/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * LIN_V4L2Webcam.cpp created in 10 2008.
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

#include "LIN_V4L2Webcam.hpp"

#include <utils.hpp>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/kernel.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * Namespace
 */
namespace kn{


	void V4L2Webcam::initMMAP(void)
	{

		int nbbuffers = 4; // We use 6 buffers to save images

		// Allocate buffers
		memset(&rb, 0, sizeof(struct v4l2_requestbuffers));
		rb.count = nbbuffers;
		rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		rb.memory = V4L2_MEMORY_MMAP;
		if(ioctl(filedescriptor, VIDIOC_REQBUFS, &rb)<0){
			throw ControllerException("Unable allocate buffers","V4L2Webcam");
		}
		nbbuffers = rb.count;
		buffersmmap = new void*[nbbuffers];

		// Buffers mapping
		for (int i = 0; i < nbbuffers; i++) {
			memset(&buf, 0, sizeof(struct v4l2_buffer));
			buf.index = i;
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			if(ioctl(filedescriptor, VIDIOC_QUERYBUF, &buf) < 0)
				throw ControllerException("Unable to query buffer","V4L2Webcam");
			buffersmmap[i] = mmap(0 /* start anywhere */ ,buf.length, PROT_READ, MAP_SHARED, filedescriptor,buf.m.offset);
			if (buffersmmap[i] == MAP_FAILED)
				throw ControllerException("Unable to map buffer","V4L2Webcam");
		}

		// Queue buffer
		for (int i = 0; i < nbbuffers; ++i) {
			memset(&buf, 0, sizeof(struct v4l2_buffer));
			buf.index = i;
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			if(ioctl(filedescriptor, VIDIOC_QBUF, &buf) < 0)
				throw ControllerException("Unable to queue buffer","V4L2Webcam");
		}

	}

	void V4L2Webcam::initREAD(void)
	{

		buffersread = new V4L2_Buffer[1];

		buffersread[0].length = fmt.fmt.pix.sizeimage;
		buffersread[0].start = new void* [fmt.fmt.pix.sizeimage];

	}



	void V4L2Webcam::openDevice(const V4L2WebcamParams& params)
	{
		if(this->isenable)
			this->closeDevice();

		this->gb = params.grab;
		this->camwidth = params.width;
		this->camheight = params.height;

		buffersmmap = 0;
		buffersread = 0;
		tmpbuffer = 0;
		framebuffer = 0;
		outputbuffer = 0;

		isgrabbing = false;

		this->devicename = params.devicename;

		if(this->devicename == ""){
			throw ControllerException("Device name is empty","V4L2Webcam");
		}

		if ((filedescriptor = open((this->devicename).c_str(), O_RDWR)) == -1) {
			throw ControllerException("Cannot open device " + this->devicename,"V4L2Webcam");
		}

		std::string msg;
		if(!checkAvailability(msg)){
			throw ControllerException(msg,"V4L2Webcam");
		}

		// Request specif image format
		memset(&fmt, 0, sizeof(struct v4l2_format));
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt.fmt.pix.width = this->camwidth;
		fmt.fmt.pix.height = this->camheight;
		if(params.fmt == FMT_MJPEG)
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
		else
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
		fmt.fmt.pix.field = V4L2_FIELD_ANY;
		if (ioctl(filedescriptor, VIDIOC_S_FMT, &fmt) < 0) {
			throw ControllerException("Unable to set format","V4L2Webcam");
		}

		// check size of image capture
		if ((fmt.fmt.pix.width != params.width) ||
			(fmt.fmt.pix.height != params.height)) {
			std::cerr << "Sorry, expected size (" << params.width << "," << params.height << ") is not available. Thus, size is " << fmt.fmt.pix.width << " " << fmt.fmt.pix.height << std::endl;
			this->camwidth = fmt.fmt.pix.width;
			this->camheight = fmt.fmt.pix.height;
		}

		// Request specific framerate
		struct v4l2_streamparm setfps;
		memset(&setfps, 0, sizeof(struct v4l2_streamparm));
		setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		setfps.parm.capture.timeperframe.numerator=1;
		setfps.parm.capture.timeperframe.denominator=params.framerate;
		if(ioctl(filedescriptor, VIDIOC_S_PARM, &setfps) < 0){
			throw ControllerException("Unable to set fps","V4L2Webcam");
		}

		if(params.grab == MMAP_METHOD)
			initMMAP();
		else
			initREAD();

		size_t framesizein = (this->camwidth * this->camheight << 1);
		switch (params.fmt) {

		case FMT_MJPEG:
			if(fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG){
				tmpbuffer = new unsigned char [framesizein];
				framebuffer = new unsigned char [this->camwidth * (this->camheight+8) * 2];
				outputbuffer = new unsigned char [this->camwidth * (this->camheight) * 3];
			}else{
				if(params.force){
					std::cerr << "V4L2Webcam warning : Unsupported pixel format but FORCE BRUTE" << std::endl;
					tmpbuffer = new unsigned char [framesizein];
					framebuffer = new unsigned char [this->camwidth * (this->camheight+8) * 2];
					outputbuffer = new unsigned char [this->camwidth * (this->camheight) * 3];
					fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
				}else{
					throw ControllerException("Unsupported pixel format","V4L2Webcam");
				}

			}
			break;
		case FMT_YUYV:
			if(fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV){
				framebuffer = new unsigned char [framesizein];
				outputbuffer = new unsigned char [this->camwidth * (this->camheight) * 3];
			}else{
				if(params.force){
					std::cerr << "V4L2Webcam warning : Unsupported pixel format but FORCE BRUTE" << std::endl;
					framebuffer = new unsigned char [framesizein];
					outputbuffer = new unsigned char [this->camwidth * (this->camheight) * 3];
					fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
				}else{
					throw ControllerException("Unsupported pixel format","V4L2Webcam");
				}
			}
			break;

		default:
			throw ControllerException("Unsupported pixel format","V4L2Webcam");
		}
        isenable = true;
	}


	bool V4L2Webcam::checkAvailability(std::string& message)
	{
		// no capability
		memset(&cap, 0, sizeof(struct v4l2_capability));

		// First get capabilities
		int ret = ioctl(filedescriptor, VIDIOC_QUERYCAP, &cap);
		if (ret < 0) {
			message = std::string("Unable to get webcam capabilities");
			return false;
		}

		if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0) {
			message =  std::string("Video capture not supported");
			return false;
		}

		if(gb==MMAP_METHOD)
			if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
				message =  std::string("Video streaming method not supported");
				return false;
			}

		if(gb==READ_METHOD)
			if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
				message =  std::string("Video read method not supported");
				return false;
			}

		return true;

	}

	void V4L2Webcam::closeDevice(void)
	{
		if(isgrabbing) stop();
		isgrabbing = false;

		if(framebuffer) delete[] framebuffer;
		framebuffer = 0;

		if(tmpbuffer) delete[] tmpbuffer;
		tmpbuffer = 0;

		if(buffersmmap){
			for(unsigned int i = 0; i < rb.count; ++i)
				munmap(buffersmmap[i], buf.length);
			delete[] buffersmmap;
		}
		buffersmmap = 0;

		if(outputbuffer) delete[] outputbuffer;
		outputbuffer = 0;

		if(buffersread) delete[] buffersread;
		buffersread = 0;

		isenable = false;

		if(filedescriptor>0) close(filedescriptor);
		filedescriptor = -1;

	}


	void V4L2Webcam::start(void)
	{
		int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if(ioctl(filedescriptor, VIDIOC_STREAMON, &type) < 0)
			throw ControllerException("Unable to start streaming","start");
		isgrabbing = true;

	}

	void V4L2Webcam::stop(void)
	{
		int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if(ioctl(filedescriptor, VIDIOC_STREAMOFF, &type) < 0)
			throw ControllerException("Unable to stop streaming","start");
		isgrabbing = false;
	}


	unsigned char * V4L2Webcam::getImage(void)
	{

#define HEADERFRAME1 0xaf

		if (!isgrabbing)
			start();

		memset(&buf, 0, sizeof(struct v4l2_buffer));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		if(ioctl(filedescriptor, VIDIOC_DQBUF, &buf) < 0)
			throw ControllerException("Unable to dequeue buffer","getImage");


		if(gb==MMAP_METHOD){
			if(buf.bytesused <= HEADERFRAME1) {	/* Prevent crash on empty image */
				/*		if(debug)*/
				std::cerr<<"Ignoring empty buffer ..."<<std::endl;
				return 0;
			}

			if(fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG){
				memcpy(tmpbuffer, buffersmmap[buf.index],buf.bytesused);
				int w = camwidth;
				int h = camheight;
				if (jpeg_decode(&framebuffer, tmpbuffer, &w, &h) < 0)
					return 0;
			}
			else{
				memcpy(framebuffer, buffersmmap[buf.index], (this->camwidth * this->camheight << 1));
			}
		}else{
			read (filedescriptor, buffersread[0].start, buffersread[0].length);
		}

		if(ioctl(filedescriptor, VIDIOC_QBUF, &buf) < 0)
			throw ControllerException("Unable to queue buffer","getImage");


		if(gb==MMAP_METHOD){
			yuyv_to_rgb24(this->camwidth,this->camheight,framebuffer,outputbuffer);
			return outputbuffer;
		}else
			return (unsigned char *)buffersread[0].start;

	}

	size_t V4L2Webcam::width(void) const
	{
		return this->camwidth;
	}

	size_t V4L2Webcam::height(void) const
	{
		return this->camheight;
	}

	bool V4L2Webcam::isControlSupported(const WebcamControl& control)
	{
		queryctrl.id = control;
		if (ioctl(this->filedescriptor, VIDIOC_QUERYCTRL, &queryctrl) < 0) {
			std::cerr << "ioctl get control error" << std::endl;
			return false;
		}
		if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED) {
			std::cerr << "Control " << (char*)queryctrl.name << " is disable" << std::endl;
			return false;
		}
		if (queryctrl.flags & V4L2_CTRL_TYPE_BOOLEAN)
			return true;

		if (queryctrl.type & V4L2_CTRL_TYPE_INTEGER)
			return true;

		std::cerr << "Control " << (char*)queryctrl.name << " is not supported" << std::endl;
		return false;
	}

	bool V4L2Webcam::isControlSupportedQuery(const WebcamControl& control, struct v4l2_queryctrl* queryctrl)
	{
		queryctrl->id = control;
		if (ioctl(this->filedescriptor, VIDIOC_QUERYCTRL, queryctrl) < 0) {
			std::cerr << "ioctl get control error" << std::endl;
			return false;
		}
		if (queryctrl->flags & V4L2_CTRL_FLAG_DISABLED) {
			std::cerr << "Control " << (char*)queryctrl->name << " is disable" << std::endl;
			return false;
		}
		if (queryctrl->flags & V4L2_CTRL_TYPE_BOOLEAN)
			return true;

		if (queryctrl->type & V4L2_CTRL_TYPE_INTEGER)
			return true;

		std::cerr << "Control " << (char*)queryctrl->name << " is not supported" << std::endl;
		return false;
	}

	int V4L2Webcam::getControlValue(const WebcamControl& control)
	{
		if (!isControlSupported(control))
			return -1;
		control_s.id = control;
		if (ioctl(this->filedescriptor, VIDIOC_G_CTRL, &control_s) < 0) {
			std::cerr << "ioctl get control error" << std::endl;
			return -1;
		}
		return control_s.value;
	}

	bool V4L2Webcam::resetControlValue(const WebcamControl& control)
	{
		int val_def;
		if (isControlSupportedQuery(control,&queryctrl)){
			val_def = queryctrl.default_value;
			control_s.id = control;
			control_s.value = val_def;
			if (ioctl(this->filedescriptor, VIDIOC_S_CTRL, &control_s) < 0) {
				std::cerr << "resetControlValue : ioctl set control error" << std::endl;
				return false;;
			}
			return true;
		}

		return false;
	}



	int V4L2Webcam::getControlMinValue(const WebcamControl& control)
	{
		if (isControlSupportedQuery(control,&queryctrl)){
			return queryctrl.minimum;
		}
		return -1;
	}

	int V4L2Webcam::getControlMaxValue(const WebcamControl& control)
	{
		if (isControlSupportedQuery(control,&queryctrl)){
			return queryctrl.maximum;
		}
		return -1;
	}

	int V4L2Webcam::getControlStepValue(const WebcamControl& control)
	{
		if (isControlSupportedQuery(control,&queryctrl)){
			return queryctrl.step;
		}
		return -1;
	}

	bool V4L2Webcam::setControlValue(const WebcamControl& control, const int& value)
	{
		if (isControlSupportedQuery(control,&queryctrl)){
			int min, max, step;
			min = queryctrl.minimum;
			max = queryctrl.maximum;
			step = queryctrl.step;

			if ((value >= min) && (value <= max) && value%step==0) {
				control_s.id = control;
				control_s.value = value;
				if (ioctl(this->filedescriptor, VIDIOC_S_CTRL, &control_s) < 0) {
					std::cerr << "setControlValue : ioctl set control error" << std::endl;
					return false;
				}
				return true;
			}
		}

		return false;
	}

	bool V4L2Webcam::setControlUpValue(const WebcamControl& control)
	{
		if (isControlSupportedQuery(control,&queryctrl)){
			int min, max, step, value;
			min = queryctrl.minimum;
			max = queryctrl.maximum;
			step = queryctrl.step;

			control_s.id = control;
			if (ioctl(this->filedescriptor, VIDIOC_G_CTRL, &control_s) < 0) {
				std::cerr << "ioctl get control error" << std::endl;
				return -1;
			}
			value = control_s.value + step;

			if ((value >= min) && (value <= max)) {
				control_s.id = control;
				control_s.value = value;
				if (ioctl(this->filedescriptor, VIDIOC_S_CTRL, &control_s) < 0) {
					std::cerr << "setControlValue : ioctl set control error" << std::endl;
					return false;
				}
				return true;
			}
		}

		return false;
	}

	bool V4L2Webcam::setControlDownValue(const WebcamControl& control)
	{
		if (isControlSupportedQuery(control,&queryctrl)){
			int min, max, step, value;
			min = queryctrl.minimum;
			max = queryctrl.maximum;
			step = queryctrl.step;

			control_s.id = control;
			if (ioctl(this->filedescriptor, VIDIOC_G_CTRL, &control_s) < 0) {
				std::cerr << "ioctl get control error" << std::endl;
				return -1;
			}
			value = control_s.value - step;

			if ((value >= min) && (value <= max)) {
				control_s.id = control;
				control_s.value = value;
				if (ioctl(this->filedescriptor, VIDIOC_S_CTRL, &control_s) < 0) {
					std::cerr << "setControlValue : ioctl set control error" << std::endl;
					return false;
				}
				return true;
			}
		}

		return false;
	}

	bool V4L2Webcam::toggleControlValue(const WebcamControl& control, const WebcamToggleControl& value)
	{
		if (!isControlSupported(control)){
			return false;
		}
		bzero(&control_s,sizeof(struct v4l2_control));
		control_s.id = control;
		control_s.value = value;
		if (ioctl(this->filedescriptor, VIDIOC_S_CTRL, &control_s) < 0) {
			std::cerr << "setControlValue : ioctl set control error" << std::endl;
			return false;
		}

		return true;
	}

	/*
	 * End of Namespace
	 */

}
