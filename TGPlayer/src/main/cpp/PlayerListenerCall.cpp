//
// Created by Apple on 2020-03-11.
//

#include <native_log.h>
#include "PlayerListenerCall.h"


PlayerListenerCall::PlayerListenerCall(JavaVM *jvm) {
    this->jvm = jvm;


}

void PlayerListenerCall::initFindClass(jobject tgPlayer) {

    JNIEnv *env=NULL;
    int result=jvm->GetEnv((void**)&env,JNI_VERSION_1_4);

    this->tgPlayer = env->NewGlobalRef(tgPlayer);



}


void PlayerListenerCall::invokePrepared() {

    int attach = -1;

    JNIEnv *env=NULL;
    int ret=jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4);
    LOGE("GetEnv result %d",ret);
    if (env==NULL){
        attach = jvm->AttachCurrentThread(&env, NULL);
        LOGE("AttachCurrentThread %d",attach);
    }

    LOGE("AttachCurrentThread %d",tgPlayer==NULL);
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
    JNIEnv *env=NULL;
    if (jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4) < 0){
        attach = jvm->AttachCurrentThread(&env, NULL);
    }


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
    JNIEnv *env=NULL;
    if (jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4) < 0){
        attach = jvm->AttachCurrentThread(&env, NULL);
    }

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

void PlayerListenerCall::invokeError(int code, const char *extra) {

    int attach = -1;
    JNIEnv *env=NULL;
    if (jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4) < 0){
        attach = jvm->AttachCurrentThread(&env, NULL);
    }




    jclass playerClazz = env->GetObjectClass(tgPlayer);

    jfieldID mOnErrorListenerField = env->GetFieldID(playerClazz, "mOnErrorListener",
                                                                "Lcom/aisaka/media/TGPlayer$OnErrorListener;");


    jobject mOnErrorListener = env->GetObjectField(tgPlayer, mOnErrorListenerField);

    if (mOnErrorListener != NULL) {

        jclass clazz = env->GetObjectClass(mOnErrorListener);

        if (clazz != NULL) {
            jmethodID videoSizeChange = env->GetMethodID(clazz, "onError",
                                                         "(Lcom/aisaka/media/TGPlayer;ILjava/lang/String;)V");
            if (videoSizeChange != NULL) {
                jstring msg=env->NewStringUTF(extra);
                env->CallVoidMethod(mOnErrorListener, videoSizeChange, tgPlayer,code,msg);
                env->ReleaseStringUTFChars(msg,extra);
            }
        }
    }


    if (attach == 0) {
        jvm->DetachCurrentThread();
    }

}