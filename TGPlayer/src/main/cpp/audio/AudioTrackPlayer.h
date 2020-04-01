//
// Created by Apple on 2020-03-22.
//

#ifndef PLAYERDEMO_AUDIOTRACKPLAYER_H
#define PLAYERDEMO_AUDIOTRACKPLAYER_H


#include "BaseAudioPlayer.h"

class AudioTrackPlayer : public BaseAudioPlayer {
public:
    AudioTrackPlayer();

    int initPlayer(const AVCodecParameters *parameters);

    int start();

    int pause();

    int stop();

    int enqueueData(void *buf, int size);

    int setVolume(float left, float right);
};


#endif //PLAYERDEMO_AUDIOTRACKPLAYER_H
