//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_DECODEVIDEO_H
#define PLAYERDEMO_DECODEVIDEO_H


#include "PlayerQueue.h"
#include <native_log.h>


extern "C" {
#include <libswscale/swscale.h>
#include "include/libavcodec/avcodec.h"
#include <libyuv/libyuv.h>
};


class DecodeVideo {
public:
    AVCodecContext *codecContext;
    int clock;
    long duration;
    PlayerQueue *playerQueue;
    pthread_t audioDecodeThread;
    pthread_t videoDecodeThread;
    int videoWidth;
    int videoHeight;
    const AVCodecParameters *params;
    AVDictionary *opts = NULL;
    SwsContext* swsContext;
    DecodeVideo(AVCodecContext *codecContext,const AVCodecParameters *params);

    int open_codec();

    int decode(AVFrame* dst);
    int renderYUV(AVFrame *dst,AVFrame *frame);
    ~DecodeVideo();

};


#endif //PLAYERDEMO_DECODEVIDEO_H
