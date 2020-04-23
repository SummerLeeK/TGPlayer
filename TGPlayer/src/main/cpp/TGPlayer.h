//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGPLAYER_H
#define PLAYERDEMO_TGPLAYER_H

extern "C" {
#include <libavformat/avformat.h>
};

#include "DecodeVideo.h"
#include "DecodeAudio.h"
#include "JavaCallHandle.h"
#include "PlayerListenerCall.h"


class TGPlayer {
public:
    AVFormatContext *formatContext;
    AVCodecContext *videoCodecContext;
    AVCodecContext *audioCodecContext;
    char *path;
    bool pause;
    bool exit = false;
    pthread_t readFrameThread;
    pthread_t prepareThread;


    DecodeVideo *decodeVideo;
    DecodeAudio *decodeAudio;
    pthread_mutex_t playerMutex;
    PlayerListenerCall *listenerCall;
    JavaCallHandle *javaCallHandle;
    BaseAudioPlayer *audioPlayer;
    int clock;

    int videoStreamIndex;

    int audioStreamIndex;


    TGPlayer();

    int setDataSource(const char *path);

    int prepare();

    int prepareSync();

    int start();

    int stop();




};


#endif //PLAYERDEMO_TGPLAYER_H
