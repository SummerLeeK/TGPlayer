//
// Created by Apple on 2020-02-27.
//

// ----------------------------------------------------------------------------

#include <jni.h>
#include <pthread.h>
#include <stdbool.h>
#include <android/log.h>
#include <native_log.h>
#include "TGPlayer.h"
#include "JavaCallHandle.h"
#include "PlayerListenerCall.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
}


#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))


JavaVM *jvm;

pthread_mutex_t mutex;
static jobject globalRefTGPlayer;
JavaCallHandle *javaCallHandle;
PlayerListenerCall *listenerCall;

static void setTGPlayerPtr(JNIEnv *env, jobject thiz, void *player) {

    jclass clazz = env->FindClass(JNI_CLASS_TGPLAYER);

    jfieldID playerPtr = env->GetFieldID(clazz, "playerPtr", "J");

    env->SetLongField(thiz, playerPtr, (long) player);

    LOGD("%ld", reinterpret_cast<long>(player));
}


static TGPlayer *getTGPlayerPtr(JNIEnv *env, jobject thiz) {

    jclass clazz = env->FindClass(JNI_CLASS_TGPLAYER);

    jfieldID playerPtr = env->GetFieldID(clazz, "playerPtr", "J");

    long ptr = env->GetLongField(thiz, playerPtr);


    LOGE("%ld", ptr);

    return reinterpret_cast<TGPlayer *>(ptr);

}

static void TGPlayer_setDataSourceAndHeaders(JNIEnv *env, jobject thiz, jstring pathstring) {

    const char *path = env->GetStringUTFChars(pathstring, NULL);

    TGPlayer *player = getTGPlayerPtr(env, thiz);

    player->setDataSource(path);

    env->ReleaseStringUTFChars(pathstring, path);
}


static void TGPlayer_setVideoSurface(JNIEnv *env, jobject thiz, jobject surface) {
    TGPlayer *player = getTGPlayerPtr(env, thiz);

    player->setVideoSurface(env,surface);

}

static void TGPlayer_prepareAsync(JNIEnv *env, jobject thiz) {
    TGPlayer *player = getTGPlayerPtr(env, thiz);

    player->prepareSync();

}

static void TGPlayer_prepare(JNIEnv *env, jobject thiz) {
    TGPlayer *player = getTGPlayerPtr(env, thiz);

    player->prepare();

}

static void TGPlayer_start(JNIEnv *env, jobject thiz) {
    TGPlayer *player = getTGPlayerPtr(env, thiz);

    player->start();
}

static void TGPlayer_stop(JNIEnv *env, jobject thiz) {

}


static void TGPlayer_seekTo(JNIEnv *env, jobject thiz, jlong msec, jint mode) {

}

static void TGPlayer_pause(JNIEnv *env, jobject thiz) {

}

static void TGPlayer_isPlaying(JNIEnv *env, jobject thiz) {

}

static jobject TGPlayer_getFrameAtTime(JNIEnv *env, jobject thiz, jlong msec, int mode) {

    return NULL;
}

static jint TGPlayer_getCurrentPosition(JNIEnv *env, jobject thiz) {

    return 0;

}

static jint TGPlayer_getDuration(JNIEnv *env, jobject thiz) {
    return 0;
}

static void TGPlayer_release(JNIEnv *env, jobject thiz) {

}


static void TGPlayer_reset(JNIEnv *env, jobject thiz) {

}


static void
TGPlayer_setVolume(JNIEnv *env, jobject thiz, jfloat leftVolume, jfloat rightVolume) {

}


static void TGPlayer_native_init(JNIEnv *env, jobject thiz) {

}

static void TGPlayer_native_setup(JNIEnv *env, jobject thiz) {


    globalRefTGPlayer = env->NewGlobalRef(thiz);
    TGPlayer *player = new TGPlayer();

    listenerCall->initFindClass(thiz);
    player->javaCallHandle = javaCallHandle;

    player->listenerCall = listenerCall;
    setTGPlayerPtr(env, globalRefTGPlayer, player);
}


static jobject TGPlayer_getMediaMeta(JNIEnv *env, jobject thiz) {
    return NULL;
}


