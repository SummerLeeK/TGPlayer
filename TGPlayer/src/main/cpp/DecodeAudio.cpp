//
// Created by Apple on 2020-02-27.
//

#include <audio/AudioTrackPlayer.h>
#include "DecodeAudio.h"


DecodeAudio::DecodeAudio(bool useOpenSLES, AVCodecParameters *params,
                         AVCodecContext *codecContext) {
    playerQueue = new PlayerQueue;

    if (useOpenSLES) {
        audioPlayer = new OpenSLESPlayer;
    } else {
        audioPlayer = new AudioTrackPlayer;
    }

    this->codecContext = codecContext;
    swrContext = swr_alloc();


}

DecodeAudio::~DecodeAudio() {
    delete playerQueue;
}


void *decode(void *data) {
    DecodeAudio *audio = reinterpret_cast<DecodeAudio *>(data);


    audio->audioPlayer->initPlayer(audio->params);
    audio->audioPlayer->start();
    pthread_exit(&audio->decodeThread);

    AVPacket *packet = NULL;
    for (;;) {
        packet = av_packet_alloc();
        if (audio->playerQueue->popPkt(packet) != 0)
            continue;

        int ret = avcodec_send_packet(audio->codecContext, packet);

        if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
            av_packet_free(&packet);
            av_free(&packet);
            packet = NULL;
            continue;
        }
        AVFrame *frame = av_frame_alloc();
        if( avcodec_receive_frame(audio->codecContext, frame)==0){

            int dst_chanel_layout=1;

            swr_alloc_set_opts(audio->swrContext,AV_CH_LAYOUT_STEREO,AV_SAMPLE_FMT_S16,frame->sample_rate,frame->channel_layout,(AVSampleFormat)frame->format,frame->sample_rate,0,NULL);

            swr_convert(audio->swrContext,);

            audio->audioPlayer->enqueueData();
        }

    }
}

void DecodeAudio::start() {
    audioPlayer->start();
    pthread_create(&decodeThread, NULL, decode, this);
}


