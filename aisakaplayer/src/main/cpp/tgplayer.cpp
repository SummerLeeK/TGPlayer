//
// Created by Apple on 2020-02-27.
//

#include <native_log.h>
#include "TGPlayer.h"
#include "Exception.h"


TGPlayer::TGPlayer() {


}


int TGPlayer::setDataSource(const char *path) {

    int result = 0;
    int size = strlen(path);


    this->path = (char *) malloc(size);

    memset(this->path, 0, size);
    strcpy(this->path, path);

    formatContext = avformat_alloc_context();

    if (formatContext == NULL) {
        result = -1;

        return result;
    }


    result = avformat_open_input(&formatContext, path, NULL, NULL);


    if (result < 0) {
        LOGE("avformat_open_input FAILED %d reason is %s", result, av_err2str(result));

        char *msg = av_err2str(result);
//        sprintf(msg, "setDataSource failed %s", path);
        javaCallHandle->throwException(IOException, msg);

        return result;
    }

    return result;
}

void *preparing(void *data) {

    int result = 0;
    TGPlayer *player = reinterpret_cast<TGPlayer *>(data);

    result = avformat_find_stream_info(player->formatContext, NULL);

    if (result < 0) {
        LOGE("avformat_find_stream_info FAILED %d reason is %s", result, av_err2str(result));
//        player->javaCallHandle->throwException(IOException, msg);
        return NULL;
    }


    av_dump_format(player->formatContext, -1, player->path, 0);


    int videoStreamIndex = av_find_best_stream(player->formatContext, AVMEDIA_TYPE_VIDEO, -1, -1,
                                               NULL,
                                               NULL);


    if (videoStreamIndex >= 0) {
        player->tgvideo = new TGVideo();
    }
}

int TGPlayer::prepare() {
    int result;
    if (formatContext == NULL) {

        javaCallHandle->throwException(IllegalStateException,
                                       "setDataSource maybe not complete true");
        return -1;
    }

    pthread_create(prepareThread, NULL, preparing, this);


    return 0;

}

int TGPlayer::start() {

    return 0;
}