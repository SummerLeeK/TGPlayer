//
// Created by Apple on 2020-02-27.
//

#include "DecodeVideo.h"

DecodeVideo::DecodeVideo(AVCodecContext *avCodecContext, const AVCodecParameters *parameters) {
    playerQueue = new PlayerQueue;
    codecContext = avCodecContext;
    this->params = parameters;



}

int DecodeVideo::open_codec() {

    AVCodec *codec = avcodec_find_decoder(params->codec_id);
    int result = 0;
    if (codec == NULL) {
        LOGE("video avcodec_find_decoder failed %s", "");
        return -1;
    }

    result = avcodec_parameters_to_context(codecContext, params);

    if (result < 0) {
        LOGE("video avcodec_parameters_to_context failed %s", "");
        return result;
    }

    result = avcodec_open2(codecContext, codec, NULL);


    if (result < 0) {
        LOGE("video avcodec_open2 failed %s", "");
        return result;
    }

    return 0;
}

int DecodeVideo::decode(AVFrame *dst) {
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    if (playerQueue->getPkt(packet) != 0) {
        LOGE("deocde video getPkt Failed size = %d", playerQueue->getPacketQueueSize());
        return -1;
    }

    int result = avcodec_send_packet(codecContext, packet);

    if (result != 0) {
        LOGE("deocde video avcodec_send_packet Failed result = %d", result);
        return result;
    }

    result= avcodec_receive_frame(codecContext,frame);

    if (result != 0) {
        LOGE("deocde video avcodec_receive_frame Failed result = %d", result);
        return result;
    }

    swsContext=sws_getContext(frame->width, frame->height,(AVPixelFormat)frame->format,frame->width, frame->height, AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL, NULL, NULL);
    sws_scale(swsContext, (const unsigned char* const*) frame->data, frame->linesize, 0,frame->height, dst->data, dst->linesize);

    return 0;

}

DecodeVideo::~DecodeVideo() {
    delete playerQueue;
}


