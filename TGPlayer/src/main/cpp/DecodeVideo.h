//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_DECODEVIDEO_H
#define PLAYERDEMO_DECODEVIDEO_H


#include "PlayerQueue.h"

extern "C" {
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
    AVCodecParameters *params;

    DecodeVideo(const AVCodecParameters *params);

    void start();




    ~TGVideo();

};


#endif //PLAYERDEMO_DECODEVIDEO_H
