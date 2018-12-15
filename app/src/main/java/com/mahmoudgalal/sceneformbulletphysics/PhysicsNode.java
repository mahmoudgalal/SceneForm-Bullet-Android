////////////////////////////////////////////////
// Created by Mahmoud Galal on 25/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////
package com.mahmoudgalal.sceneformbulletphysics;

import com.google.ar.sceneform.Node;

public class PhysicsNode extends Node {

    public long getPhysicsObjectId() {
        return physicsObjectId;
    }

    public void setPhysicsObjectId(long physicsObjectId) {
        this.physicsObjectId = physicsObjectId;
    }

    public boolean isStatic() {
        return mass == 0.0f;
    }

    public float getMass() {
        return mass;
    }

    public void setMass(float mass) {
        this.mass = mass;
    }
    private float mass = 0f;
    private long physicsObjectId = Long.MIN_VALUE ;

}
