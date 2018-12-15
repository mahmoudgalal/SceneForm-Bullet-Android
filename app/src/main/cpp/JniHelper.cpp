////////////////////////////////////////////////
// Created by Mahmoud Galal on 25/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////

#include "JniHelper.h"


void JniHelper::setNodeWorldPosition(void *node, btVector3 &postion) {
    jclass nodeClass = e_ctx.nodeClz;
    jclass  vector3Class = e_ctx.vector3Clz;
    jobject nodeObject = reinterpret_cast<jobject >(node);
    if(!nodeObject){
        LOGE("Error retrieving node...");
        return;
    }
    jobject javaPosition = e_ctx.env->NewObject(e_ctx.vector3Clz,e_ctx.vector3CID,
                                                postion.x(),postion.y(),postion.z());
    if(javaPosition){
        e_ctx.env->CallVoidMethod(nodeObject,e_ctx.setWorldPositionMID,javaPosition);

    }

}

void JniHelper::setNodeWorldRotation(void *node, btQuaternion &rotation) {
    jclass nodeClass = e_ctx.nodeClz;
    jclass  vector3Class = e_ctx.vector3Clz;
    jobject nodeObject = reinterpret_cast<jobject >(node);
    if(!nodeObject){
        LOGE("Error retrieving node...");
        return;
    }
    jfloat angle = rotation.getAngle();
    angle*= 180.f/PI ; //convert to degrees
    btVector3 axis = rotation.getAxis();//.normalized();
    jobject javaRotAxis = e_ctx.env->NewObject(e_ctx.vector3Clz,e_ctx.vector3CID,
                                                axis.x(),axis.y(),axis.z());
    if(javaRotAxis){
        jobject javaQuaternion = e_ctx.env->NewObject(e_ctx.quaternionClz,e_ctx.quaternionCID,
                javaRotAxis,angle);
        if(javaQuaternion){
            e_ctx.env->CallVoidMethod(nodeObject,e_ctx.setWorldRotationMID,javaQuaternion);
        }
    }
}

void JniHelper::removeNativeNode(void *node) {
    if(node){
        jobject nativeNode = reinterpret_cast<jobject >(node);
        if(nativeNode)
        e_ctx.env->DeleteGlobalRef(nativeNode);
    }
}

float JniHelper::getFloatAttribute(jfieldID fid, jobject obj) {
    return e_ctx.env->GetFloatField(obj,fid);
}

Vector3& JniHelper::convertToNativeVector(jobject javaVector) {
    float x = getFloatAttribute(e_ctx.vector3XfieldId,javaVector);
    float y = getFloatAttribute(e_ctx.vector3YfieldId,javaVector);
    float z = getFloatAttribute(e_ctx.vector3ZfieldId,javaVector);
    Vector3 ret = Vector3(x,y,z);
    return ret;

}

