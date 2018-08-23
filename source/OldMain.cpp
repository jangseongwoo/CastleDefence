#define CLIENT_DESCRIPTION "InformationOverlay"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameManager.h"
#include "PlayState.h"

using namespace Ogre;

class InputController : public FrameListener, 
  public OIS::KeyListener, 
  public OIS::MouseListener
{

public:
  InputController(Root* root, OIS::Keyboard *keyboard, OIS::Mouse *mouse) : mRoot(root), mKeyboard(keyboard), mMouse(mouse)
  {
    mSceneMgr = root->getSceneManager("main");

    mAnimationState = mSceneMgr->getEntity("Professor")->getAnimationState("Run");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

    mCameraYaw = mSceneMgr->getSceneNode("CameraYaw");
    mCameraPitch = mSceneMgr->getSceneNode("CameraPitch");
    mCameraHolder = mSceneMgr->getSceneNode("CameraHolder");

    mPanel = static_cast<Ogre::OverlayContainer*>(OverlayManager::getSingletonPtr()->getOverlayElement("container1"));
    mLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/KPU_LOGO");
    mPanel2 = static_cast<Ogre::OverlayContainer*>(OverlayManager::getSingletonPtr()->getOverlayElement("container2"));

    mContinue = true;

    keyboard->setEventCallback(this);
    mouse->setEventCallback(this);
  }


  bool frameStarted(const FrameEvent &evt)
  {
    mKeyboard->capture();
    mMouse->capture();
    mAnimationState->addTime(evt.timeSinceLastFrame);

    static float panelX = -0.3f;
    mPanel->setPosition(panelX, 0.5f);
    panelX = panelX > 1.0f ? -0.3f : panelX + 0.1f * evt.timeSinceLastFrame;

    static float scale = 0.0f;
    mLogoOverlay->setScale(abs(cos(scale)), abs(cos(scale)));
    scale += 0.01f;

    return true;
  }

bool frameEnded(const FrameEvent &evt)
{
  static Ogre::DisplayString currFps = L"���� FPS: "; 
  static Ogre::DisplayString avgFps = L"��� FPS: ";
  static Ogre::DisplayString bestFps = L"�ְ� FPS: ";
  static Ogre::DisplayString worstFps = L"���� FPS: ";

  OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("AverageFps");
  OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("CurrFps");
  OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("BestFps");
  OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("WorstFps");

  const RenderTarget::FrameStats& stats = mRoot->getAutoCreatedWindow()->getStatistics();
  
  guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
  guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
  guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS));
  guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS));

  return mContinue;
}

  // Key Linstener Interface Implementation

  bool keyPressed( const OIS::KeyEvent &evt )
  {
    // Fill Here -----------------------------------------------
    switch(evt.key) 
    {
    case OIS::KC_A: break;
    }
    // ---------------------------------------------------------

    return true;

  }

  bool keyReleased( const OIS::KeyEvent &evt )
  {

    switch(evt.key) 
    {
    case OIS::KC_ESCAPE: mContinue = false; break;
    }

    return true;
  }


  // Mouse Listener Interface Implementation

  bool mouseMoved( const OIS::MouseEvent &evt )
  {
    mCameraYaw->yaw(Degree(-evt.state.X.rel));
    mCameraPitch->pitch(Degree(-evt.state.Y.rel));

    mCameraHolder->translate(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.1f));

    return true;
  }

  bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
  {
    return true;
  }

  bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
  {
    return true;
  }


private:
  bool mContinue;
  Ogre::Root* mRoot;
  Ogre::SceneManager* mSceneMgr;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;

  Ogre::Light *mLightP, *mLightD, *mLightS;


  Ogre::AnimationState* mWalkState;
  Ogre::AnimationState* mIdleState;
  Ogre::AnimationState* mAnimationState;

  SceneNode* mCharacterRoot;
  SceneNode* mCharacterYaw;

  SceneNode* mCameraHolder;
  SceneNode* mCameraYaw;
  SceneNode* mCameraPitch;

  Ogre::Vector3 mCharacterDirection;

  bool mRotating;  
  Quaternion mSrcQuat, mDestQuat;  
  float mRotatingTime;

  Ogre::OverlayContainer*  mPanel;
  Ogre::OverlayContainer*  mPanel2; 
  Ogre::Overlay*           mLogoOverlay;
};







class LectureApp {





public:

  LectureApp() {}

  ~LectureApp() {}

