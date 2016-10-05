/*
 * KeyboardManager.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "KeyboardManager.h"
#include "MyGUI.h"
#include "GuiManager.h"
#include "ApplicationStateManager.h"

#include <OgreLogManager.h>
#include <sstream>


KeyboardManager* KeyboardManager::singletonObject = 0;


KeyboardManager::KeyboardManager() : KeyListener() {}

KeyboardManager::~KeyboardManager() {}

KeyboardManager* KeyboardManager::getInstance()
{
	if (KeyboardManager::singletonObject == 0) {
		singletonObject = new KeyboardManager();
	}

	return singletonObject;
}

bool KeyboardManager::keyPressed( const OIS::KeyEvent &arg )
{
    if (GuiManager::getInstance()->getTrayManager()->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
    ApplicationStateManager::getInstance()->processPressedButton(arg.key);
    GuiManager::getInstance()->getCameraManager()->injectKeyDown(arg);

    return true;
}

bool KeyboardManager::keyReleased( const OIS::KeyEvent &arg )
{
	MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
	GuiManager::getInstance()->getCameraManager()->injectKeyUp(arg);
    return true;
}

