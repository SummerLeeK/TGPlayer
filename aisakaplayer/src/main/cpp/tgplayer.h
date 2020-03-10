//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGPLAYER_H
#define PLAYERDEMO_TGPLAYER_H

extern "C" {
#include <libavformat/avformat.h>
};

#include "TGVideo.h"
#include "TGAudio.h"
#include "JavaCallHandle.h"


class TGPlayer {
public:
    AVFormatContext *formatContext;
    char *path;
    int *playStatus;
    pthread_t *prepareThread;
    TGVideo *tgvideo;
    TGAudio *tgaudio;
    JavaCallHandle *javaCallHandle;
    int clock;
    bool isPlaying = false;

    TGPlayer();

    int setDataSource(const char *path);

    int prepare();

    int prepareSync();

    int start();


    int stop();


};


#endif //PLAYERDEMO_TGPLAYER_H
