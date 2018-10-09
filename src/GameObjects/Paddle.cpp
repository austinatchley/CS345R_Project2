#include <GameObjects/Paddle.h>

namespace Game {
Paddle::Paddle(Ogre::SceneManager *scnMgr, ECS::EventManager *eventManager,
               btDiscreteDynamicsWorld *world,
               const Ogre::String &material = "Examples/SphereMappedRustySteel",
               float scale = 1.f,
               const btTransform &trans = btTransform::getIdentity())
    : GameObject(scnMgr, eventManager, world, Ogre::SceneManager::PT_CUBE,
                 material, scale, trans) {
    mShape = new btBoxShape(btVector3(scale, scale, scale));

    mMass = 0.f;
    mInertia.setZero();

    mKinematic = true;
}

void Paddle::handleCollision() {
    // if collide with ball, bounce it
}
} // namespace Game