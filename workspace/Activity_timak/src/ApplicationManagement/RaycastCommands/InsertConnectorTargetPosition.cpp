/*
 * InsertConnectorTargetPosition.cpp
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#include "InsertConnectorTargetPosition.h"

#include <MyGUI_PointerManager.h>
#include <MyGUI_Singleton.h>
#include <MyGUI_Window.h>
#include <OgreMovableObject.h>
#include <string>

#include "../../Core/Layer.h"
#include "../../Gui/ConnectorWindow.h"
#include "../ApplicationStateManager.h"
#include "../DiagramContexts/ClassDiagramContext.h"
#include "../DrawManager.h"
#include "../GuiManager.h"
#include "../InteractionManager.h"


InsertConnectorTargetPosition::InsertConnectorTargetPosition()
{
	cla = NULL;
}

InsertConnectorTargetPosition::~InsertConnectorTargetPosition() {}

bool InsertConnectorTargetPosition::conditionsAccepted() {
	return (InteractionManager::getInstance()->getActiveLayer() != 0) ? true : false;
}

bool InsertConnectorTargetPosition::check() {
	Ogre::MovableObject* touchedObject = InteractionManager::getInstance()->getActualMovable();
	if (touchedObject == 0) {
		return false;
	}

	std::string touchedObjectNamePart = touchedObject->getName().substr(0, 6);
	if (touchedObjectNamePart.compare("class_") == 0) {
		return true;
	}

	return false;
}

void InsertConnectorTargetPosition::action() {
	Layer* activeLayer = InteractionManager::getInstance()->getActiveLayer();
	this->cla = activeLayer->findClass(InteractionManager::getInstance()->getActualMovable()->getName());

	if (this->cla != 0) {
		ApplicationStateManager::getInstance()->setNextState();
		GuiManager::getInstance()->hideOldCursor(); // temporary - hides only old cursor, but new appears
		ClassDiagramContext* ctx = static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext());
		ctx->getWindowConnector()->setTargetData(cla);
		ctx->getWindowConnector()->fillDefaultText();
		//ctx->getWindowConnector()->getWidget()->setVisible(true);
		MyGUI::PointerManager::getInstance().setVisible(true);
		DrawManager::getInstance()->showLayers();
	}
}

bool InsertConnectorTargetPosition::stop() {
	return (this->cla != 0) ? true : false;
}

void InsertConnectorTargetPosition::postProcessAction() {}




