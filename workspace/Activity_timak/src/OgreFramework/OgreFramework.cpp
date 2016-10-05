/*
 * OgreFramework.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

/*
This source file is part of the:
      http://www.ogre3d.org/tikiwiki/
      http://www.ogre3d.org/tikiwiki/tiki-index.php?page=BaseApplication-h&structure=Development
-----------------------------------------------------------------------------
Many parts of this class was modified to archieve desired functionality.
*/

#include "OgreFramework.h"

#include <OgreColourValue.h>
#include <OgreIteratorWrapper.h>
#include <OgrePlatform.h>
#include <OgrePrerequisites.h>
#include <OgreQuaternion.h>
#include <OgreResourceGroupManager.h>
#include <OgreString.h>
#include <OgreStringConverter.h>
#include <OgreStringVector.h>
#include <OgreTextureManager.h>
#include <OgreVector3.h>
#include <OgreWindowEventUtilities.h>
#include <OISPrereqs.h>
#include <stddef.h>
#include <winbase.h>
#include <WIN32/OgreTimerImp.h>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../ApplicationManagement/AnimationManager.h"
#include "../ApplicationManagement/DiagramContexts/DiagramContext.h"
#include "../ApplicationManagement/DrawManager.h"
#include "../ApplicationManagement/GuiManager.h"
#include "../ApplicationManagement/KeyboardManager.h"
#include "../ApplicationManagement/MouseManager.h"


//-------------------------------------------------------------------------------------
OgreFramework::OgreFramework(void)
        : mRoot(0),
        mCamera(0),
        mSceneMgr(0),
        mWindow(0),
        mResourcesCfg(Ogre::StringUtil::BLANK),
        mPluginsCfg(Ogre::StringUtil::BLANK),
        mTrayMgr(0),
        mCameraMan(0),
        mDetailsPanel(0),
        mInputManager(0),
        mMouse(0),
        mKeyboard(0),
        mTimer(0)
{
}

//-------------------------------------------------------------------------------------
OgreFramework::~OgreFramework(void)
{
    if (mTrayMgr)
        delete mTrayMgr;
    if (mCameraMan)
        delete mCameraMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//-------------------------------------------------------------------------------------
bool OgreFramework::configure(void)
{
    if (mRoot->restoreConfig())
    {
        mWindow = mRoot->initialise(true, "3D UML Render Window");
        return true;
    }
    else if (mRoot->showConfigDialog())
    {
        // File ogre.cfg don't exist or is invalid
        mWindow = mRoot->initialise(true, "3D UML Render Window");
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void OgreFramework::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------
void OgreFramework::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("MainCamera");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,300));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
}
//-------------------------------------------------------------------------------------
void OgreFramework::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    // ---------- Keyboard Manager ----------
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    // ---------- Mouse Manager ----------
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(MouseManager::getInstance());
    mKeyboard->setEventCallback(KeyboardManager::getInstance());

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
    mTrayMgr->hideCursor();
    //	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);

    // Timer initialization
    mTimer = new Ogre::Timer();
    mTimer->reset();

    // ---------- GUI Manager ----------
    GuiManager::getInstance()->createGui(mTrayMgr, mCamera, mCameraMan);
    ApplicationStateManager::getInstance()->getDiagramContext()->activateGui();

    // create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void OgreFramework::destroyScene(void)
{}
//-------------------------------------------------------------------------------------
void OgreFramework::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void OgreFramework::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void OgreFramework::createResourceListener(void)
{
}
//-------------------------------------------------------------------------------------
void OgreFramework::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void OgreFramework::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else

    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

    int startTime = 0;
    double deltaTime = 1;
    int frameMs = 30; // one frame duration in ms
    while (!ApplicationStateManager::getInstance()->isReadyToShutdown())
    {

        startTime = mTimer->getMillisecondsCPU();

        if (deltaTime < frameMs)
            Sleep(frameMs - deltaTime); // windows only

        Ogre::WindowEventUtilities::messagePump();

        mMouse->capture();
        mKeyboard->capture();

        ApplicationStateManager::getInstance()->update(deltaTime / 1000);
        AnimationManager::getInstance()->updateAnimations(deltaTime / 1000); // TODO: block operations while animations are running
        //    		ApplicationStateManager::getInstance()->blockOperations(true/false);

        mRoot->renderOneFrame();

        deltaTime = mTimer->getMillisecondsCPU() - startTime; // http://www.youtube.com/watch?v=XL-lO9ITYvY
    }

    DrawManager::getInstance()->cleanUp();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool OgreFramework::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn)
        return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // ---------- GUI Manager - init ----------
    GuiManager::getInstance()->initMyGui(mWindow, mSceneMgr);

    // Create the scene
    createScene();

    createFrameListener();

    //mCamera->setPolygonMode(Ogre::PM_WIREFRAME);
    //mDetailsPanel->setParamValue(10, "Points");

    return true;
};
//-------------------------------------------------------------------------------------
bool OgreFramework::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(ApplicationStateManager::getInstance()->isReadyToShutdown())
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------

//Adjust mouse clipping area
void OgreFramework::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void OgreFramework::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

