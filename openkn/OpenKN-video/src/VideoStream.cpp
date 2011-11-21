/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * VideoStream.cpp created in 08 2009.
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

#define __STDC_CONSTANT_MACROS

#include "VideoStream.hpp"

#include "VideoException.hpp"

#include <cstring>


VideoStream::VideoStream( const std::string& filename ) {

    this->filename = filename;

   av_register_all();

    // Open video file
    this->pFormatCtx = 0;
    if(av_open_input_file(&(this->pFormatCtx), this->filename.c_str(), NULL, 0, NULL)!=0)
        throw kn::VideoException(std::string("Failed to open ")+this->filename,"VideoStream");

    // Get information about the stream
    if(av_find_stream_info(this->pFormatCtx)<0)
        throw kn::VideoException(std::string("Failed to find stream info"),"VideoStream");

    // Search a video stream
    this->videoStream=-1;
    for(unsigned int i=0; i<this->pFormatCtx->nb_streams; i++)
        if(this->pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO) {
            this->videoStream=i;
            break;
        }

    if(this->videoStream==-1)
        throw kn::VideoException(std::string("Unable to find a valid video stream"),"VideoStream");

    // Get a pointer to the codec context for the video stream
    this->pCodecCtx = 0;
    this->pCodecCtx=pFormatCtx->streams[this->videoStream]->codec;

    AVCodec *pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==0)
        throw kn::VideoException(std::string("Unsupported codec"),"VideoStream");


    // Open the corresponding codec
    if(avcodec_open(this->pCodecCtx, pCodec)<0)
        throw kn::VideoException(std::string("Unable to open the codec"),"VideoStream");

    this->pFrame = 0;
    this->pFrame = avcodec_alloc_frame();

    PixelFormat dst_pix_fmt = PIX_FMT_RGB24;
    img_convert_ctx = 0;
    img_convert_ctx = sws_getContext(this->pCodecCtx->width, this->pCodecCtx->height,
                                     this->pCodecCtx->pix_fmt,
                                     this->pCodecCtx->width, this->pCodecCtx->height,
                                     dst_pix_fmt, SWS_POINT, NULL, NULL, NULL);
    //SWS_BILINEAR, SWS_FAST_BILINEAR, SWS_BICUBIC, SWS_POINT

    if(img_convert_ctx==0)
        throw kn::VideoException(std::string("Cannot initialize the conversion context"),"VideoStream");

    // Create the conversion frame
    this->pFrameRGB = 0;
    this->pFrameRGB = avcodec_alloc_frame();
    int numBytes = avpicture_get_size(PIX_FMT_RGB24, this->pCodecCtx->width, this->pCodecCtx->height);
    this->conversionbuffer = 0;
    this->conversionbuffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));
    avpicture_fill((AVPicture *)this->pFrameRGB, this->conversionbuffer, dst_pix_fmt,
                   this->pCodecCtx->width, this->pCodecCtx->height);

    this->framerate = this->pFormatCtx->streams[this->videoStream]->r_frame_rate.num / this->pFormatCtx->streams[this->videoStream]->r_frame_rate.den;

    this->numberofframe = this->pFormatCtx->streams[this->videoStream]->duration;//  pFormatCtx->duration / (this->framerate*1000.0f);

    this->eos = false;

    this->currentframe = 0;

}


VideoStream::~VideoStream( void ){

    if(this->pFrame){
        av_free(this->pFrame);
        this->pFrame = 0;
    }

    if(this->pFrameRGB){
        av_free(this->pFrameRGB);
        this->pFrameRGB = 0;
    }

    if(this->conversionbuffer){
        av_free(this->conversionbuffer);
        this->conversionbuffer = 0;
    }

    if(this->pCodecCtx){
        avcodec_close(this->pCodecCtx);
        this->pCodecCtx = 0;
    }

    if(this->img_convert_ctx){
        sws_freeContext(this->img_convert_ctx);
        this->img_convert_ctx = 0;
    }

    if(this->pFormatCtx){
        av_close_input_file(this->pFormatCtx);
        this->pFormatCtx = 0;
    }

}



unsigned char * VideoStream::getFrame( void ){

    int frameFinished = -1;
    AVPacket packet;
    int eof = av_read_frame(this->pFormatCtx, &packet);
    if(eof==0){
        this->eos = false;
        avcodec_decode_video(this->pCodecCtx, this->pFrame, &frameFinished, packet.data, packet.size);
        if(frameFinished){
            sws_scale(this->img_convert_ctx, this->pFrame->data, this->pFrame->linesize,
                      0, this->pCodecCtx->height, this->pFrameRGB->data, this->pFrameRGB->linesize);
            av_free_packet(&packet);
            this->currentframe++;
            return pFrameRGB->data[0];
        }
    }else{
        this->eos = true;
    }
    av_free_packet(&packet);
    return 0;
}


void VideoStream::goToFrameId (unsigned int n ){
    if(n < this->currentframe){
        av_seek_frame(this->pFormatCtx,-1,n,AVSEEK_FLAG_ANY|AVSEEK_FLAG_BACKWARD);
        this->currentframe = n;
        this->eos = false;
    }else{
        if(this->currentframe < n && n < numberofframe){
            av_seek_frame(this->pFormatCtx,-1,n,AVSEEK_FLAG_ANY);
            this->currentframe = n;
            this->eos = false;
        }
    }

}



AVFrame *alloc_picture(PixelFormat pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;

    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf = new uint8_t[size];
    if (!picture_buf) {
        av_free(picture);
        return 0;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                   pix_fmt, width, height);
    return picture;
}


