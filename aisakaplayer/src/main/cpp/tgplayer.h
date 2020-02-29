//
// Created by Apple on 2020-02-27.
//

#ifndef PLAYERDEMO_TGPLAYER_H
#define PLAYERDEMO_TGPLAYER_H


#include <libavformat/avformat.h>
#include "tgvideo.h"
#include "tgaudio.h"

class tgplayer {
public:
    AVFormatContext *formatContext;
    char *path;
    tgvideo tgvideo;
    tgaudio tgaudio;
    int clock;
    bool isPlaying = false;

    void start();


    void stop();


};


#endif //PLAYERDEMO_TGPLAYER_H
