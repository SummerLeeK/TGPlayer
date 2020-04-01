//
// Created by Apple on 2020-03-22.
//

#ifndef PLAYERDEMO_BASEAUDIOPLAYER_H
#define PLAYERDEMO_BASEAUDIOPLAYER_H

extern "C" {
#include <libavcodec/avcodec.h>
};

typedef struct {
    uint8_t * data;
    int size;
}PCMData;
class BaseAudioPlayer {
public:
    virtual int initPlayer(const AVCodecParameters *parameters) {
        return 0;
    };

    virtual int start() { return 0; };

    virtual int pause() { return 0; };

    virtual int stop() { return 0; };

    virtual int enqueueData(void *buf, int size) { return 0; };

    virtual int setVolume(float left, float right) { return 0; };
};


#endif //PLAYERDEMO_BASEAUDIOPLAYER_H
