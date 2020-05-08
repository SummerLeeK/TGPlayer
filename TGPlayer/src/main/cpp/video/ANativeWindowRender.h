//
// Created by Apple on 2020-03-22.
//

#ifndef PLAYERDEMO_ANATIVEWINDOWRENDER_H
#define PLAYERDEMO_ANATIVEWINDOWRENDER_H


#include "BaseVideoPlayer.h"
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <native_log.h>
extern "C"{
#include <libavutil/imgutils.h>
};


class ANativeWindowRender : public BaseVideoPlayer {
public:
    ANativeWindow *nativeWindow;
    const AVCodecParameters *codecParameters;
    AVCodecContext *avCodecContext;
    pthread_t playerThread;

    ANativeWindowRender(const AVCodecParameters *codecParameters, AVCodecContext *avCodecContext);



    int initplayer(JNIEnv *env,jobject surface);

    int start();

    int pause();

    int release();


};


#endif //PLAYERDEMO_ANATIVEWINDOWRENDER_H
