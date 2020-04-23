//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_DECODEAUDIO_H
#define PLAYERDEMO_DECODEAUDIO_H


#include <libswresample/swresample.h>
#include "PlayerQueue.h"
#include "audio/OpenSLESPlayer.h"

class DecodeAudio {
public:
    long duration;
    int channel;
    int bitRatePerFrame;
    int channelLayout;
    int sample_rate;
    int sample_fmt;
    int clock;
    int type;
    SwrContext *swrContext;
    AVCodecContext *codecContext;
    BaseAudioPlayer *audioPlayer;
    PlayerQueue *playerQueue;

    pthread_t decodeThread;
    AVCodecParameters *params;

    DecodeAudio(bool useOpenSLES,AVCodecParameters *params,AVCodecContext *codecContext);

    void start();

    ~DecodeAudio();
};


#endif //PLAYERDEMO_DECODEAUDIO_H
