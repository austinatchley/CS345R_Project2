#pragma once

#include "State.h"

#include <GameObjects/GameObject.h>

#include <ECS/Component.h>
#include <ECS/ECSManager.h>
#include <ECS/Entity.h>
#include <ECS/EventManager.h>
#include <ECS/System.h>

#include <Util/Events/EventSubscribers.h>
#include <Util/Events/Events.h>

#include <SoundManager.h>

#include <GameObjects/Camera.h>
#include <GameObjects/Ball.h>
#include <GameObjects/Ground.h>
#include <GameObjects/Paddle.h>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreRTShaderSystem.h>
#include <OgreTrays.h>

#include "btBulletDynamicsCommon.h"

//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>

#define NUM_BALLS 10
#define BALL_TIMER 2.f
#define BALL_RING_RADIUS 40.f

#define BALL_RADIUS 5.f
#define PADDLE_SCALE 5.f

#define LIGHT_INTENSITY 1.0
#define AMBIENT_LIGHT                                                          \
    Ogre::ColourValue(LIGHT_INTENSITY, LIGHT_INTENSITY, LIGHT_INTENSITY)

using namespace Ogre;
using namespace OgreBites;

namespace Game {
// The game state where you actually play the game
// This should handle all game-specific logic
class GameState : public State {
  public:
    GameState(ECS::EventManager *eventManager, Root *root,
              Ogre::RenderWindow *renderWindow,
              OgreBites::TrayManager *trayMgr);
    virtual ~GameState();

    void setup() override;

    void update(const Ogre::FrameEvent &evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;
    bool mouseMoved(const OgreBites::MouseMotionEvent &evt) override;
    bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override;
    void buttonHit(OgreBites::Button *button) override;

    std::size_t addObject(GameObject *obj);

  private:
    Root *mRoot;
    SceneManager *mScnMgr;
    RTShader::ShaderGenerator *mShadergen;
    Ogre::RenderWindow *mRenderWindow;

    Ogre::SceneNode *mCamNode;
    Ogre::SceneNode *mCamRootNode;
    Game::Camera *mCamera;
    Ogre::Viewport *mViewport;

    float ballTimer;

    Paddle *mPaddle;
    Ground *mGround;

    btTransform mPaddleTrans;
    btTransform mGroundTrans;

    std::vector<GameObject *> mObjects;

    // Bullet
    btDefaultCollisionConfiguration *mCollisionConfig;
    btCollisionDispatcher *mDispatcher;
    btBroadphaseInterface *mOverlappingPairCache;
    btSequentialImpulseConstraintSolver *mSolver;
    btDiscreteDynamicsWorld *mDynamicsWorld;

    // ECS
    ECS::EventManager *mEventManager;

    // GUI
    OgreBites::TrayManager *mTrayMgr;
    int score;
};
}
