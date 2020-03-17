//
// Created by Apple on 2020-03-10.
//

#ifndef PLAYERDEMO_PLAYERQUEUE_H
#define PLAYERDEMO_PLAYERQUEUE_H


extern "C" {
#include "include/libavutil/frame.h"
#include "include/libavcodec/avcodec.h"
};

#include <queue>
#include <jni.h>
#include <stdbool.h>
#include <pthread.h>

using namespace std;

class PlayerQueue {
public:
    queue<AVFrame*> frameQueue;
    queue<AVPacket*> packetQueue;
    pthread_mutex_t packetMutex;
    pthread_cond_t packetCond;

    pthread_mutex_t frameMutex;
    pthread_cond_t frameCond;

    PlayerQueue();


    int pushPkt(AVPacket *pkt);

    int popPkt(AVPacket *pkt);


    int pushFrame(AVFrame *frame);

    int popFrame(AVFrame *frame);

    ~PlayerQueue();
};


#endif //PLAYERDEMO_PLAYERQUEUE_H
