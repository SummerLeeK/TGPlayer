//
// Created by hklee on 20-4-23.
//



#ifndef PLAYERDEMO_BASEVIDEOPLAYER_H
#define PLAYERDEMO_BASEVIDEOPLAYER_H


#include <DecodeVideo.h>

extern "C" {
#include <libavcodec/avcodec.h>
}

class BaseVideoPlayer {
public:
    AVDictionary **opts ;
    DecodeVideo *decodeVideo;
    const AVCodecParameters *mCodecParameters;
    AVCodecContext *mAvCodecContext;

    BaseVideoPlayer(const AVCodecParameters *codecParameters, AVCodecContext *avCodecContext);

    virtual int initplayer(JNIEnv *env, jobject surface) {
        return 0;
    };


    virtual int start() {
        return 0;
    };


    virtual int pause() {
        return 0;
    };

    virtual int release() {
        return 0;
    };
};

#endif //PLAYERDEMO_BASEVIDEOPLAYER_H