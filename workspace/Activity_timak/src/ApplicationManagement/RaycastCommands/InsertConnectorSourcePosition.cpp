/*
 * InsertConnectorSourcePosition.cpp
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#include "InsertConnectorSourcePosition.h"

#include <OgreMovableObject.h>
#include <string>

#include "../../Core/Layer.h"
#include "../../Gui/ConnectorWindow.h"
#include "../ApplicationStateManager.h"
#include "../DiagramContexts/ClassDiagramContext.h"
#include "../DrawManager.h"
#include "../InteractionManager.h"


InsertConnectorSourcePosition::InsertConnectorSourcePosition() {}

InsertConnectorSourcePosition::~InsertConnectorSourcePosition() {}

bool InsertConnectorSourcePosition::conditionsAccepted() {
	return (InteractionManager::getInstance()->getActiveLayer() != 0) ? true : false;
}

bool InsertConnectorSourcePosition::check() {
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

void InsertConnectorSourcePosition::action() {
	Layer* activeLayer = InteractionManager::getInstance()->getActiveLayer();

	DrawManager::getInstance()->hideLayersExcept(activeLayer);
	DrawManager::getInstance()->setBookmarksVisibility(false);

	this->cla = activeLayer->findClass(InteractionManager::getInstance()->getActualMovable()->getName());

	if (this->cla != 0) {
		ApplicationStateManager::getInstance()->setNextState();
		static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->getWindowConnector()->setSourceData(cla);
		DrawManager::getInstance()->showLayers();
		DrawManager::getInstance()->setBookmarksVisibility(true);
	}
}

bool InsertConnectorSourcePosition::stop() {
	return (this->cla != 0) ? true : false;
}

void InsertConnectorSourcePosition::postProcessAction() {}


