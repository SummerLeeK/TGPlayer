//
// Created by hklee on 20-4-23.
//

#include "../include/libavcodec/avcodec.h"
#include "../DecodeVideo.h"

#ifndef PLAYERDEMO_BASEVIDEOPLAYER_H
#define PLAYERDEMO_BASEVIDEOPLAYER_H

#endif //PLAYERDEMO_BASEVIDEOPLAYER_H

class BaseVideoPlayer{
public:
    DecodeVideo *decodeVideo;

    BaseVideoPlayer(const AVCodecParameters *codecParameters,AVCodecContext *avCodecContext);

    int open_codec();
};