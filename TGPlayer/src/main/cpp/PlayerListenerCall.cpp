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
    jclass playerClazz = env->FindClass(JNI_CLASS_TGPLAYER);
    jfieldID mOnPreparedListenerField = env->GetFieldID(playerClazz, "mOnPreparedListener",
                                                        "Lcom/aisaka/media/TGPlayer$OnPreparedListener;");
    OnPreparedListener = env->GetObjectField(tgPlayer, mOnPreparedListenerField);


    jfieldID mOnCompletionListenerField = env->GetFieldID(playerClazz, "mOnCompletionListener",
                                                          "Lcom/aisaka/media/TGPlayer$OnCompletionListener;");
    OnCompletionListener = env->GetObjectField(tgPlayer, mOnCompletionListenerField);


    jfieldID OnBufferingUpdateListenerField = env->GetFieldID(playerClazz,
                                                              "mOnBufferingUpdateListener",
                                                              "Lcom/aisaka/media/TGPlayer$OnBufferingUpdateListener;");
    OnBufferingUpdateListener = env->GetObjectField(tgPlayer, OnBufferingUpdateListenerField);


    jfieldID mOnSeekCompleteListenerField = env->GetFieldID(playerClazz, "mOnSeekCompleteListener",
                                                            "Lcom/aisaka/media/TGPlayer$OnSeekCompleteListener;");
    OnSeekCompleteListener = env->GetObjectField(tgPlayer, mOnSeekCompleteListenerField);


    jfieldID mOnVideoSizeChangedListenerField = env->GetFieldID(playerClazz,
                                                                "mOnVideoSizeChangedListener",
                                                                "Lcom/aisaka/media/TGPlayer$OnVideoSizeChangedListener;");
    OnVideoSizeChanged = env->GetObjectField(tgPlayer, mOnVideoSizeChangedListenerField);


    jfieldID mOnErrorListenerField = env->GetFieldID(playerClazz, "mOnErrorListener",
                                                     "Lcom/aisaka/media/TGPlayer$OnErrorListener;");
    OnSeekCompleteListener = env->GetObjectField(tgPlayer, mOnErrorListenerField);


    jfieldID mOnInfoListenerField = env->GetFieldID(playerClazz, "mOnInfoListener",
                                                    "Lcom/aisaka/media/TGPlayer$OnInfoListener;");
    OnInfoListener = env->GetObjectField(tgPlayer, mOnInfoListenerField);

}


void PlayerListenerCall::invokePrepared() {

    int result=jvm->AttachCurrentThread(&env, NULL);

    LOGE("PlayerListenerCall invokePrepared AttachCurrentThread = %d",result);
    if (OnPreparedListener != NULL) {

        jclass clazz = env->FindClass(PREPARED_LISTENER);

        jmethodID onPrepared = env->GetMethodID(clazz, "onPrepared",
                                                "(Lcom/aisaka/media/TGPlayer;)V");

        env->CallVoidMethod(OnPreparedListener, onPrepared, tgPlayer);
    }

    jvm->DetachCurrentThread();

}