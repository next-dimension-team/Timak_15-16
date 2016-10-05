/*
 * OgreFramework.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

/*
This source file is part of the:
      http://www.ogre3d.org/tikiwiki/
      http://www.ogre3d.org/tikiwiki/tiki-index.php?page=BaseApplication-h&structure=Development
-----------------------------------------------------------------------------
Many parts of this class was modified to archieve some functionality.
*/

#ifndef OGREFRAMEWORK_H_
#define OGREFRAMEWORK_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkCameraMan.h>
#include <OgreFrameListener.h>
#include <SdkTrays.h>

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"
#include "../Gui/ClassWindow.h"
#include "../Gui/ConnectorWindow.h"
#include "../ApplicationManagement/ApplicationStateManager.h"


class OgreFramework : public Ogre::FrameListener, public Ogre::WindowEventListener, OgreBites::SdkTrayListener
{
public:
	OgreFramework(void);
    virtual ~OgreFramework(void);

    virtual void go(void);

protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0; // Override me!
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);


    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

    // OgreBites
	OgreBites::SdkTrayManager* mTrayMgr;
	OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
	OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel

    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    // Timer
    Ogre::Timer* mTimer;
};

#endif /* OGREFRAMEWORK_H_ */
