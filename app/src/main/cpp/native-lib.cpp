////////////////////////////////////////////////
// Created by Mahmoud Galal on 23/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////
#include "BaseHeader.h"

#include "PhysicsManager.h"


EnvironmentContext e_ctx;
static PhysicsManager* physicsManager = nullptr;


extern "C" JNIEXPORT void JNICALL
        Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_init(
                JNIEnv* env,
                jobject /* this */){
    if(! physicsManager)
        physicsManager = new PhysicsManager();
    physicsManager->initializePhysics();
}

extern "C" JNIEXPORT void JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_updatePhysicsObjects(
        JNIEnv* env,
        jobject /* this */){
    if(physicsManager)
        physicsManager->updatePhysicsObjects();
}
extern "C" JNIEXPORT void JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_stepPhysicsWorld(
        JNIEnv* env,
        jobject /* this */,
        jfloat step){
    if(physicsManager)
        physicsManager->stepPhysicsWorld(step);
}

extern "C" JNIEXPORT void JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_destroy(
        JNIEnv* env,
        jobject /* this */) {
    if (physicsManager) {
        physicsManager->deInitializePhysics();
        delete physicsManager;
        physicsManager = nullptr;
    }
}
extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_getNumberOfPhysicsBodies(
        JNIEnv* env,
        jobject /* this */){
    return  physicsManager?physicsManager->
            getNumberOfPhysicsBodies():INT64_MIN ;
}
extern "C" JNIEXPORT void JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_removePhysicsBody(
        JNIEnv* env,
        jobject /* this */,
        jlong id){
      if(physicsManager)
          physicsManager->removePhysicsBody(id);
}
//Vector3 size,Vector3 position,Node attachedNode
extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createGround(
        JNIEnv* env,
        jobject /* this */,
        jobject  size,jobject position,jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 sizeV = jniHelper.convertToNativeVector(size);
        Vector3 positionV = jniHelper.convertToNativeVector(position);
        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return physicsManager->createGround(sizeV,positionV,(void*)attachedNodeG);
    }
    return INT64_MIN ;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createPhysicsBox(
        JNIEnv* env,
        jobject /* this */,
        jobject  size,jobject initialPosition ,jfloat mass,jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 sizeV = jniHelper.convertToNativeVector(size);
        Vector3 positionV = jniHelper.convertToNativeVector(initialPosition);

        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return physicsManager->createPhysicsBox(sizeV,positionV,mass,(void*)attachedNodeG);
    }
    return INT64_MIN ;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createPhysicsCylinder(
        JNIEnv* env,
        jobject /* this */,
        jobject  size,
        jobject initialPosition ,
        jfloat mass,
        jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 sizeV = jniHelper.convertToNativeVector(size);
        Vector3 positionV = jniHelper.convertToNativeVector(initialPosition);

        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return physicsManager->createPhysicsCylinder(sizeV,positionV,mass,(void*)attachedNodeG);
    }
    return INT64_MIN;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createPhysicsSphere(
        JNIEnv* env,
        jobject /* this */,
        jfloat  radius,
        jobject initialPosition ,
        jfloat mass,
        jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 positionV = jniHelper.convertToNativeVector(initialPosition);
        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return physicsManager->createPhysicsSphere(radius,positionV,mass,(void*)attachedNodeG);
    }
    return INT64_MIN ;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createPhysicsBoxFromEye(
        JNIEnv* env,
        jobject /* this */,
        jobject  size,jobject initialPosition ,jobject lookat ,
        jfloat mass,
        jfloat forceFactor,
        jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 sizeV = jniHelper.convertToNativeVector(size);
        Vector3 positionV = jniHelper.convertToNativeVector(initialPosition);
        Vector3 lookAtV = jniHelper.convertToNativeVector(lookat);

        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return  physicsManager->createPhysicsBoxFromEye(sizeV,positionV,lookAtV,
                                                mass,forceFactor,
                                                (void*)attachedNodeG);
    }
    return INT64_MIN ;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createPhysicsCylinderFromEye(
        JNIEnv* env,
        jobject /* this */,
        jobject  size,jobject initialPosition ,jobject lookat ,
        jfloat mass,
        jfloat forceFactor,
        jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 sizeV = jniHelper.convertToNativeVector(size);
        Vector3 positionV = jniHelper.convertToNativeVector(initialPosition);
        Vector3 lookAtV = jniHelper.convertToNativeVector(lookat);

        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return physicsManager->createPhysicsCylinderFromEye(sizeV,positionV,lookAtV,
                                                mass,forceFactor,
                                                (void*)attachedNodeG);
    }
    return INT64_MIN ;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_createPhysicsSphereFromEye(
        JNIEnv* env,
        jobject /* this */,
        jfloat  radius,
        jobject initialPosition ,jobject lookat ,
        jfloat mass,
        jfloat forceFactor,
        jobject attachedNode) {
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 positionV = jniHelper.convertToNativeVector(initialPosition);
        Vector3 lookAtV = jniHelper.convertToNativeVector(lookat);

        jobject  attachedNodeG = e_ctx.env->NewGlobalRef(attachedNode);
        return physicsManager->createPhysicsSphereFromEye(radius,positionV,lookAtV,
                                                mass,forceFactor,
                                                (void*)attachedNodeG);
    }
    return INT64_MIN ;
}