void VideoStream::encode(const std::string& filename, unsigned char ** frames, const unsigned int& nbframes, const unsigned int& width, const unsigned& height){

    av_register_all();

    // Deduce the format of the video
    AVOutputFormat *fmt = guess_format(NULL, filename.c_str(), NULL);
    if(fmt==0)
        throw kn::VideoException(std::string("Could not deduce output format from file extension"),"VideoStream");

    AVFormatContext *oc = avformat_alloc_context();//av_alloc_format_context();
    if(oc==0)
        throw kn::VideoException(std::string("Cannot allocate format context"),"VideoStream");

    oc->preload= (int)(0.5*AV_TIME_BASE);
    oc->max_delay= (int)(0.7*AV_TIME_BASE);
    oc->oformat = fmt;
    snprintf(oc->filename, sizeof(oc->filename), "%s", filename.c_str());

    AVStream *video_st = 0;

    // If we found a valid codec, we fill the information about the codec context
    if (fmt->video_codec != CODEC_ID_NONE){

        video_st = av_new_stream(oc, 0);
        if (!video_st)
            throw kn::VideoException(std::string("Unable to create a new stream"),"VideoStream");

        AVCodecContext *c = video_st->codec;
        c->codec_id = fmt->video_codec;
        c->codec_type = CODEC_TYPE_VIDEO;
        c->bit_rate = 400000;
        c->me_method = 3;
        c->width = width;
        c->height = height;
        c->time_base.num = 1;
        c->time_base.den = 25;
        c->max_b_frames=1;
        c->pix_fmt = PIX_FMT_YUV420P;
        c->gop_size = 10;
        if (c->codec_id == CODEC_ID_MPEG2VIDEO) {
            c->max_b_frames = 2;
        }
        if (c->codec_id == CODEC_ID_MPEG1VIDEO){
            c->mb_decision=2;
        }
        if(!strcmp(oc->oformat->name, "mp4") || !strcmp(oc->oformat->name, "mov") || !strcmp(oc->oformat->name, "3gp"))
            c->flags |= CODEC_FLAG_GLOBAL_HEADER;
    }

    if (av_set_parameters(oc, NULL) < 0)
        throw kn::VideoException(std::string("Invalid output format parameters"),"VideoStream");

    AVCodecContext *c = video_st->codec;

    AVCodec *codec = avcodec_find_encoder(c->codec_id);
    if (codec==0)
        throw kn::VideoException(std::string("No available codec was found"),"VideoStream");

    if (avcodec_open(c, codec) < 0)
        throw kn::VideoException(std::string("Unable to open the codec"),"VideoStream");

    uint8_t *video_outbuf = NULL;
    int video_outbuf_size;
    if (!(oc->oformat->flags & AVFMT_RAWPICTURE)) {
        video_outbuf_size = c->width*c->height*3;
        video_outbuf = new uint8_t [video_outbuf_size];
    }

    AVFrame *picture = alloc_picture(c->pix_fmt, c->width, c->height);
    if (!picture)
        throw kn::VideoException(std::string("Unable to allocate picture"),"VideoStream");

    AVFrame *tmp_picture = alloc_picture(PIX_FMT_RGB24, c->width, c->height);
    if (!tmp_picture)
        throw kn::VideoException(std::string("Unable to allocate tmppicture"),"VideoStream");


    if (!(fmt->flags & AVFMT_NOFILE))
        if (url_fopen(&oc->pb, filename.c_str(), URL_WRONLY) < 0)
            throw kn::VideoException(std::string("Unable to create the file"),"VideoStream");

    av_write_header(oc);

    struct SwsContext *img_convert_ctx = sws_getContext(c->width, c->height, PIX_FMT_RGB24,
                                                        c->width, c->height, c->pix_fmt,
                                                        SWS_BILINEAR, 0, 0, 0);
    if(img_convert_ctx==0)
        throw kn::VideoException(std::string("Unable to create a scaling context"),"VideoStream");

    for(unsigned int i = 0; i < nbframes; ++i) {
        avpicture_fill((AVPicture *)tmp_picture, frames[i], PIX_FMT_RGB24, c->width, c->height);
        sws_scale(img_convert_ctx, tmp_picture->data, tmp_picture->linesize, 0, c->height, picture->data, picture->linesize);

        int out_size = avcodec_encode_video(c, video_outbuf, video_outbuf_size, picture);
        if (out_size != 0) {
            AVPacket pkt;
            av_init_packet(&pkt);

            pkt.pts= c->coded_frame->pts;
            if(c->coded_frame->key_frame)
                pkt.flags |= PKT_FLAG_KEY;
            pkt.stream_index= video_st->index;
            pkt.data= video_outbuf;
            pkt.size= out_size;
            pkt.dts=AV_NOPTS_VALUE;
            pkt.pos= -1;
            pkt.duration=(int64_t)0;   //TODO
            int ret = av_write_frame(oc, &pkt);
            if(ret<0){
                std::cerr << "Error writing frame " << i << std::endl;
            }
        }
    }

    av_free(picture->data[0]);
    av_free(picture);
    if (tmp_picture) {
        av_free(tmp_picture->data[0]);
        av_free(tmp_picture);
    }
    av_free(video_outbuf);

    avcodec_close(c);

    av_write_trailer(oc);

    for(unsigned int i = 0; i < oc->nb_streams; i++) {
        av_freep(&oc->streams[i]);
    }

    if (!(fmt->flags & AVFMT_NOFILE)) {
        url_fclose(oc->pb);
    }

    av_free(oc);

}