  void go(void)
  {
    // OGRE�� ���� ��Ʈ ������Ʈ ����
#if !defined(_DEBUG)
    mRoot = new Root("plugins.cfg", "ogre.cfg", "ogre.log");
#else
    mRoot = new Root("plugins_d.cfg", "ogre.cfg", "ogre.log");
#endif


    // �ʱ� ������ ���ǱԷ��̼� ���� - ogre.cfg �̿�
    if (!mRoot->restoreConfig()) {
      if (!mRoot->showConfigDialog()) return;
    }

    mWindow = mRoot->initialise(true, CLIENT_DESCRIPTION " : Copyleft by Dae-Hyun Lee 2010");

    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");

    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    mCamera = mSceneMgr->createCamera("main");

    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.0f,0.0f,0.0f));
    mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));


    ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
    ResourceGroupManager::getSingleton().addResourceLocation("./", "FileSystem");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


    _drawGridPlane();

    _setLights();

    _drawGroundPlane();

    _setOverlay();



    SceneNode* professorRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("ProfessorRoot");
    SceneNode* professorYaw = professorRoot->createChildSceneNode("ProfessorYaw");


    SceneNode* cameraYaw = professorRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
    SceneNode* cameraPitch = cameraYaw->createChildSceneNode("CameraPitch");
    SceneNode* cameraHolder = cameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));


    Entity* entity = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
    professorYaw->attachObject(entity);
    entity->setCastShadows(true);

    cameraHolder->attachObject(mCamera);
    mCamera->lookAt(cameraYaw->getPosition());



    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>( mInputManager->createInputObject(OIS::OISMouse, true));

    InputController* inputController = new InputController(mRoot, mKeyboard, mMouse);
    mRoot->addFrameListener(inputController);

    mRoot->startRendering();

    mInputManager->destroyInputObject(mKeyboard);
    mInputManager->destroyInputObject(mMouse);
    OIS::InputManager::destroyInputSystem(mInputManager);

    delete inputController;

    delete mRoot;
  }

private:


  void _setOverlay(void)
  {
    mOverlayMgr = OverlayManager::getSingletonPtr();
    mTextOverlay = mOverlayMgr->create("TextOverlay");

    mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
    mPanel->setDimensions(1, 1);
    mPanel->setPosition(-0.3f, 0.5f);

    OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID");
    textBox->setMetricsMode(Ogre::GMM_PIXELS);
    textBox->setPosition(10, 10);
    textBox->setWidth(100);
    textBox->setHeight(20);
    textBox->setParameter("font_name", "Font/NanumBold18");
    textBox->setParameter("char_height", "40");
    textBox->setColour(Ogre::ColourValue::White);
    textBox->setCaption(L"�ѱ����������б� �̴��� ����");
    mPanel->addChild(textBox);

    mTextOverlay->add2D(mPanel);
    mTextOverlay->show();

    mLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/KPU_LOGO");
    mLogoOverlay->show();

mLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
mLogoOverlay->show(); 
  }

  void _setLights(void)
  {
    mSceneMgr->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

    mLightD = mSceneMgr->createLight("LightD");
    mLightD->setType(Light::LT_DIRECTIONAL);
    mLightD->setDirection( Vector3( 1, -2.0f, -1 ) );
    mLightD->setVisible(true);
  }

  void _drawGroundPlane(void)
  {
    Plane plane( Vector3::UNIT_Y, 0 );
    MeshManager::getSingleton().createPlane(
      "Ground", 
      ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
      plane,
      500,500,
      1,1,
      true,1,5,5,
      Vector3::NEGATIVE_UNIT_Z
      );

    Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground" );
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setMaterialName("KPU_LOGO");
    groundEntity->setCastShadows(false);
  }

  void _drawGridPlane(void)
  {
    // ��ǥ�� ǥ��
    Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
    mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode",Ogre::Vector3(0,0,0))->attachObject(mAxesEntity);
    mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

    Ogre::ManualObject* gridPlane =  mSceneMgr->createManualObject("GridPlane"); 
    Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode"); 

    Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial","General"); 
    gridPlaneMaterial->setReceiveShadows(false); 
    gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,0); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,1); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,1); 

    gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
    for(int i=0; i<21; i++)
    {
      gridPlane->position(-500.0f, 0.0f, 500.0f-i*50);
      gridPlane->position(500.0f, 0.0f, 500.0f-i*50);

      gridPlane->position(-500.f+i*50, 0.f, 500.0f);
      gridPlane->position(-500.f+i*50, 0.f, -500.f);
    }

    gridPlane->end(); 

    gridPlaneNode->attachObject(gridPlane);
  }


  Ogre::Root* mRoot;
  Ogre::RenderWindow* mWindow;
  Ogre::SceneManager* mSceneMgr;
  Ogre::Camera* mCamera;
  Ogre::Viewport* mViewport;

  Ogre::Light *mLightP, *mLightD, *mLightS;

  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;
  OIS::InputManager *mInputManager;

  Ogre::OverlayManager*    mOverlayMgr;
  Ogre::Overlay*           mTextOverlay;
  Ogre::Overlay*           mLogoOverlay;
  Ogre::Overlay*           mDebugOverlay;
  Ogre::OverlayContainer*  mPanel;
};


#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
    // Create GameManager object
    GameManager game;

    try
    {
      // initialize the game and switch to the first state
      game.init();
      game.changeState(PlayState::getInstance());
      game.go();
    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBoxA( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL );
#else
      std::cerr << "An exception has occured: " <<
        e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
  }

#ifdef __cplusplus
}
#endif