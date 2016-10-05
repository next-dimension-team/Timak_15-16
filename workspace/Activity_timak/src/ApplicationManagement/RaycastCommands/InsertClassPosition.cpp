/*
 * InsertClassPosition.cpp
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#include "InsertClassPosition.h"

#include <MyGUI_PointerManager.h>
#include <MyGUI_Singleton.h>
#include <MyGUI_Window.h>
#include <OgreMovableObject.h>
#include <OgreRay.h>
#include <OgreSceneNode.h>
#include <OgreSceneQuery.h>
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <string>

#include "../../Core/Layer.h"
#include "../../Graphics/ElementGraphics.h"
#include "../../Gui/ClassWindow.h"
#include "../ApplicationStateManager.h"
#include "../DiagramContexts/ClassDiagramContext.h"
#include "../DrawManager.h"
#include "../GuiManager.h"
#include "../InteractionManager.h"

InsertClassPosition::InsertClassPosition() {}

InsertClassPosition::~InsertClassPosition() {}

bool InsertClassPosition::conditionsAccepted() {
	return (InteractionManager::getInstance()->getActiveLayer() != 0) ? true : false;
}

bool InsertClassPosition::check() {
	return (InteractionManager::getInstance()->getActualMovable() && InteractionManager::getInstance()->getActualMovable()->getName().compare(InteractionManager::getInstance()->getActiveLayer()->getName()) == 0);
}

void InsertClassPosition::action() {
	Ogre::Vector3 worldPos = InteractionManager::getInstance()->getRay().getPoint(InteractionManager::getInstance()->getRayResultIterator()->distance);
	Ogre::Vector3 localPos = InteractionManager::getInstance()->getActiveLayer()->getGraphics()->getSceneNode()->convertWorldToLocalPosition(worldPos);

	ApplicationStateManager::getInstance()->setNextState();
	GuiManager::getInstance()->hideOldCursor(); // temporary - hides only old cursor, but new appears
	ClassDiagramContext* ctx = static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext());
	ctx->getWindowClass()->setData(InteractionManager::getInstance()->getActiveLayer(), new Ogre::Vector2(localPos.x, localPos.y));
	ctx->getWindowClass()->fillDefaultText();
	ctx->getWindowClass()->getWidget()->setVisible(true);
	MyGUI::PointerManager::getInstance().setVisible(true);

	DrawManager::getInstance()->showLayers();
}

bool InsertClassPosition::stop() {
	return true;
}

void InsertClassPosition::postProcessAction() {}

