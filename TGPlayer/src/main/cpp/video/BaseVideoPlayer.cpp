//
// Created by test on 2021/12/8.
//
#include "BaseVideoPlayer.h"

BaseVideoPlayer::BaseVideoPlayer(const AVCodecParameters *codecParameters, AVCodecContext *avCodecContext): mCodecParameters(codecParameters), mAvCodecContext(avCodecContext){}
