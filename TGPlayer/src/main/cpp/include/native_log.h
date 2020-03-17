//
// Created by Apple on 2019-10-22.
//
#include <android/log.h>

#ifndef FFMPEGANDROID_NATIVE_LOG_H
#define FFMPEGANDROID_NATIVE_LOG_H

#endif //FFMPEGANDROID_NATIVE_LOG_H

#define TAG "TGPLAYER"

#define LOGV(FMT, ...) __android_log_print(ANDROID_LOG_VERBOSE,TAG, FMT,##__VA_ARGS__)
#define LOGD(FMT, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG, FMT,##__VA_ARGS__)
#define LOGI(FMT, ...) __android_log_print(ANDROID_LOG_INFO, TAG, FMT,##__VA_ARGS__)
#define LOGW(FMT, ...) __android_log_print(ANDROID_LOG_WARN,TAG, FMT,##__VA_ARGS__)
#define LOGE(FMT, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,FMT, ##__VA_ARGS__)

#define SLASSERT(x)                   \
  do {                                \
    assert(SL_RESULT_SUCCESS == (x)); \
    (void)(x);                        \
  } while (0)
