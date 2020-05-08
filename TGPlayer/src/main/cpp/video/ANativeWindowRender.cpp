//
// Created by Apple on 2020-03-22.
//


#include "ANativeWindowRender.h"

ANativeWindowRender::ANativeWindowRender(const AVCodecParameters *codecParameters,
                                         AVCodecContext *avCodecContext) : BaseVideoPlayer(
        codecParameters, avCodecContext) {
    this->avCodecContext = avCodecContext;
    this->codecParameters = codecParameters;

    decodeVideo = new DecodeVideo(avCodecContext, codecParameters);
}

int ANativeWindowRender::initplayer(JNIEnv *env, jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);

    decodeVideo->open_codec();

    return 0;
}


void *playVideo(void *data) {
    ANativeWindowRender *render = reinterpret_cast<ANativeWindowRender *>(data);
    ANativeWindow_Buffer buffer;

    AVFrame *rgbframe = av_frame_alloc();
    for (;;) {

        int result = render->decodeVideo->decode(rgbframe);
        if (result == 0) {
            ANativeWindow_setBuffersGeometry(render->nativeWindow, rgbframe->width, rgbframe->height,
                                             WINDOW_FORMAT_RGBA_8888);
            ANativeWindow_lock(render->nativeWindow, &buffer, NULL);

            av_image_fill_arrays(rgbframe->data, rgbframe->linesize,
                                 static_cast<const uint8_t *>(buffer.bits), AV_PIX_FMT_RGBA,
                                 rgbframe->width,
                                 rgbframe->height, 1);

            ANativeWindow_unlockAndPost(render->nativeWindow);
        }
    }

    pthread_exit(&render->playerThread);
}

int ANativeWindowRender::start() {
    pthread_create(&playerThread,NULL,playVideo,this);
    return 0;
}

int ANativeWindowRender::pause() {
    return 0;
}

int ANativeWindowRender::release() {
    return 0;
}