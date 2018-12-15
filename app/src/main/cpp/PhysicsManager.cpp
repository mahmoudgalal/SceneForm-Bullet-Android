////////////////////////////////////////////////
// Created by Mahmoud Galal on 23/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////

#include "PhysicsManager.h"


void PhysicsManager::initializePhysics(){
    ///-----initialization_start-----

    ///collision configuration contains default setup for memory, collision setup.
    // Advanced users can create their own configuration.
    collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a
            // different dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    ///-----initialization_end-----
}
long PhysicsManager::createGround(Vector3 &size, Vector3 &position, void *attachedNode) {
    //the ground is a cube of side 100 at position y = -56.
    //the sphere will hit it at y = -6, with center at -5

        btCollisionShape* groundShape = new btBoxShape(btVector3(size.x/2.f, size.y/2.f, size.z/2.f));

        collisionShapes.push_back(groundShape);

        btTransform groundTransform;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(position.x
                ,position.y,position.z));

        btScalar mass(0.);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            groundShape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);
        body->setUserIndex(5);
        body->setUserPointer(attachedNode);
        body->setFriction(1);

        //add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);
    return reinterpret_cast<long>(body);
}
long PhysicsManager::createPhysicsBox(Vector3 &size, Vector3 &initialPosition, float mass,
                                      void *attachedNode) {
    //create a dynamic rigidbody

    btCollisionShape* colShape = createBoxShape(btVector3(size.x/2.f,size.y/2.f,size.z/2.f));
    //btCollisionShape* colShape = new btBoxShape(btScalar(1.));
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    startTransform.setOrigin(btVector3(initialPosition.x, initialPosition.y
            , initialPosition.z));
    btQuaternion quat(btVector3(0.4,.02,.1),67);
    startTransform.setRotation(quat);


    btRigidBody* body =  createRigidBody(dynamicsWorld,mass,startTransform,colShape);// new btRigidBody(rbInfo);
    body->setFriction(1);
    body->setUserIndex(10);

    //saving the visual node to the physics node
    body->setUserPointer(attachedNode);
    return reinterpret_cast<long>(body);
}

long PhysicsManager::createPhysicsCylinder(Vector3 &size, Vector3 &initialPosition, float mass,
                                      void *attachedNode) {
    //create a dynamic rigidbody

    btCollisionShape* colShape = new btCylinderShape(btVector3(size.x,size.y/2.f,size.z));
    //btCollisionShape* colShape = new btBoxShape(btScalar(1.));
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(initialPosition.x, initialPosition.y,
                                       initialPosition.z));
    btQuaternion quat(btVector3(0.4,.02,.1),67);
    startTransform.setRotation(quat);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserIndex(15);
   // body->setDamping(0.01,0.01);

    body->setUserPointer(attachedNode);
   // body->setFriction(1);
    dynamicsWorld->addRigidBody(body);
    return reinterpret_cast<long>(body);
}


long PhysicsManager::createPhysicsSphere(float radius, Vector3 &initialPosition, float mass,
                                         void *attachedNode) {
    //create a dynamic rigidbody

    btCollisionShape* colShape = new btSphereShape(radius);
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(initialPosition.x, initialPosition.y,
                                       initialPosition.z));
    btQuaternion quat(btVector3(0.4,.02,.1),67);
    startTransform.setRotation(quat);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserIndex(12);

    body->setUserPointer(attachedNode);

    dynamicsWorld->addRigidBody(body);
    return reinterpret_cast<long>(body);
}

long PhysicsManager::createPhysicsSphereFromEye(float radius, Vector3 &initialPosition,
                                                Vector3 &lookat, float mass, float forceFactor,
                                                void *attachedNode) {
    //create a dynamic rigidbody

    btCollisionShape* colShape = new btSphereShape(radius);
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(initialPosition.x, initialPosition.y,
                                       initialPosition.z));
    btQuaternion quat(btVector3(0.4,.02,.1),67);
    startTransform.setRotation(quat);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserIndex(10);
   // body->setDamping(0.01,0.01);

    body->setUserPointer(attachedNode);
    body->setFriction(0.3f);
    btVector3 force(lookat.x,lookat.y,lookat.z);

    dynamicsWorld->addRigidBody(body);
    body->applyImpulse(forceFactor * force,btVector3(0.f,0.f,0.f));
    return reinterpret_cast<long>(body);
}

