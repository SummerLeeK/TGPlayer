//
// Created by Apple on 2020-02-27.
//

#include "DecodeVideo.h"

DecodeVideo::DecodeVideo(const AVCodecParameters *parameters) {
    playerQueue=new PlayerQueue;
}

DecodeVideo::~TGVideo() {
    delete playerQueue;
}