extern "C" JNIEXPORT void JNICALL
Java_com_mahmoudgalal_sceneformbulletphysics_PhysicsManager_applyForce(
        JNIEnv* env,
        jobject /* this */,
        jlong  body,
        jobject force ,
        jobject relPos ){
    if (physicsManager) {
        JniHelper jniHelper;
        Vector3 forceV = jniHelper.convertToNativeVector(force);
        Vector3 relPosV = jniHelper.convertToNativeVector(relPos);
        physicsManager->applyForce(body,forceV,relPosV);
    }
}

    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
        JNIEnv *env;
        memset(&e_ctx, 0, sizeof(e_ctx));
        e_ctx.javaVM = vm;

        if (vm->GetEnv( (void**)&env, JNI_VERSION_1_6) != JNI_OK) {
            return JNI_ERR; // JNI version not supported.
        }
        ///////////////////////////////////////////////////////////////////
        // Capture necessary jni fields in a global structure
        /////////////////////////////////////////////////////////////////////
        e_ctx.env = env;

        jclass  clz = (env)->FindClass("com/google/ar/sceneform/Node");
         e_ctx.nodeClz =  (jclass) env->NewGlobalRef(clz);
         e_ctx.setWorldPositionMID = env->GetMethodID(e_ctx.nodeClz,
                                                    "setWorldPosition",
                                                    "(Lcom/google/ar/sceneform/math/Vector3;)V");
        e_ctx.setWorldRotationMID = env->GetMethodID(e_ctx.nodeClz,
                                                    "setWorldRotation",
                                                    "(Lcom/google/ar/sceneform/math/Quaternion;)V");

        jclass  vclz = env->FindClass("com/google/ar/sceneform/math/Vector3");
        e_ctx.vector3Clz =  (jclass)env->NewGlobalRef(vclz);

        jclass  qclz = env->FindClass("com/google/ar/sceneform/math/Quaternion");
        e_ctx.quaternionClz =  (jclass)env->NewGlobalRef(qclz);

        e_ctx.quaternionCID = env->GetMethodID(e_ctx.quaternionClz,
                                               "<init>",
                                               "(Lcom/google/ar/sceneform/math/Vector3;F)V");
        e_ctx.vector3CID = env->GetMethodID(e_ctx.vector3Clz,
                                               "<init>",
                                               "(FFF)V");

        e_ctx.vector3XfieldId = env->GetFieldID(e_ctx.vector3Clz,"x","F");
        e_ctx.vector3YfieldId = env->GetFieldID(e_ctx.vector3Clz,"y","F");
        e_ctx.vector3ZfieldId = env->GetFieldID(e_ctx.vector3Clz,"z","F");

        return  JNI_VERSION_1_6;
    }



