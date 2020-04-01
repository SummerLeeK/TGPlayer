//
// Created by Apple on 2020-03-11.
//

#include <native_log.h>
#include "PlayerListenerCall.h"


PlayerListenerCall::PlayerListenerCall(JNIEnv *env, JavaVM *jvm) {
    this->env = env;
    this->jvm = jvm;


}

void PlayerListenerCall::initFindClass(jobject tgPlayer) {

    this->tgPlayer = tgPlayer;

//    jclass playerClazz = env->FindClass(JNI_CLASS_TGPLAYER);
//
//    jfieldID mOnCompletionListenerField = env->GetFieldID(playerClazz, "mOnCompletionListener",
//                                                          "Lcom/aisaka/media/TGPlayer$OnCompletionListener;");
//    OnCompletionListener = env->GetObjectField(tgPlayer, mOnCompletionListenerField);
//
//
//    jfieldID OnBufferingUpdateListenerField = env->GetFieldID(playerClazz,
//                                                              "mOnBufferingUpdateListener",
//                                                              "Lcom/aisaka/media/TGPlayer$OnBufferingUpdateListener;");
//    OnBufferingUpdateListener = env->GetObjectField(tgPlayer, OnBufferingUpdateListenerField);
//
//
//    jfieldID mOnSeekCompleteListenerField = env->GetFieldID(playerClazz, "mOnSeekCompleteListener",
//                                                            "Lcom/aisaka/media/TGPlayer$OnSeekCompleteListener;");
//    OnSeekCompleteListener = env->GetObjectField(tgPlayer, mOnSeekCompleteListenerField);
//
//
//    jfieldID mOnVideoSizeChangedListenerField = env->GetFieldID(playerClazz,
//                                                                "mOnVideoSizeChangedListener",
//                                                                "Lcom/aisaka/media/TGPlayer$OnVideoSizeChangedListener;");
//    OnVideoSizeChanged = env->GetObjectField(tgPlayer, mOnVideoSizeChangedListenerField);
//
//
//    jfieldID mOnErrorListenerField = env->GetFieldID(playerClazz, "mOnErrorListener",
//                                                     "Lcom/aisaka/media/TGPlayer$OnErrorListener;");
//    OnSeekCompleteListener = env->GetObjectField(tgPlayer, mOnErrorListenerField);
//
//
//    jfieldID mOnInfoListenerField = env->GetFieldID(playerClazz, "mOnInfoListener",
//                                                    "Lcom/aisaka/media/TGPlayer$OnInfoListener;");
//    OnInfoListener = env->GetObjectField(tgPlayer, mOnInfoListenerField);

}


void PlayerListenerCall::invokePrepared() {

    int attach = -1;

    attach = jvm->AttachCurrentThread(&env, NULL);


    jclass playerClazz = env->GetObjectClass(tgPlayer);

    jfieldID mOnPreparedListenerField = env->GetFieldID(playerClazz, "mOnPreparedListener",
                                                        "Lcom/aisaka/media/TGPlayer$OnPreparedListener;");


    jobject OnPreparedListener = env->GetObjectField(tgPlayer, mOnPreparedListenerField);

    if (OnPreparedListener != NULL) {

        jclass clazz = env->GetObjectClass(OnPreparedListener);

        if (clazz != NULL) {
            jmethodID onPrepared = env->GetMethodID(clazz, "onPrepared",
                                                    "(Lcom/aisaka/media/TGPlayer;)V");
            if (onPrepared != NULL) {
                env->CallVoidMethod(OnPreparedListener, onPrepared, tgPlayer);
            }
        }
    }


    if (attach == 0) {
        jvm->DetachCurrentThread();
    }

}

void PlayerListenerCall::invokeComplete() {


    int attach = -1;

    attach = jvm->AttachCurrentThread(&env, NULL);


    jclass playerClazz = env->GetObjectClass(tgPlayer);

    jfieldID mOnCompleteListenerField = env->GetFieldID(playerClazz, "mOnCompletionListener",
                                                        "Lcom/aisaka/media/TGPlayer$OnCompletionListener;");


    jobject OnCompleteListener = env->GetObjectField(tgPlayer, mOnCompleteListenerField);

    if (OnCompleteListener != NULL) {

        jclass clazz = env->GetObjectClass(OnCompleteListener);

        if (clazz != NULL) {
            jmethodID onComplete = env->GetMethodID(clazz, "onCompletion",
                                                    "(Lcom/aisaka/media/TGPlayer;)V");
            if (onComplete != NULL) {
                env->CallVoidMethod(OnCompleteListener, onComplete, tgPlayer);
            }
        }
    }


    if (attach == 0) {
        jvm->DetachCurrentThread();
    }

}


void PlayerListenerCall::invokeVideoSize(int width, int height) {

    int attach = -1;

    attach = jvm->AttachCurrentThread(&env, NULL);


    jclass playerClazz = env->GetObjectClass(tgPlayer);

    jfieldID mOnVideoSizeChangedListenerField = env->GetFieldID(playerClazz, "mOnVideoSizeChangedListener",
                                                        "Lcom/aisaka/media/TGPlayer$OnVideoSizeChangedListener;");


    jobject mOnVideoSizeChangedListener = env->GetObjectField(tgPlayer, mOnVideoSizeChangedListenerField);

    if (mOnVideoSizeChangedListener != NULL) {

        jclass clazz = env->GetObjectClass(mOnVideoSizeChangedListener);

        if (clazz != NULL) {
            jmethodID videoSizeChange = env->GetMethodID(clazz, "onVideoSizeChanged",
                                                    "(Lcom/aisaka/media/TGPlayer;II)V");
            if (videoSizeChange != NULL) {
                env->CallVoidMethod(mOnVideoSizeChangedListener, videoSizeChange, tgPlayer,width,height);
            }
        }
    }


    if (attach == 0) {
        jvm->DetachCurrentThread();
    }
}