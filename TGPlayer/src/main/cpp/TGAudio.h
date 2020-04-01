//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGAUDIO_H
#define PLAYERDEMO_TGAUDIO_H


#include "PlayerQueue.h"
#include "audio/OpenSLESPlayer.h"

class TGAudio {
public:
    long duration;
    int channel;
    int bitRatePerFrame;
    int channelLayout;
    int sample_rate;
    int sample_fmt;
    int clock;
    int type;

    BaseAudioPlayer *audioPlayer;
    PlayerQueue *playerQueue;

    pthread_t decodeThread;
    TGAudio(bool useOpenSLES);

    void start();

    void findParams(const AVCodecParameters *params);

    ~TGAudio();
};


#endif //PLAYERDEMO_TGAUDIO_H
