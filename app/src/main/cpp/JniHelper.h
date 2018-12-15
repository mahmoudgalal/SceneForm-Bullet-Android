////////////////////////////////////////////////
// Created by Mahmoud Galal on 25/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////

#ifndef SCENEFORMTEST_JNIHELPER_H
#define SCENEFORMTEST_JNIHELPER_H

#include "BaseHeader.h"
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
extern EnvironmentContext e_ctx;
class JniHelper {

public:
    void setNodeWorldPosition(void* node,btVector3& postion);
    void setNodeWorldRotation(void* node,btQuaternion& rotation);
    void removeNativeNode(void* node);
    float getFloatAttribute(jfieldID fid,jobject obj);
    Vector3& convertToNativeVector(jobject javaVector);
};


#endif //SCENEFORMTEST_JNIHELPER_H
