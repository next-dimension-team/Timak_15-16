/*
 * InsertClassBookmark.cpp
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#include "InsertClassBookmark.h"

#include <OgreMovableObject.h>
#include <string>

#include "../../Core/LayerBookmark.h"
#include "../ApplicationStateManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../InteractionManager.h"
#include "../../Core/Metamodel/include/Element.h"


InsertClassBookmark::InsertClassBookmark() {}

InsertClassBookmark::~InsertClassBookmark() {}

bool InsertClassBookmark::conditionsAccepted() {
	return true;
}

bool InsertClassBookmark::check() {
	return (InteractionManager::getInstance()->getActualMovable() && InteractionManager::getInstance()->getActualMovable()->getName().substr(0, 14).compare("layerBookmark_") == 0);
}

void InsertClassBookmark::action()
{
	std::pair<Element*, team4::MetamodelElement*> elements = ElementCollection::getInstance()->findElement(InteractionManager::getInstance()->getActualMovable()->getName());
	Element* layerBookmark = elements.first;
	Layer* activeLayer = static_cast<LayerBookmark*>(layerBookmark)->getTarget();
	InteractionManager::getInstance()->setActiveLayer(activeLayer);
	ApplicationStateManager::getInstance()->setNextState();
	DrawManager::getInstance()->hideLayersExcept(activeLayer);
	DrawManager::getInstance()->setBookmarksVisibility(false);
}

bool InsertClassBookmark::stop() {
	return true;
}

void InsertClassBookmark::postProcessAction() {}



