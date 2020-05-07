//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_DECODEAUDIO_H
#define PLAYERDEMO_DECODEAUDIO_H



#include "PlayerQueue.h"

#include <pthread.h>
#include <native_log.h>

extern "C" {
#include <libswresample/swresample.h>
}

class DecodeAudio {
public:

    AVCodecContext *codecContext;

    uint8_t *buf;
    PlayerQueue *playerQueue;

    const AVCodecParameters *params;
    bool isNewPacket= true;


    DecodeAudio(const AVCodecParameters *params,AVCodecContext *codecContext);

    int open_codec();

    int getPcmData(uint8_t ** pcm);

    ~DecodeAudio();
};


#endif //PLAYERDEMO_DECODEAUDIO_H
