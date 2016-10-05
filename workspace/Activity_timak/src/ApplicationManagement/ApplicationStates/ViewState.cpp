/*
 * ViewState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "ViewState.h"

#include <typeinfo>

#include "../ApplicationStateManager.h"
#include "../DiagramContexts/SelectDiagramContext.h"
#include "../DrawManager.h"
#include "../GuiManager.h"
#include "ModifyState.h"
#include "SelectDiagramState.h"


ViewState::ViewState(ApplicationState* parentState) : ApplicationState(parentState) {}
ViewState::~ViewState() {}

void ViewState::init() {
	GuiManager::getInstance()->hideCursor();
	DrawManager::getInstance()->showLayers();
	DrawManager::getInstance()->setBookmarksVisibility(false);
}

void ViewState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_SPACE) {
		this->setState(typeid(ModifyState).name());
	} else if (key == OIS::KC_ESCAPE) {
		ApplicationStateManager::getInstance()->setDiagramContext(new SelectDiagramContext());
		ApplicationStateManager::getInstance()->getDiagramContext()->activateGui();
		this->setState(typeid(SelectDiagramState).name());
	}
}

void ViewState::initInternalStates() {
	currentInternalState = 0;
}
