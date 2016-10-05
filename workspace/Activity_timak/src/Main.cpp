// team4 include *********

//#include "./src/Core/Mvc/Gui.h"

// **********************

#include "Main.h"

#include <OgreCamera.h>
#include <OgreColourValue.h>
#include <OgreCommon.h>
#include <OgreException.h>
#include <OgreLight.h>
#include <OgreLogManager.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgrePass.h>
#include <OgrePlatform.h>
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreTechnique.h>
#include <OgreVector3.h>
#include <OgreViewport.h>
#include <SdkCameraMan.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>
#include <string>

#include "ApplicationManagement/ApplicationStateManager.h"
#include "ApplicationManagement/DiagramContexts/SelectDiagramContext.h"
#include "ApplicationManagement/DrawManager.h"
#include "ApplicationManagement/InteractionManager.h"




//-------------------------------------------------------------------------------------
Ogre::SceneManager* Main::sMSceneMgr;

//-------------------------------------------------------------------------------------
Main::Main(void)
{}

//-------------------------------------------------------------------------------------
Main::~Main(void)
{}

//-------------------------------------------------------------------------------------
void Main::createScene(void)
{
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

    // Load material
    Ogre::MaterialPtr matptr = Ogre::MaterialManager::getSingleton().create("BaseColoured","General");
    matptr->load();
    matptr->getBestTechnique()->getPass(0)->setVertexColourTracking(Ogre::TVC_DIFFUSE);
    matptr->getBestTechnique()->getPass(0)->setLightingEnabled(false);

    //---------------------------------------------------------------------------------
    DrawManager* drawM = DrawManager::getInstance();
    drawM->init(mSceneMgr);

    InteractionManager* interactionM = InteractionManager::getInstance();
    interactionM->setCamera(mCamera);
    interactionM->setSceneManager(mSceneMgr);

    Ogre::LogManager::getSingleton().createLog("myLog.txt", true, true, false);

    // ---------- Application State Manager - init ----------
    ApplicationStateManager::getInstance()->setDiagramContext(new SelectDiagramContext());

    DrawManager::getInstance()->drawAll();

    DrawManager::getInstance()->setBookmarksVisibility(false);
    ////*************************************************************************************************************
}

//-------------------------------------------------------------------------------------
void Main::chooseSceneManager(void)
{
    OgreFramework::chooseSceneManager();
    Main::sMSceneMgr = mSceneMgr;
}
//-------------------------------------------------------------------------------------
void Main::createCamera(void)
{

    // create the camera
    mCamera = mSceneMgr->createCamera("MainCam");

    // set its position, direction
    mCamera->setPosition(Ogre::Vector3(0,200,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));

    // set the near clip distance
    mCamera->setNearClipDistance(5);
    //	mCamera->setFarClipDistance(3000);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

//-------------------------------------------------------------------------------------
void Main::createViewports(void)
{

    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(1,1,1));

    mWindow->setFullscreen(false, vp->getActualWidth(), vp->getActualHeight());

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

}

//-------------------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Main app;

        try
        {
            app.go();
        }
        catch( Ogre::Exception& e )
        {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
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


