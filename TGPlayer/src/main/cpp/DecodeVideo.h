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
    SwsContext* swsContext;
    DecodeVideo(AVCodecContext *codecContext,const AVCodecParameters *params);

    int open_codec();

    int decode(AVFrame* dst);

    ~DecodeVideo();

};


#endif //PLAYERDEMO_DECODEVIDEO_H
