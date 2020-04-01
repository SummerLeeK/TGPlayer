//
// Created by Apple on 2020-02-27.
//

#include <native_log.h>

extern "C" {
#include <libavutil/time.h>
}

#include "TGPlayer.h"
#include "Exception.h"


TGPlayer::TGPlayer() {

    pthread_mutex_init(&playerMutex, NULL);

}

int findAVCodecContext(void* data) {
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);

    int videoStreamIndex = av_find_best_stream(player->formatContext, AVMEDIA_TYPE_VIDEO, -1, -1,
                                               NULL,
                                               0);

    LOGE("videoStreamIndex = %d", videoStreamIndex);

    if (videoStreamIndex >= 0) {

        player->videoStreamIndex = videoStreamIndex;
        player->tgvideo = new TGVideo();

        AVCodecParameters *parameters = player->formatContext->streams[videoStreamIndex]->codecpar;
        AVCodec *codec = avcodec_find_decoder(parameters->codec_id);

        if (codec == NULL) {
            char msg[100];
            sprintf(msg, "audio codec cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }

        player->videoCodecContext = avcodec_alloc_context3(codec);

        player->tgvideo->duration = player->formatContext->streams[videoStreamIndex]->duration;

        if (player->videoCodecContext == NULL) {
            char msg[100];

            sprintf(msg, "video codec context cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }


        LOGE("video bits_per_raw_sample %d",parameters->bits_per_raw_sample);
        player->listenerCall->invokeVideoSize(parameters->width,parameters->height);


    }

    int audioStreamIndex = av_find_best_stream(player->formatContext, AVMEDIA_TYPE_AUDIO, -1, -1,
                                               NULL, 0);

    if (audioStreamIndex > 0) {
        player->audioStreamIndex = audioStreamIndex;
        player->tgaudio = new TGAudio(true);


        AVCodecParameters *parameters = player->formatContext->streams[audioStreamIndex]->codecpar;
        AVCodec *code = avcodec_find_decoder(parameters->codec_id);

        if (code == NULL) {
            char msg[100];

            sprintf(msg, "audio codec cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }

        player->tgaudio->findParams(parameters);

        player->audioCodecContext = avcodec_alloc_context3(code);

        player->tgaudio->duration = player->formatContext->streams[audioStreamIndex]->duration;

        LOGE("audiof bits_per_raw_sample %d",parameters->bits_per_raw_sample);
        if (player->audioCodecContext == NULL) {

            char msg[100];

            sprintf(msg, "audio codec context cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }

    }

    return 0;
}


int TGPlayer::setDataSource(const char *path) {

    int result = 0;
    int size = strlen(path);


    this->path = (char *) malloc(size);

    memset(this->path, 0, size);
    strcpy(this->path, path);

    return result;
}


void *preparing(void *data) {

    int result = 0;
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);

    player->formatContext = avformat_alloc_context();

    if (player->formatContext == NULL) {

        player->javaCallHandle->throwException(IllegalStateException,
                                               "setDataSource maybe not complete true");
        goto complete;
    }
    AVDictionary *dict;
    av_dict_set(&dict, "max_delay", "30000000", 0);


    result = avformat_open_input(&player->formatContext, player->path, NULL, &dict);


    if (result < 0) {
        LOGE("avformat_open_input FAILED %d reason is %s", result, av_err2str(result));

        char *msg = av_err2str(result);
//        sprintf(msg, "setDataSource failed %s", path);
        player->javaCallHandle->throwException(IOException, msg);

        goto complete;
    }


    result = avformat_find_stream_info(player->formatContext, NULL);

    if (result < 0) {
        LOGE("avformat_find_stream_info FAILED %d reason is %s", result, av_err2str(result));
        char *msg = av_err2str(result);
        player->javaCallHandle->throwException(IOException, msg);


        goto complete;
    }


//    av_dump_format(player->formatContext, -1, player->path, 0);


    result = findAVCodecContext(data);

    if (result < 0) {
        goto complete;
    }

    player->listenerCall->invokePrepared();

    LOGD("TGPlayer prepare finish");
    complete:
    pthread_exit(&player->prepareThread);
}


int TGPlayer::prepare() {


    pthread_mutex_lock(&playerMutex);


    int result = 0;

    formatContext = avformat_alloc_context();

    if (formatContext == NULL) {

        javaCallHandle->throwException(IllegalStateException,
                                       "setDataSource maybe not complete true");
        goto failed;
    }

    AVDictionary *dict;

    av_dict_set(&dict, "max_delay", "30000000", 0);


    result = avformat_open_input(&formatContext, path, NULL, &dict);


    if (result < 0) {
        LOGE("avformat_open_input FAILED %d reason is %s", result, av_err2str(result));

        char *msg = av_err2str(result);
//        sprintf(msg, "setDataSource failed %s", path);
        javaCallHandle->throwException(IOException, msg);

        goto failed;
    }


    result = avformat_find_stream_info(formatContext, NULL);

    if (result < 0) {
        LOGE("avformat_find_stream_info FAILED %d reason is %s", result, av_err2str(result));
//        player->javaCallHandle->inv(IOException, msg);


        goto failed;
    }


//    av_dump_format(player->formatContext, -1, player->path, 0);

    result = findAVCodecContext(this);

    if (result < 0) {
        goto failed;
    }


    LOGD("TGPlayer prepare finish");
    failed:
    pthread_mutex_unlock(&playerMutex);

    return result;
}


int TGPlayer::prepareSync() {


    pthread_mutex_lock(&playerMutex);

    pthread_create(&this->prepareThread, NULL, preparing, this);

    pthread_mutex_unlock(&playerMutex);

    return 0;
}


void *readFrame(void *data) {
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);


    int ret = -1;
    while (!player->exit) {

        if (player->pause) {
            av_usleep(1000 * 100);
            continue;
        }


        if (player->tgaudio != NULL && player->tgaudio->playerQueue->packetQueue.size() > 100) {
            av_usleep(1000 * 100);
            continue;
        }

        if (player->tgvideo != NULL && player->tgvideo->playerQueue->packetQueue.size() > 100) {
            av_usleep(1000 * 100);
            continue;
        }

        AVPacket *packet = av_packet_alloc();
        ret = av_read_frame(player->formatContext, packet);

        if (ret == 0) {
            if (packet->stream_index == player->videoStreamIndex) {
                player->tgvideo->playerQueue->pushPkt(packet);
            } else if (packet->stream_index == player->audioStreamIndex) {
                player->tgvideo->playerQueue->pushPkt(packet);
            } else {
                av_packet_free(&packet);
                av_free(packet);
                packet = NULL;
            }
        } else {
            av_packet_free(&packet);
            av_free(packet);
            packet = NULL;

            if ((player->tgvideo != NULL && player->tgvideo->playerQueue->frameQueue.empty()) ||
                (player->tgaudio != NULL && player->tgaudio->playerQueue->frameQueue.empty())) {
                player->exit = true;
            }
        }
    }


    player->listenerCall->invokeComplete();

    pthread_exit(&player->readFrameThread);
}

int TGPlayer::start() {

    pthread_mutex_lock(&playerMutex);

    pthread_create(&readFrameThread, NULL, readFrame, this);

    pthread_mutex_unlock(&playerMutex);
    return 0;
}