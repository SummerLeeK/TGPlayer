//
// Created by Apple on 2020-03-10.
//

#ifndef PLAYERDEMO_JAVACALLHANDLE_H
#define PLAYERDEMO_JAVACALLHANDLE_H

#include <jni.h>

class JavaCallHandle {
public:
    JNIEnv *env;
    JavaVM *vm;

    JavaCallHandle(JNIEnv *env,JavaVM *vm);

    void invokeVoidMethod(jobject obi, jclass clazz, const char *methodName, const char *sig,va_list vl);

    int throwException(const char* exceptionClass, const char *message);

    int throwException(int type);

};


#endif //PLAYERDEMO_JAVACALLHANDLE_H
