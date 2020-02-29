//
// Created by Apple on 2019-11-04.
//

#ifndef FFMPEGANDROID_AUDIOPLAYER_H
#define FFMPEGANDROID_AUDIOPLAYER_H

#define VIDEO_PICTURE_QUEUE_SIZE 3
#define SUBPICTURE_QUEUE_SIZE 16
#define SAMPLE_QUEUE_SIZE 9
#define FRAME_QUEUE_SIZE FFMAX(SAMPLE_QUEUE_SIZE, FFMAX(VIDEO_PICTURE_QUEUE_SIZE, SUBPICTURE_QUEUE_SIZE))


#ifndef TEST_H
#define TEST_H



//you code

#include <pthread.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <native_log.h>
#include <queue>

extern "C" {
#include "libavutil/frame.h"
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
};

#endif
#define AUDIO_PLAYER_LOG "AUDIO_PLAYER_LOG"

using namespace std;
/* Common struct for handling all types of decoded data and allocated render buffers. */
typedef struct Frame {
    uint8_t *frame_data;
} Frame;

typedef struct FrameQueue {
    queue<Frame*> queue;
    int read_index;
    int write_index;
    int size;
    int max_size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} FrameQueue;


class audio_player {
public:
    AVFormatContext *formatContext = NULL;
    AVStream *audioStream = NULL;
    int audioStreamIndex;
    AVCodecContext *codecContext = NULL;
    AVCodecParserContext *parserContext = NULL;
    AVCodec *codec = NULL;
    FrameQueue *frameQueue;

    FILE* file;
    //音频重采样
    struct SwrContext *swrCtx = NULL;


    uint64_t out_channel_layout;
    int out_nb_samples;
    AVSampleFormat out_sample_fmt;
    int out_sample_rate;
    int out_channels;

    SLObjectItf slEngineObj_;
    SLEngineItf slEngineItf_;
    SLObjectItf outputMixObject;
    SLObjectItf playerItf;
    SLPlayItf pcmPlayerPlay;
    SLVolumeItf volumeItf;
//缓冲器队列接口
    SLAndroidSimpleBufferQueueItf pcmBufferQueue;


    int initOpenSLES();

    int openDecoder(const char *path);

    int initQueue();

    int pushQueue(Frame* frame);

    void start(const char *path);

    Frame* popQueue();

    ~audio_player();

};

 void *audio_thread(void *args);

#endif //FFMPEGANDROID_AUDIOPLAYER_H
