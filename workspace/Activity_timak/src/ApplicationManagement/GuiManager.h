/*
 * GuiManager.h
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

namespace MyGUI {
	class Gui;
	class OgrePlatform;
	class RenderWindow;
	class SceneManager;
}


#include <OISKeyboard.h>	// prerequisity for SdkTrays!!
#include <OISMouse.h>		// prerequisity for SdkTrays!!
#include <SdkTrays.h>		// TODO: create adapter!!
#include <SdkCameraMan.h>
#include "../Core/Element.h"

class GuiManager
{
	public:
		static GuiManager* getInstance();

		void createGui(OgreBites::SdkTrayManager* mTrayMgr, Ogre::Camera* mCamera, OgreBites::SdkCameraMan* mCameraMan);
		void initMyGui(Ogre::RenderWindow* mWindow, Ogre::SceneManager* mSceneMgr);
		void hideCursor();
		void hideOldCursor();
		void showCursor();
		void setPosition(Ogre::Vector3 position);
		Ogre::Vector3 getPosition();
		void setElement(Element* element);
		Element* getElement();
		bool isCursorVisible();
		void closeGui();
		OgreBites::SdkTrayManager* getTrayManager();
		OgreBites::SdkCameraMan* getCameraManager();
		MyGUI::Gui* getGui();

	private:
		static GuiManager* singletonObject;


		GuiManager();
		~GuiManager();

		bool mCursorIsVisible;

		Ogre::Camera* mCamera;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mWindow;

		// MyGUI
		MyGUI::Gui* mGUI;
		MyGUI::OgrePlatform* mPlatform;

		 // OgreBites
		OgreBites::SdkTrayManager* mTrayMgr;
		OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller

		Ogre::Vector3 position;
		Element* element;
};

#endif /* GUIMANAGER_H_ */
