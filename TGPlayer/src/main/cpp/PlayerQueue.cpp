//
// Created by Apple on 2NULL2NULL-NULL3-1NULL.
//

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

            av_packet_free(&packet);
            av_free(packet);
            packet = NULL;
            break;
        } else {
            pthread_cond_wait(&packetCond, &packetMutex);
        }

    }

    pthread_cond_signal(&packetCond);
    pthread_mutex_unlock(&packetMutex);

    return 0;

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


PlayerQueue::~PlayerQueue() {

    pthread_mutex_destroy(&packetMutex);

    pthread_cond_destroy(&packetCond);

    pthread_mutex_destroy(&frameMutex);

    pthread_cond_destroy(&frameCond);
}