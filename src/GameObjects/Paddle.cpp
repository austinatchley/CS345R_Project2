#include <GameObjects/Paddle.h>
#include <States/GameState.h>

#define THICKNESS 1.f / 6.f

namespace Game
{
Paddle::Paddle(Ogre::SceneManager* scnMgr,
               Ogre::SceneNode* parent,
               ECS::EventManager* eventManager,
               btDiscreteDynamicsWorld* world,
               const Ogre::String& material = "Examples/"
                                              "SphereMappedRustySteel",
               float scale = 1.f,
               const btTransform& trans = btTransform::getIdentity())
: GameObject(parent ? parent : scnMgr->getRootSceneNode(),
             eventManager,
             world,
             scnMgr->createEntity(Ogre::SceneManager::PT_CUBE),
             material,
             scale,
             trans)
{
    mNode->setScale(scale * THICKNESS / 100.f, scale / 100.f, scale / 100.f);
    mShape = new btBoxShape(btVector3(scale * THICKNESS + 40, scale + 22, scale + 22));

    mMass = 0.f;
    mInertia.setZero();

    mRestitution = 1.f;

    mKinematic = true;
}

void Paddle::handleCollision()
{
  mGameState->scoreinc();
}
} // namespace Game
