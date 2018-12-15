////////////////////////////////////////////////
// Created by Mahmoud Galal on 23/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////

#ifndef SCENEFORMTEST_PHYSICSMANAGER_H
#define SCENEFORMTEST_PHYSICSMANAGER_H

#include "JniHelper.h"
#include "btBulletDynamicsCommon.h"



class PhysicsManager {

public:
    PhysicsManager(){

    }
    void initializePhysics();
    long createGround(Vector3& size,Vector3& position,void* attachedNode = nullptr);
    long createPhysicsBox(Vector3& size,Vector3& initialPosition,
                          float mass = 5,void* attachedNode = nullptr);
    long createPhysicsCylinder(Vector3& size,Vector3& initialPosition,
                          float mass = 5,void* attachedNode = nullptr);
    long createPhysicsSphere(float radius,Vector3& initialPosition,
                          float mass = 5,void* attachedNode = nullptr);
    long createPhysicsBoxFromEye(Vector3& size,Vector3& initialPosition,
                                 Vector3& lookAt,float mass = 5,
                                 float force =250,void* attachedNode = nullptr);
    long createPhysicsSphereFromEye(float radius,Vector3& initialPosition,
                                 Vector3& lookAt,float mass = 5,
                                 float force =250,void* attachedNode = nullptr);
    long createPhysicsCylinderFromEye(Vector3& size,Vector3& initialPosition,
                                    Vector3& lookAt,float mass = 5,
                                    float force =250,void* attachedNode = nullptr);
    long getNumberOfPhysicsBodies();
    void removePhysicsBody(long id);
    void applyForce(long id , Vector3& force,Vector3& relPos);
    void stepPhysicsWorld(float timestep);
    void updatePhysicsObjects();

    void deInitializePhysics();

private:

    JniHelper jniHelper;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btBroadphaseInterface* overlappingPairCache;
    btCollisionDispatcher* dispatcher;
    btDefaultCollisionConfiguration* collisionConfiguration;
    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;


    btBoxShape* createBoxShape(const btVector3& halfExtents)
    {
        btBoxShape* box = new btBoxShape(halfExtents);
        return box;
    }


    btRigidBody*	createRigidBody(btDiscreteDynamicsWorld*  dynamicsWorld,float mass,
                                    const btTransform& startTransform, btCollisionShape* shape,
                                    const btVector4& color = btVector4(1, 0, 0, 1),
                                    void* attachedNode = nullptr)
    {
        btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->calculateLocalInertia(mass, localInertia);

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

#define USE_MOTIONSTATE 1
#ifdef USE_MOTIONSTATE
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

        btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

        btRigidBody* body = new btRigidBody(cInfo);
        //body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

#else
        btRigidBody* body = new btRigidBody(mass, 0, shape, localInertia);
		body->setWorldTransform(startTransform);
#endif//

        body->setUserIndex(-1);
        body->setUserPointer(attachedNode);
        dynamicsWorld->addRigidBody(body);
        return body;
    }

};





#endif //SCENEFORMTEST_PHYSICSMANAGER_H
