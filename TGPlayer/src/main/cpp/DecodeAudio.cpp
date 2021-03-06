//
// Created by Apple on 2020-02-27.
//

#include "DecodeAudio.h"


DecodeAudio::DecodeAudio(const AVCodecParameters *params,
                         AVCodecContext *codecContext) {
    playerQueue = new PlayerQueue;

    this->params = params;
    this->codecContext = codecContext;


    buf = (uint8_t *) malloc(params->sample_rate * 2 * 2 * 2/3);

}

DecodeAudio::~DecodeAudio() {


    avcodec_close(codecContext);

    delete playerQueue;
}

/**
 * 返回每个通道的采样个数
 * @param pcm
 * @return
 */
int DecodeAudio::getPcmData(uint8_t **pcm) {
    AVPacket *packet = NULL;
    int nb_sample = 0;
    for (;;) {

        if (isNewPacket) {

            packet = av_packet_alloc();
            if (playerQueue->getPkt(packet) != 0) {
                LOGE("getPkt failed %d", playerQueue->getPacketQueueSize());
                continue;
            }

        }

        LOGE("avcodec_send_packet is NULL %d",packet==NULL);
        int ret = avcodec_send_packet(codecContext, packet);

        if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
//            一帧数据已经读取完毕
            playerQueue->popPkt(packet);
            av_packet_free(&packet);
//            av_free(&packet);
//            packet = NULL;
            isNewPacket = true;
//            LOGE("avcodec_send_packet %d", playerQueue->getPacketQueueSize());
            continue;
        }
        AVFrame *frame = av_frame_alloc();
        if (avcodec_receive_frame(codecContext, frame) == 0) {

            SwrContext *swrContext;
            swrContext = swr_alloc_set_opts(NULL, AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16,
                                            frame->sample_rate, frame->channel_layout,
                                            (AVSampleFormat) frame->format, frame->sample_rate, 0,
                                            NULL);
            if (!swrContext || swr_init(swrContext) < 0) {
                av_frame_free(&frame);
                av_free(frame);
                frame = NULL;
                continue;
            }
            int64_t dst_nb_samples = av_rescale_rnd(
                    swr_get_delay(swrContext, frame->sample_rate) + frame->nb_samples,
                    frame->sample_rate, frame->sample_rate, AV_ROUND_INF);
            nb_sample = swr_convert(swrContext, &buf, dst_nb_samples,
                                    (const uint8_t **) frame->data,
                                    frame->nb_samples);


            LOGE("swr_convert %d", nb_sample);

            av_frame_free(&frame);
            av_free(frame);
            frame = NULL;
            swr_free(&swrContext);
            *pcm = buf;
            break;
        } else
        {
            isNewPacket = true;
            av_frame_free(&frame);
//            av_free(frame);
            frame = NULL;
            av_packet_free(&packet);
//            av_free(packet);
            packet = NULL;


            continue;
        }

    }

    return nb_sample;
}


int DecodeAudio::open_codec() {

    AVCodec *codec = avcodec_find_decoder(params->codec_id);


    if (avcodec_parameters_to_context(codecContext, params) != 0) {
        LOGE("avcodec_parameters_to_context failed %s", "");
        return -1;
    }

    int result = avcodec_open2(codecContext, codec, NULL);

    if (result < 0) {
        LOGE("audio codec open failed %s", av_err2str(result));
    }

    return 0;
}