long PhysicsManager::createPhysicsBoxFromEye(Vector3 &size, Vector3 &initialPosition,
                                             Vector3 &lookat, float mass, float forceFactor,
                                             void *attachedNode) {
    //create a dynamic rigidbody
    btCollisionShape* colShape = new btBoxShape(btVector3(size.x/2.f,size.y/2.f,size.z/2.f));
    //btCollisionShape* colShape = new btBoxShape(btScalar(1.));
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(initialPosition.x, initialPosition.y,
                                       initialPosition.z));
    btQuaternion quat(btVector3(0.4,.02,.1),67);
    startTransform.setRotation(quat);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserIndex(10);
    body->setDamping(0.01,0.01);

    body->setUserPointer(attachedNode);
    body->setFriction(1);
    btVector3 force(lookat.x,lookat.y,lookat.z);

    dynamicsWorld->addRigidBody(body);
    body->applyImpulse(forceFactor * force,btVector3(0.f,0.f,0.f));
    return reinterpret_cast<long>(body);
}

long PhysicsManager::createPhysicsCylinderFromEye(Vector3 &size, Vector3 &initialPosition,
                                                  Vector3 &lookat, float mass, float forceFactor,
                                                  void *attachedNode) {
    //create a dynamic rigidbody
    btCollisionShape* colShape = new btCylinderShape(btVector3(size.x,size.y/2.f,size.z));
    //btCollisionShape* colShape = new btBoxShape(btScalar(1.));
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(initialPosition.x, initialPosition.y,
                                       initialPosition.z));
    btQuaternion quat(btVector3(0.4,.02,.1),67);
    startTransform.setRotation(quat);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserIndex(10);
    //body->setDamping(0.01,0.01);

    body->setUserPointer(attachedNode);
    body->setFriction(0.2f);
    btVector3 force(lookat.x,lookat.y,lookat.z);

    dynamicsWorld->addRigidBody(body);
    body->applyImpulse(forceFactor * force,btVector3(0.f,0.f,0.f));
    return reinterpret_cast<long>(body);
}

void PhysicsManager::stepPhysicsWorld(float timestep) {
    if(dynamicsWorld)
        dynamicsWorld->stepSimulation(timestep, 10);
}

long PhysicsManager::getNumberOfPhysicsBodies() {
    return  dynamicsWorld?dynamicsWorld->getNumCollisionObjects():INT64_MIN;
}
/**
 * update your graphics here
 */
void PhysicsManager::updatePhysicsObjects(){
    int numOfObjects = dynamicsWorld->getNumCollisionObjects();
    for (int j = numOfObjects - 1; j >= 0; j--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        //LOGE("Updating1....");
        if (body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
          //  LOGE("Updating....");
            void* attachedNode = body->getUserPointer();
            if(attachedNode){//update cubes only
                btVector3 origin = trans.getOrigin();
                //update rotation
                btQuaternion rot = trans.getRotation();
                jniHelper.setNodeWorldPosition(attachedNode,origin);
                jniHelper.setNodeWorldRotation(attachedNode,rot);
            }
        }
        else
        {
            trans = obj->getWorldTransform();
        }
    }
}

void PhysicsManager::applyForce(long id, Vector3 &force_, Vector3 &relPos_) {
    if(id>0) {
        btRigidBody *body = reinterpret_cast<btRigidBody *>(id);
        if(body){
            btVector3 force (force_.x,force_.y,force_.z);
            btVector3 relPos (relPos_.x,relPos_.y,relPos_.z);
            body->setActivationState(ACTIVE_TAG);
            body->applyForce(force,relPos);
        }
    }
}


void PhysicsManager::removePhysicsBody(long id) {
    if(id>0){
        btRigidBody* body = reinterpret_cast<btRigidBody*>(id);
        if (body ){
            if(body->getMotionState())
                delete body->getMotionState();
            dynamicsWorld->removeCollisionObject(body);
            delete body;
        }

    }
}

void PhysicsManager::deInitializePhysics() {
    ///-----cleanup_start-----
    int i;
    for (i = dynamicsWorld->getNumConstraints() - 1; i >= 0; i--)
    {
        dynamicsWorld->removeConstraint(dynamicsWorld->getConstraint(i));
    }
    //remove the rigidbodies from the dynamics world and delete them
    for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            void* attachedNode = body->getUserPointer();
            if(attachedNode){
                jniHelper.removeNativeNode(attachedNode);
            }
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    //delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++)
    {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    //delete dynamics world
    delete dynamicsWorld;
    dynamicsWorld = nullptr;
    //delete solver
    delete solver;

    //delete broadphase
    delete overlappingPairCache;

    //delete dispatcher
    delete dispatcher;

    delete collisionConfiguration;

    //next line is optional: it will be cleared by the destructor when the array goes out of scope
    collisionShapes.clear();
}

