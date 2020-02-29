//
// Created by Apple on 2019-10-22.
//
#include <android/log.h>
#ifndef FFMPEGANDROID_NATIVE_LOG_H
#define FFMPEGANDROID_NATIVE_LOG_H

#endif //FFMPEGANDROID_NATIVE_LOG_H


#define LOGV(TAG, ...) __android_log_print(ANDROID_LOG_VERBOSE,TAG, __VA_ARGS__);
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG, __VA_ARGS__);
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);
#define LOGW(TAG, ...) __android_log_print(ANDROID_LOG_WARN,TAG, __VA_ARGS__);
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG, __VA_ARGS__);

#define SLASSERT(x)                   \
  do {                                \
    assert(SL_RESULT_SUCCESS == (x)); \
    (void)(x);                        \
  } while (0)
