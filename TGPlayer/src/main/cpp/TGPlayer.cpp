//
// Created by Apple on 2020-02-27.
//

#include <native_log.h>
#include "TGPlayer.h"
#include "Exception.h"


TGPlayer::TGPlayer() {

    pthread_mutex_init(&playerMutex, NULL);

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
        result = -1;

        return NULL;
    }

    AVDictionary *dict;
    av_dict_set(&dict,"max_delay","30000000",0);


    result = avformat_open_input(&player->formatContext,player->path, NULL, &dict);


    if (result < 0) {
        LOGE("avformat_open_input FAILED %d reason is %s", result, av_err2str(result));

        char *msg = av_err2str(result);
//        sprintf(msg, "setDataSource failed %s", path);
        player->javaCallHandle->throwException(IOException, msg);

        return NULL;
    }


    result = avformat_find_stream_info(player->formatContext, NULL);

    if (result < 0) {
        LOGE("avformat_find_stream_info FAILED %d reason is %s", result, av_err2str(result));
//        player->javaCallHandle->inv(IOException, msg);


        return NULL;
    }


//    av_dump_format(player->formatContext, -1, player->path, 0);


    int videoStreamIndex = av_find_best_stream(player->formatContext, AVMEDIA_TYPE_VIDEO, -1, -1,
                                               NULL,
                                               NULL);

    LOGE("videoStreamIndex = %d",videoStreamIndex);

    if (videoStreamIndex >= 0) {

        player->tgvideo = new TGVideo();
    }

    player->listenerCall->invokePrepared();
}

int TGPlayer::prepare() {

    if (formatContext == NULL) {

        javaCallHandle->throwException(IllegalStateException,
                                       "setDataSource maybe not complete true");
        return -1;
    }

    pthread_mutex_lock(&playerMutex);

    preparing(this);

    pthread_mutex_unlock(&playerMutex);

    return 0;

}

int TGPlayer::prepareSync() {
    if (formatContext == NULL) {

        javaCallHandle->throwException(IllegalStateException,
                                       "setDataSource maybe not complete true");
        return -1;
    }

    pthread_mutex_lock(&playerMutex);

    pthread_create(&prepareThread, NULL, preparing, this);

    pthread_mutex_unlock(&playerMutex);

    return 0;
}