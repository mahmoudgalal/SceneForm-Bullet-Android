////////////////////////////////////////////////
// Created by Mahmoud Galal on 25/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////

#ifndef SCENEFORMTEST_BASEHEADER_H
#define SCENEFORMTEST_BASEHEADER_H

#include <jni.h>
#include <string>
// for __android_log_print(ANDROID_LOG_INFO, "YourApp", "formatted message");
#include <android/log.h>
#define TAG "NativeBulletScene"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

typedef struct environment_context {
    JavaVM  *javaVM;
    JNIEnv* env;
    jclass   nodeClz;
    jclass   vector3Clz;
    jclass   quaternionClz;
    jmethodID  setWorldPositionMID;
    jmethodID  setWorldRotationMID;
    jmethodID  vector3CID;
    jmethodID  quaternionCID;
    /////////////////////////
    jfieldID vector3XfieldId;
    jfieldID vector3YfieldId;
    jfieldID vector3ZfieldId;
    //jobject  mainActivityObj;
} EnvironmentContext;
#define  PI 3.1415926
class Vector3 {
public:
    Vector3():x(0.f),y(0.0f),z(0.f){}
    Vector3(float _x,float _y,float _z):x(_x),y(_y),z(_z){}
public:
    float x,y,z;
};

#endif //SCENEFORMTEST_BASEHEADER_H
