//
// Created by Apple on 2020-03-22.
//


#ifndef PLAYERDEMO_OPENSLESPLAYER_H
#define PLAYERDEMO_OPENSLESPLAYER_H

#include "BaseAudioPlayer.h"

extern "C" {
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES.h>
};


class OpenSLESPlayer : public BaseAudioPlayer {
public:
    SLEngineItf slEngineItf;
    SLObjectItf engineItf;
    SLObjectItf outputMixItf;
    SLObjectItf playerObjectItf;
    SLAndroidDataFormat_PCM_EX formatPcmEx;
    SLPlayItf playItf;
    SLAndroidSimpleBufferQueueItf playBufferQueueItf;

    OpenSLESPlayer();

    int initPlayer(const AVCodecParameters *parameters);


    int start();

    int pause();

    int stop();

    int enqueueData(void *buf, int size);

    int setVolume(float left, float right);

    ~OpenSLESPlayer();

};


#endif //PLAYERDEMO_OPENSLESPLAYER_H
