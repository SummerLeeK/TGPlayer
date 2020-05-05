//
// Created by Apple on 2020-03-11.
//

#ifndef PLAYERDEMO_PLAYERLISTENERCALL_H
#define PLAYERDEMO_PLAYERLISTENERCALL_H

#include <jni.h>

#define JNI_CLASS_TGPLAYER   "com/aisaka/media/TGPlayer"
#define PREPARED_LISTENER    "com/aisaka/media/TGPlayer$OnPreparedListener"

class PlayerListenerCall {
private:
    JavaVM *jvm;
    jobject tgPlayer;
    jclass playerClazz;
    jmethodID mOnPreparedMethod;
    jobject OnPreparedListener;
public:
    PlayerListenerCall( JavaVM *jvm);


    void initFindClass(jobject tgplayer);

    void invokePrepared();


    void invokeComplete();

    void invokeBufferingUpdate();

    void invokeVideoSize(int width, int height);

    void invokeError(int code, const char *extra);

    void invokeInfo(int what, int extra);


};


#endif //PLAYERDEMO_PLAYERLISTENERCALL_H
