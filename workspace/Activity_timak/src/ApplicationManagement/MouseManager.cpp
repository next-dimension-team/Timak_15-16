/*
 * MouseManager.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "MouseManager.h"

#include "MyGUI.h"
#include "GuiManager.h"
#include "ApplicationStateManager.h"
#include <SdkCameraMan.h>


MouseManager* MouseManager::singletonObject = 0;


MouseManager::MouseManager() : MouseListener() {}

MouseManager::~MouseManager() {}

MouseManager* MouseManager::getInstance()
{
	if (MouseManager::singletonObject == 0) {
		singletonObject = new MouseManager();
	}

	return singletonObject;
}

bool MouseManager::mouseMoved( const OIS::MouseEvent &arg )
{
	// TODO: Use only ONE mouse cursor
	MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);

	if (GuiManager::getInstance()->getTrayManager()->injectMouseMove(arg)) return true;

	if (!GuiManager::getInstance()->isCursorVisible()) {
		GuiManager::getInstance()->getCameraManager()->injectMouseMove(arg);
	}

	return true;
}

bool MouseManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	ApplicationStateManager::getInstance()->processClickedMouse(arg, id);

    if (GuiManager::getInstance()->getTrayManager()->injectMouseDown(arg, id)) return true;

    GuiManager::getInstance()->getCameraManager()->injectMouseDown(arg, id);
    return true;
}

bool MouseManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));

    if (GuiManager::getInstance()->getTrayManager()->injectMouseUp(arg, id)) return true;

    GuiManager::getInstance()->getCameraManager()->injectMouseUp(arg, id);
    return true;
}

