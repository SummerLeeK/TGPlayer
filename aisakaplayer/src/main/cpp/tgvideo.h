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
    PlayerQueue *playerQueue;

};


#endif //PLAYERDEMO_TGVIDEO_H
