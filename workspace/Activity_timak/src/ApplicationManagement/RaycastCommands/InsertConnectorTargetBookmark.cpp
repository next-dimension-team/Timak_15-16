/*
 * InsertConnectorTargetBookmark.cpp
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#include "InsertConnectorTargetBookmark.h"

#include <OgreMovableObject.h>
#include <string>

#include "../../Core/LayerBookmark.h"
#include "../ApplicationStateManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../InteractionManager.h"


InsertConnectorTargetBookmark::InsertConnectorTargetBookmark() {}

InsertConnectorTargetBookmark::~InsertConnectorTargetBookmark() {}

bool InsertConnectorTargetBookmark::conditionsAccepted() {
	return true;
}

bool InsertConnectorTargetBookmark::check() {
	Ogre::MovableObject* touchedObject = InteractionManager::getInstance()->getActualMovable();
	if (touchedObject == 0) {
		return false;
	}

	std::string touchedObjectNamePart = touchedObject->getName().substr(0, 14);
	if (touchedObjectNamePart.compare("layerBookmark_") == 0) {
		return true;
	}

	return false;
}

void InsertConnectorTargetBookmark::action()
{

	Element* layerBookmark = ElementCollection::getInstance()->findElement(InteractionManager::getInstance()->getActualMovable()->getName()).first;
	Layer* activeLayer = static_cast<LayerBookmark*>(layerBookmark)->getTarget();
	InteractionManager::getInstance()->setActiveLayer(activeLayer);
	ApplicationStateManager::getInstance()->setNextState();
	DrawManager::getInstance()->hideLayersExcept(activeLayer);
	DrawManager::getInstance()->setBookmarksVisibility(false);
}

bool InsertConnectorTargetBookmark::stop() {
	return true;
}

void InsertConnectorTargetBookmark::postProcessAction() {}


