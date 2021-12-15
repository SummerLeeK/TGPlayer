//
// Created by Apple on 2NULL2NULL-NULL3-1NULL.
//

#include <native_log.h>
#include "PlayerQueue.h"

PlayerQueue::PlayerQueue() {

    pthread_mutex_init(&packetMutex, NULL);

    pthread_cond_init(&packetCond, NULL);

    pthread_mutex_init(&frameMutex, NULL);

    pthread_cond_init(&frameCond, NULL);
}


int PlayerQueue::pushPkt(AVPacket *pkt) {

    pthread_mutex_lock(&packetMutex);
    packetQueue.push(pkt);
    pthread_cond_signal(&packetCond);
    pthread_mutex_unlock(&packetMutex);

    LOGD("playqueue push packet");
    return 0;

}


int PlayerQueue::popPkt(AVPacket *pkt) {
    pthread_mutex_lock(&packetMutex);


    while (true) {

        if (packetQueue.size() > 0) {
            AVPacket *packet = packetQueue.front();

            if (av_packet_ref(pkt, packet) == 0) {
                packetQueue.pop();
            }

            av_packet_unref(packet);
//            av_free(packet);
//            packet = NULL;
            break;
        } else {
            pthread_cond_wait(&packetCond, &packetMutex);
        }

    }


    pthread_cond_signal(&packetCond);
    pthread_mutex_unlock(&packetMutex);
    LOGD("playqueue pop packet");
    return 0;

}

int PlayerQueue::getPkt(AVPacket *pkt) {
    int result = -1;
    pthread_mutex_lock(&packetMutex);

    while (true) {

        if (packetQueue.size() > 0) {
            AVPacket *packet = packetQueue.front();

            if (av_packet_ref(pkt, packet)==0){
                packetQueue.pop();
                av_packet_free(&packet);
                av_free(packet);
                packet = NULL;
                result=0;
            }
            break;
        } else {
            pthread_cond_wait(&packetCond, &packetMutex);
        }

    }

    pthread_mutex_unlock(&packetMutex);
    LOGD("playqueue pop packet");
    return result;

}


int PlayerQueue::pushFrame(AVFrame *frame) {

    pthread_mutex_lock(&frameMutex);

    frameQueue.push(frame);
    pthread_cond_signal(&frameCond);
    pthread_mutex_unlock(&frameMutex);

    return 0;
}

int PlayerQueue::popFrame(AVFrame *frame) {


    pthread_mutex_lock(&frameMutex);

    while (true) {

        if (frameQueue.size() > 0) {
            AVFrame *tempFrame = frameQueue.front();

            if (av_frame_ref(frame, tempFrame) == 0) {
                frameQueue.pop();
            }

            av_frame_free(&tempFrame);
            av_free(tempFrame);
            tempFrame = NULL;
            break;
        } else {
            pthread_cond_wait(&frameCond, &frameMutex);
        }

    }

    pthread_mutex_unlock(&frameMutex);
    return 0;
}


int PlayerQueue::getPacketQueueSize() {
    int size = 0;

    pthread_mutex_lock(&packetMutex);

    size = packetQueue.size();
    pthread_mutex_unlock(&packetMutex);

    return size;

}


int PlayerQueue::getFrameQueueSize() {

    int size = 0;

    pthread_mutex_lock(&frameMutex);

    size = frameQueue.size();

    pthread_mutex_unlock(&frameMutex);

    return size;

}


void PlayerQueue::clearPacketQueue() {

    pthread_cond_signal(&packetCond);

}

PlayerQueue::~PlayerQueue() {

    pthread_mutex_destroy(&packetMutex);

    pthread_cond_destroy(&packetCond);

    pthread_mutex_destroy(&frameMutex);

    pthread_cond_destroy(&frameCond);
}
