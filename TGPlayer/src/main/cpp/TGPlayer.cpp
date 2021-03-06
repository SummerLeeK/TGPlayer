//
// Created by Apple on 2020-02-27.
//

#include <native_log.h>
#include <audio/OpenSLESPlayer.h>
#include <video/ANativeWindowRender.h>

extern "C" {
#include <libavutil/time.h>
#include <libavutil/mem.h>
#include <libavutil/channel_layout.h>
}

#include "TGPlayer.h"
#include "Exception.h"


TGPlayer::TGPlayer() {

    pthread_mutex_init(&playerMutex, NULL);

}

int findAVCodecContext(void *data) {
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);

    int videoStreamIndex = av_find_best_stream(player->formatContext, AVMEDIA_TYPE_VIDEO, -1, -1,
                                               NULL,
                                               0);

    LOGE("videoStreamIndex = %d", videoStreamIndex);

    if (videoStreamIndex >= 0) {

        player->videoStreamIndex = videoStreamIndex;


        AVCodecParameters *parameters = player->formatContext->streams[videoStreamIndex]->codecpar;
        AVCodec *codec = avcodec_find_decoder(parameters->codec_id);

        if (codec == NULL) {
            char msg[100];
            sprintf(msg, "audio codec cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }


        player->videoCodecContext = avcodec_alloc_context3(codec);

        player->videoPlayer = new ANativeWindowRender(parameters,player->videoCodecContext);




        if (player->videoCodecContext == NULL) {
            char msg[100];

            sprintf(msg, "video codec context cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }


        LOGE("video bits_per_raw_sample %d", parameters->bits_per_raw_sample);
        player->listenerCall->invokeVideoSize(parameters->width, parameters->height);


    }

    int audioStreamIndex = av_find_best_stream(player->formatContext, AVMEDIA_TYPE_AUDIO, -1, -1,
                                               NULL, 0);

    if (audioStreamIndex >= 0) {
        player->audioStreamIndex = audioStreamIndex;


        AVCodecParameters *parameters = player->formatContext->streams[audioStreamIndex]->codecpar;
        AVCodec *code = avcodec_find_decoder(parameters->codec_id);

        if (code == NULL) {
            char msg[100];

            sprintf(msg, "audio codec cant't find %d", parameters->codec_id);
            player->javaCallHandle->throwException(IOException, msg);
            return -1;
        }


        player->audioCodecContext = avcodec_alloc_context3(code);

        player->audioPlayer = new OpenSLESPlayer;

        player->audioPlayer->initPlayer(player->audioCodecContext, parameters);

        LOGE("audiof bits_per_raw_sample %d", parameters->bits_per_raw_sample);
        LOGE("audioplayer address %p",player->audioPlayer);
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


int TGPlayer::setVideoSurface(JNIEnv *env, jobject surfaceObj) {
    videoPlayer->initplayer(env, surfaceObj);
    return 0;
}

void *preparing(void *data) {

    int result = 0;
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);
    AVDictionary *dict = NULL;
    player->formatContext = avformat_alloc_context();

    if (player->formatContext == NULL) {

        player->javaCallHandle->throwException(IllegalStateException,
                                               "setDataSource maybe not complete true");
        char *msg = (char *) malloc(sizeof(char) * 200);
        sprintf(msg, "setDataSource maybe not complete true %s", player->path);
//        player->javaCallHandle->throwException(IOException, msg);
        player->listenerCall->invokeError(-22, msg);
        goto complete;
    }

    av_dict_set(&dict, "max_delay", "30000000", 0);


    result = avformat_open_input(&player->formatContext, player->path, NULL, NULL);


    if (result < 0) {
        LOGE("avformat_open_input FAILED %d reason is %s", result, av_err2str(result));

        char *msg = (char *) malloc(sizeof(char) * 200);
        sprintf(msg, "prepareAsync failed %s", player->path);
//        player->javaCallHandle->throwException(IOException, msg);
        player->listenerCall->invokeError(-22, msg);

        goto complete;
    }


    result = avformat_find_stream_info(player->formatContext, NULL);

    if (result < 0) {
        LOGE("avformat_find_stream_info FAILED %d reason is %s", result, av_err2str(result));
        char *msg = (char *) malloc(sizeof(char) * 200);
        sprintf(msg, "avformat_find_stream_info failed %s", player->path);
        player->listenerCall->invokeError(-22, msg);
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

    AVDictionary *dict = NULL;
    int result = 0;

    formatContext = avformat_alloc_context();

    if (formatContext == NULL) {

        javaCallHandle->throwException(IllegalStateException,
                                       "setDataSource maybe not complete true");
        goto failed;
    }


    av_dict_set(&dict, "max_delay", "30000000", 0);


    result = avformat_open_input(&formatContext, path, NULL, &dict);


    if (result < 0) {
        LOGE("avformat_open_input FAILED %d reason is %s", result, av_err2str(result));

        char *msg = (char *) malloc(sizeof(char) * 100);
        sprintf(msg, "setDataSource failed %s", path);
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

    LOGD("start read frame %d %d",player==NULL,true);
    int ret = -1;



    while (!player->exit) {

        if (player->pause) {
            av_usleep(1000 * 100);
            continue;
        }


        if (player->audioPlayer != NULL &&
            player->audioPlayer->decodeAudio->playerQueue->getPacketQueueSize() > 100) {
            av_usleep(1000 * 100);
            continue;
        }

        if (player->videoPlayer != NULL &&
            player->videoPlayer->decodeVideo->playerQueue->packetQueue.size() > 100) {
            av_usleep(1000 * 100);
            continue;
        }

        AVPacket *packet = av_packet_alloc();
        ret = av_read_frame(player->formatContext, packet);

        if (ret == 0) {
            if (packet->stream_index == player->videoStreamIndex) {
//                player->videoPlayer->decodeVideo->playerQueue->pushPkt(packet);
            } else if (packet->stream_index == player->audioStreamIndex) {
                player->audioPlayer->decodeAudio->playerQueue->pushPkt(packet);
            } else {
                av_packet_free(&packet);
                av_free(packet);
                packet = NULL;
            }
        } else {
            av_packet_free(&packet);
            av_free(packet);
            packet = NULL;

            if (
//                    (player->videoPlayer != NULL &&
//                 player->videoPlayer->decodeVideo->playerQueue->frameQueue.empty()) ||
                (player->audioPlayer != NULL &&
                 player->audioPlayer->decodeAudio->playerQueue->frameQueue.empty())) {
                player->exit = true;
            }
        }
    }


    player->listenerCall->invokeComplete();

    pthread_exit(&player->readFrameThread);
}

void* playThreadMethod(void*data){
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);

    player->audioPlayer->start();
    player->videoPlayer->start();
    pthread_exit(&player->playThread);
}

int TGPlayer::start() {


    LOGE("%s","start");
    pthread_mutex_lock(&playerMutex);

    pthread_create(&readFrameThread, NULL, readFrame, this);


    pthread_create(&playThread,NULL,playThreadMethod,this);


    pthread_mutex_unlock(&playerMutex);

    return 0;
}



