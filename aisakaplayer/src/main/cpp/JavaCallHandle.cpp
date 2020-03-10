//
// Created by Apple on 2020-03-10.
//

#include "JavaCallHandle.h"
#include "Exception.h"

JavaCallHandle::JavaCallHandle(JNIEnv *env, JavaVM *vm) {
    this->env = env;
    this->vm = vm;
}

void
JavaCallHandle::invokeVoidMethod(jobject obj, jclass clazz, const char *methodName, const char *sig,
                                 va_list vl) {
    jmethodID jmethodId = env->GetMethodID(clazz, methodName, sig);


    env->CallVoidMethod(obj, jmethodId, vl);
}

int JavaCallHandle::throwException(const char *exceptionClass, const char *message) {


    jclass exception = env->FindClass(exceptionClass);
    if (exception != NULL) {
        return env->ThrowNew(exception, message);
    }

    return -1;

}

int JavaCallHandle::throwException(int type) {
    if (type == -5) {
        jclass ioException=env->FindClass(IOException);
        return env->ThrowNew(ioException, "I/O error");
    }
}