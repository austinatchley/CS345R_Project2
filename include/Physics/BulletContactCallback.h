#pragma once

#include <btBulletDynamicsCommon.h>

namespace Util {
    class GameObject;
}

namespace Physics {
struct CollisionContext
{
    bool hit;

    const btCollisionObject* body;
    const btCollisionObject* lastBody;
    
    Util::GameObject* obj;

    float dist;
    float velNormal;
    
    btVector3 point;
    btVector3 normal;
    btVector3 velocity;

    CollisionContext()
    {
        reset();
    }

    void reset()
    {
        hit = false;

        body = nullptr;

        obj = nullptr;

        dist = 0.f;
        velNormal = 0.f;

        point.setZero();
        normal.setZero();
        velocity.setZero();
    }
};

struct BulletContactCallback
    : public btCollisionWorld::ContactResultCallback
{
    BulletContactCallback(btRigidBody& tgtBody, CollisionContext& context)
        : btCollisionWorld::ContactResultCallback()
        , body(tgtBody)
        , ctxt(context)
    {}

    btRigidBody& body;
    CollisionContext& ctxt;

    virtual bool needsCollision(btBroadphaseProxy* proxy) const
    {
        if (!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
        {
            return false;
        }

        return body.checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
    }

    virtual btScalar addSingleResult(btManifoldPoint& cp,
            const btCollisionObject* colObj0, int partId0, int index0,
            const btCollisionObject* colObj1, int partId1, int index1)
    {
        ctxt.hit = true;
        ctxt.lastBody = ctxt.body;

        if (colObj0 == &body)
        {
            ctxt.point = cp.m_localPointA;
            ctxt.body = colObj1;
        }
        else
        {
            assert(colObj1 == &body && "Collision is invalid - body doesn't match either object");
            ctxt.point = cp.m_localPointB;
            ctxt.body = colObj0;
        }

        ctxt.obj = static_cast<Util::GameObject*>(ctxt.body->getUserPointer());
        ctxt.normal = cp.m_normalWorldOnB;
        ctxt.velocity = body.getLinearVelocity();
        ctxt.velNormal = ctxt.normal.dot(ctxt.velocity);

        return 0;
    }
};
}