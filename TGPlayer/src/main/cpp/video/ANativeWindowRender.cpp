//
// Created by Apple on 2020-03-22.
//


#include "ANativeWindowRender.h"

ANativeWindowRender::ANativeWindowRender(const AVCodecParameters *codecParameters,
                                         AVCodecContext *avCodecContext)
        : BaseVideoPlayer(codecParameters, avCodecContext) {
    this->mAvCodecContext = avCodecContext;
    this->mCodecParameters = codecParameters;

    decodeVideo = new DecodeVideo(avCodecContext, codecParameters);

    decodeVideo->open_codec();

}

int ANativeWindowRender::initplayer(JNIEnv *env, jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);

    return 0;
}


void *playVideo(void *data) {
    ANativeWindowRender *render = reinterpret_cast<ANativeWindowRender *>(data);
    ANativeWindow_Buffer buffer;

    for (;;) {
        AVFrame *rgbframe = av_frame_alloc();
        int result = render->decodeVideo->decode(rgbframe);
        if (result == 0) {
            AVFrame *dst = av_frame_alloc();
            //计算 Buffer 的大小
            int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA, rgbframe->width,
                                                      rgbframe->height, 1);
//为 m_RGBAFrame 分配空间
            uint8_t *m_FrameBuffer = (uint8_t *) av_malloc(bufferSize * sizeof(uint8_t));


            av_image_fill_arrays(dst->data, dst->linesize, m_FrameBuffer, AV_PIX_FMT_RGBA,
                                 rgbframe->width, rgbframe->height, 1);


            render->decodeVideo->swsContext = sws_getContext(rgbframe->width,
                                                             rgbframe->height,
                                                             (AVPixelFormat) rgbframe->format,
                                                             rgbframe->width, rgbframe->height,
                                                             AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL,
                                                             NULL, NULL);
            sws_scale(render->decodeVideo->swsContext,
                      (const unsigned char *const *) rgbframe->data, rgbframe->linesize, 0,
                      rgbframe->height, dst->data, dst->linesize);


            ANativeWindow_setBuffersGeometry(render->nativeWindow, rgbframe->width,
                                             rgbframe->height,
                                             WINDOW_FORMAT_RGBA_8888);
            //3. 渲染
            ANativeWindow_Buffer m_NativeWindowBuffer;

//
            render->currentPTS = rgbframe->pts * av_q2d(rgbframe->time_base);
            LOGD(TAG,"video pts=%f",render->currentPTS);
//锁定当前 Window ，获取屏幕缓冲区 Buffer 的指针
            ANativeWindow_lock(render->nativeWindow, &m_NativeWindowBuffer, nullptr);
            uint8_t *dstBuffer = static_cast<uint8_t *>(m_NativeWindowBuffer.bits);
            int srcLineSize = dst->linesize[0];//输入图的步长（一行像素有多少字节）
            int dstLineSize = m_NativeWindowBuffer.stride * 4;//RGBA 缓冲区步长

            for (int i = 0; i < render->mCodecParameters->height; ++i) {
                //一行一行地拷贝图像数据
                memcpy(dstBuffer + i * dstLineSize, m_FrameBuffer + i * srcLineSize, srcLineSize);
            }

            for (int i = 0; i < rgbframe->height; ++i) {
                //一行一行地拷贝图像数据
                memcpy(dstBuffer + i * dstLineSize, m_FrameBuffer + i * srcLineSize, srcLineSize);
            }
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
    pthread_create(&playerThread, NULL, playVideo, this);
    return 0;
}

int ANativeWindowRender::pause() {
    return 0;
}

int ANativeWindowRender::release() {
    return 0;
}