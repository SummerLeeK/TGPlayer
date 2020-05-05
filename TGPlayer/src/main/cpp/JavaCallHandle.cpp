//
// Created by Apple on 2020-03-10.
//

#include <native_log.h>
#include "JavaCallHandle.h"
#include "Exception.h"

JavaCallHandle::JavaCallHandle(JavaVM *vm) {
    this->vm = vm;
}

void
JavaCallHandle::invokeVoidMethod(jobject obj, jclass clazz, const char *methodName, const char *sig,
                                 va_list vl) {
    JNIEnv *env=NULL;
    int result=vm->GetEnv((void**)&env,JNI_VERSION_1_4);

    if (result<0){
        result= vm->AttachCurrentThread(&env,NULL);
    }
    jmethodID jmethodId = env->GetMethodID(clazz, methodName, sig);


    env->CallVoidMethod(obj, jmethodId, vl);

    if (result==0){
        vm->DetachCurrentThread();
    }
}

void JavaCallHandle::throwException(const char *exceptionClass, const char *message) {
   int attach= -1;
   JNIEnv* env=NULL;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4) < 0){
        attach = vm->AttachCurrentThread(&env, NULL);
    }
//   LOGE("JavaCallHandle throwException AttachCurrentThread = %d",result);
    jclass exception = env->FindClass(exceptionClass);
    if (exception != NULL) {
         env->ThrowNew(exception, message);
    }

    if(attach==0){
         vm->DetachCurrentThread();
    }



}

void JavaCallHandle::throwException(int type) {
    JNIEnv*env=NULL;
    int result=vm->GetEnv((void**)&env,JNI_VERSION_1_4);

    if (result<0){
        result = vm->AttachCurrentThread(&env, NULL);
    }

    if (type == -5) {
        jclass ioException = env->FindClass(IOException);
         env->ThrowNew(ioException, "I/O error");
    }


    if (result==0){
        vm->DetachCurrentThread();
    }
}