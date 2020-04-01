//
// Created by Apple on 2020-02-27.
//

#include "TGVideo.h"

TGVideo::TGVideo() {
    playerQueue=new PlayerQueue;
}

TGVideo::~TGVideo() {
    delete playerQueue;
}

void TGVideo::findParams(const AVCodecParameters *parameters) {

    videoWidth=parameters->width;
    videoHeight=parameters->height;


}


