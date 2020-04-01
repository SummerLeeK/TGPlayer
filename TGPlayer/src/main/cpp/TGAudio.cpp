//
// Created by Apple on 2020-02-27.
//

#include <audio/AudioTrackPlayer.h>
#include "TGAudio.h"


TGAudio::TGAudio(bool useOpenSLES) {
    playerQueue = new PlayerQueue;

    if (useOpenSLES) {
        audioPlayer = new OpenSLESPlayer;
    } else {
        audioPlayer = new AudioTrackPlayer;
    }

}

TGAudio::~TGAudio() {
    delete playerQueue;
}

void TGAudio::findParams(const AVCodecParameters *params) {

    audioPlayer->initPlayer(params);
}

void *decode(void *data) {
    TGAudio *audio = reinterpret_cast<TGAudio *>(data);



    pthread_exit(&audio->decodeThread);
}

void TGAudio::start() {
    audioPlayer->start();
    pthread_create(&decodeThread, NULL, decode, this);
}


