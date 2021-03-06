//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGPLAYER_H
#define PLAYERDEMO_TGPLAYER_H

extern "C" {
#include <libavformat/avformat.h>
};

#include <video/BaseVideoPlayer.h>
#include <audio/BaseAudioPlayer.h>

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
    pthread_t playThread;
    pthread_t prepareThread;

    jobject surfaceObj;

    pthread_mutex_t playerMutex;
    PlayerListenerCall *listenerCall;
    JavaCallHandle *javaCallHandle;
    BaseAudioPlayer *audioPlayer;
    BaseVideoPlayer *videoPlayer;

    int clock;

    int videoStreamIndex;

    int audioStreamIndex;


    TGPlayer();

    int setDataSource(const char *path);

    int prepare();

    int prepareSync();

    int setVideoSurface(JNIEnv* env,jobject surfaceObj);

    int start();

    int stop();




};


#endif //PLAYERDEMO_TGPLAYER_H
