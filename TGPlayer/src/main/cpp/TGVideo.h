//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGVIDEO_H
#define PLAYERDEMO_TGVIDEO_H


#include "PlayerQueue.h"

extern "C" {
#include "include/libavcodec/avcodec.h"
};


class TGVideo {
public:
    AVCodecContext *codecContext;
    int clock;
    long duration;
    PlayerQueue *playerQueue;

    int videoWidth;
    int videoHeight;

    TGVideo();

    void start();

    void findParams(const AVCodecParameters *parameters);


    ~TGVideo();

};


#endif //PLAYERDEMO_TGVIDEO_H
