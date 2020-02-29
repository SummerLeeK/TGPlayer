//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGVIDEO_H
#define PLAYERDEMO_TGVIDEO_H


#include "tgqueue.h"
#include "include/libavcodec/avcodec.h"

class tgvideo {
public:
    AVCodecContext *codecContext;

    tgqueue videoqueue;



};


#endif //PLAYERDEMO_TGVIDEO_H
