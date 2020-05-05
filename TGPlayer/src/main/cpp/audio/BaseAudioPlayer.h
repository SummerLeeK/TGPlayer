//
// Created by Apple on 2020-03-22.
//

#ifndef PLAYERDEMO_BASEAUDIOPLAYER_H
#define PLAYERDEMO_BASEAUDIOPLAYER_H

#include <DecodeAudio.h>

extern "C" {
#include <libavcodec/avcodec.h>
};

typedef struct {
    uint8_t * data;
    int size;
}PCMData;
class BaseAudioPlayer {
public:
    DecodeAudio* decodeAudio;
    uint8_t *buffer = NULL;
    int dst_channel_layout=AV_CH_LAYOUT_STEREO;
    AVSampleFormat dst_fmt=AV_SAMPLE_FMT_S16;
    int dst_channels;
//    音频采样率
    int dst_sample_rate;
//    音频时钟
    double clock=0;
    virtual int initPlayer(AVCodecContext *codecContext,const AVCodecParameters *parameters) {
        LOGE("initPlayer %s","BaseAudioPlayer");
        return 0;
    };



    virtual int start() {
        LOGE("start %s","BaseAudioPlayer");
        return 0; };

    virtual int pause() { return 0; };

    virtual int stop() { return 0; };

    virtual int enqueueData(void *buf, int size) { return 0; };

    virtual int setVolume(float left, float right) { return 0; };
};


#endif //PLAYERDEMO_BASEAUDIOPLAYER_H
