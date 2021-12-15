//
// Created by Apple on 2020-02-27.
//

#include <ANativeWindowRender.h>
#include "DecodeVideo.h"

DecodeVideo::DecodeVideo(AVCodecContext *avCodecContext, const AVCodecParameters *parameters) {
    playerQueue = new PlayerQueue;
    codecContext = avCodecContext;
    this->params = parameters;
}

int DecodeVideo::open_codec() {
    const AVCodec *codec = NULL;
    codec = avcodec_find_decoder(params->codec_id);
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
    codecContext->codec_id = codec->id;

    result = avcodec_open2(codecContext, codec, &opts);


    if (result < 0) {
        LOGE("video avcodec_open2 failed %s", "");
        return result;
    }
    LOGD("video open_codec success");
    return 0;
}

int DecodeVideo::decode(AVFrame *dst) {
    AVPacket *packet = av_packet_alloc();
    if (playerQueue->getPkt(packet) != 0) {
        LOGE("deocde video getPkt Failed size = %d", playerQueue->getPacketQueueSize());
        return -1;
    }

    int result = avcodec_send_packet(codecContext, packet);

    if (result < 0 || result == AVERROR(EAGAIN) || result == AVERROR_EOF) {
        LOGE("deocde video avcodec_send_packet Failed result = %d  %s", result, av_err2str(result));
        return result;
    }


    AVFrame *frame = av_frame_alloc();

    result = avcodec_receive_frame(codecContext, frame);

    if (result < 0 && result != AVERROR_EOF) {
        LOGE("deocde video avcodec_receive_frame Failed result = %d", result);
        av_frame_free(&frame);
        av_free(frame);
        frame = NULL;
        av_packet_free(&packet);
        av_free(packet);
        packet = NULL;

        return result;
    }
    av_frame_ref(dst, frame);
    av_packet_free(&packet);
    av_free(packet);
    packet = NULL;


    return 0;

}

int DecodeVideo::renderYUV(AVFrame *dst, AVFrame *frame) {


}

DecodeVideo::~DecodeVideo() {
    delete playerQueue;
}


