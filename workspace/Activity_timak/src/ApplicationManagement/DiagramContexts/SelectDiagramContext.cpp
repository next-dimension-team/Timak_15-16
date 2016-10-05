/*
 * SelectDiagramContext.cpp
 *
 *  Created on: 3.12.2013
 *      Author: Schade
 */

#include "SelectDiagramContext.h"
#include "../../Gui/SelectDiagramWindow.h"
#include "MyGUI_PointerManager.h"
#include "../GuiManager.h"


SelectDiagramContext::SelectDiagramContext() : DiagramContext() {}

SelectDiagramContext::~SelectDiagramContext() {}

void SelectDiagramContext::activateGui() {
	MyGUI::PointerManager::getInstance().setVisible(false);

	Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
	this->windowSelectDiagram = new SelectDiagramWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
	this->windowSelectDiagram->getWidget()->setVisible(true);

	GuiManager::getInstance()->showCursor();
}

void SelectDiagramContext::initContent() {}

SelectDiagramWindow* SelectDiagramContext::getWindowSelectDiagram()
{
	return this->windowSelectDiagram;
}

void SelectDiagramContext::closeSelectDiagramWindow()
{
	// TODO: destroy mygui widget
	this->windowSelectDiagram->getWidget()->setVisible(false);
	MyGUI::PointerManager::getInstance().setVisible(false);
}

