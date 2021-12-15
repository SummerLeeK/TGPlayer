//
// Created by Apple on 2020-03-22.
//

#ifndef PLAYERDEMO_ANATIVEWINDOWRENDER_H
#define PLAYERDEMO_ANATIVEWINDOWRENDER_H

#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <native_log.h>
extern "C"{
#include <libavutil/imgutils.h>
}
#include "BaseVideoPlayer.h"

class ANativeWindowRender : public BaseVideoPlayer {
public:
    ANativeWindowRender(const AVCodecParameters *codecParameters, AVCodecContext *avCodecContext);

    ANativeWindow *nativeWindow;

    pthread_t playerThread;

    double currentPTS=0;


    int initplayer(JNIEnv *env,jobject surface);

    int start();

    int pause();

    int release();


};


#endif //PLAYERDEMO_ANATIVEWINDOWRENDER_H