static JNINativeMethod g_methods[] = {
        {
                "_setDataSource",
                                       "(Ljava/lang/String;)V",
                                                                        (void *) TGPlayer_setDataSourceAndHeaders
        },
//        { "_setDataSourceFd",       "(I)V",     (void *) TGPlayer_setDataSourceFd },
//        { "_setDataSource",         "(Ltv/danmaku/ijk/media/player/misc/IMediaDataSource;)V", (void *)TGPlayer_setDataSourceCallback },
//        { "_setAndroidIOCallback",  "(Ltv/danmaku/ijk/media/player/misc/IAndroidIO;)V", (void *)TGPlayer_setAndroidIOCallback },

        {       "_setVideoSurface",    "(Landroid/view/Surface;)V",     (void *) TGPlayer_setVideoSurface},

                {       "_prepare",       "()V",                           (void *) TGPlayer_prepare},
        {       "_prepareAsync",       "()V",                           (void *) TGPlayer_prepareAsync},
        {       "_start",              "()V",                           (void *) TGPlayer_start},
        {       "_stop",               "()V",                           (void *) TGPlayer_stop},
        {       "_seekTo",             "(JI)V",                         (void *) TGPlayer_seekTo},
        {       "_pause",              "()V",                           (void *) TGPlayer_pause},
        {       "_isPlaying",          "()Z",                           (void *) TGPlayer_isPlaying},
        {       "_getCurrentPosition", "()J",                           (void *) TGPlayer_getCurrentPosition},
        {       "_getDuration",        "()J",                           (void *) TGPlayer_getDuration},
        {       "_release",            "()V",                           (void *) TGPlayer_release},
        {       "_reset",              "()V",                           (void *) TGPlayer_reset},
        {       "_setVolume",          "(FF)V",                         (void *) TGPlayer_setVolume},
//        { "getAudioSessionId",      "()I",      (void *) TGPlayer_getAudioSessionId },
        {       "native_init",         "()V",                           (void *) TGPlayer_native_init},
        {       "native_setup",        "(Ljava/lang/Object;)V",         (void *) TGPlayer_native_setup},
//        { "native_finalize",        "()V",      (void *) TGPlayer_native_finalize },

//        { "_setOption",             "(ILjava/lang/String;Ljava/lang/String;)V", (void *) TGPlayer_setOption },
//        { "_setOption",             "(ILjava/lang/String;J)V",                  (void *) TGPlayer_setOptionLong },

//        { "_getColorFormatName",    "(I)Ljava/lang/String;",    (void *) TGPlayer_getColorFormatName },
//        { "_getVideoCodecInfo",     "()Ljava/lang/String;",     (void *) TGPlayer_getVideoCodecInfo },
//        { "_getAudioCodecInfo",     "()Ljava/lang/String;",     (void *) TGPlayer_getAudioCodecInfo },
        {       "_getMetadata",        "()Landroid/os/Bundle;",         (void *) TGPlayer_getMediaMeta},
        {       "_getFrameAtTime",     "(JI)Landroid/graphics/Bitmap;", (void *) TGPlayer_getFrameAtTime}
//        { "_setLoopCount",          "(I)V",                     (void *) TGPlayer_setLoopCount },
//        { "_getLoopCount",          "()I",                      (void *) TGPlayer_getLoopCount },
//        { "_getPropertyFloat",      "(IF)F",                    (void *) ijkMediaPlayer_getPropertyFloat },
//        { "_setPropertyFloat",      "(IF)V",                    (void *) ijkMediaPlayer_setPropertyFloat },
//        { "_getPropertyLong",       "(IJ)J",                    (void *) ijkMediaPlayer_getPropertyLong },
//        { "_setPropertyLong",       "(IJ)V",                    (void *) ijkMediaPlayer_setPropertyLong },
//        { "_setStreamSelected",     "(IZ)V",                    (void *) ijkMediaPlayer_setStreamSelected },

//        { "native_profileBegin",    "(Ljava/lang/String;)V",    (void *) TGPlayer_native_profileBegin },
//        { "native_profileEnd",      "()V",                      (void *) TGPlayer_native_profileEnd },

//        { "native_setLogLevel",     "(I)V",                     (void *) TGPlayer_native_setLogLevel },
//        { "_setFrameAtTime",        "(Ljava/lang/String;JJII)V", (void *) TGPlayer_setFrameAtTime },
};

bool isFFmpegInited = false;


void ffmpeg_log_callback(void *avcl, int level, const char *fmt,
                         va_list vl) {


    va_list vl2;
    char line[1024];
    static int print_prefix = 1;


    va_copy(vl2, vl);
    av_log_format_line(avcl, level, fmt, vl2, line, sizeof(line), &print_prefix);
    va_end(vl2);


    __android_log_print(ANDROID_LOG_ERROR, "Player", "%s", line);
}

void FFmpeg_init() {

    if (isFFmpegInited)
        return;


    av_log_set_callback(&ffmpeg_log_callback);
//    avcodec_register_all();

    avdevice_register_all();

//    avfilter_register_all();

//    av_register_all();

    avformat_network_init();

    isFFmpegInited = true;

}


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *rev) {

    JNIEnv *env = NULL;
    jvm = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {

        return -1;
    }

    jclass tgplayer_clz = env->FindClass(JNI_CLASS_TGPLAYER);

    env->RegisterNatives(tgplayer_clz, g_methods, NELEM(g_methods));

    pthread_mutex_init(&mutex, NULL);

    javaCallHandle = new JavaCallHandle(vm);
    listenerCall = new PlayerListenerCall(vm);

    FFmpeg_init();

    return JNI_VERSION_1_4;

}


JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved) {

    delete javaCallHandle;

    delete listenerCall;

    pthread_mutex_destroy(&mutex);
}
