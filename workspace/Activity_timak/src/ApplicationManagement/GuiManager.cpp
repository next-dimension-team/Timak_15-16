/*
 * GuiManager.cpp
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#include "GuiManager.h"
#include "MyGUI_Gui.h"
#include "MyGUI_OgrePlatform.h"
#include "MyGUI_Window.h"
#include "ApplicationStateManager.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include "../Core/Element.h"

GuiManager* GuiManager::singletonObject = 0;

GuiManager::GuiManager() {}

GuiManager* GuiManager::getInstance()
{
	if (GuiManager::singletonObject == 0) {
		singletonObject = new GuiManager();
	}

	return singletonObject;
}

void GuiManager::createGui(OgreBites::SdkTrayManager* mTrayMgr, Ogre::Camera* mCamera, OgreBites::SdkCameraMan* mCameraMan)
{
	this->mTrayMgr = mTrayMgr;
	this->mCamera = mCamera;
	this->mCameraMan = mCameraMan;

    mCursorIsVisible = false;
}

void GuiManager::initMyGui(Ogre::RenderWindow* mWindow, Ogre::SceneManager* mSceneMgr)
{
	this->mPlatform = new MyGUI::OgrePlatform();
	this->mPlatform->initialise(mWindow, mSceneMgr, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*

	this->mGUI = new MyGUI::Gui();
	this->mGUI->initialise("MyGUI_Core.xml");
}

void GuiManager::hideCursor()
{
	mCameraMan->setStyle(OgreBites::CS_FREELOOK);
	mCursorIsVisible = false;
	mTrayMgr->hideCursor();
}

void GuiManager::hideOldCursor()
{
	mCursorIsVisible = false;
	mTrayMgr->hideCursor();
}

void GuiManager::showCursor()
{
	mCameraMan->setStyle(OgreBites::CS_MANUAL);
	mCursorIsVisible = true;
	mTrayMgr->showCursor("");
	mTrayMgr->windowUpdate(); // ??
}

bool GuiManager::isCursorVisible()
{
	return mCursorIsVisible;
}

void GuiManager::closeGui()
{
	mGUI->shutdown();
	delete mGUI;
	mGUI = 0;
	mPlatform->shutdown();
	delete mPlatform;
	mPlatform = 0;

	ApplicationStateManager::getInstance()->setReadyToShutdown(true);
}

OgreBites::SdkTrayManager* GuiManager::getTrayManager()
{
	return this->mTrayMgr;
}

OgreBites::SdkCameraMan* GuiManager::getCameraManager()
{
	return this->mCameraMan;
}

MyGUI::Gui* GuiManager::getGui()
{
	return this->mGUI;
}

void GuiManager::setPosition(Ogre::Vector3 position) {
	this->position = position;
}

Ogre::Vector3 GuiManager::getPosition() {
	return position;
}

void GuiManager::setElement(Element* element) {
	this->element = element;
}

Element* GuiManager::getElement() {
	return element;
}
