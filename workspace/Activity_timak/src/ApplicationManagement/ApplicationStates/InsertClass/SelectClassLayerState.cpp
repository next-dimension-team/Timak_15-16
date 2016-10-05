/*
 * SelectClassLayerState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "SelectClassLayerState.h"

#include <typeinfo>

#include "../../InteractionManager.h"
#include "../../RaycastCommands/InsertClassBookmark.h"
#include "SelectClassPositionState.h"

#include "../ViewState.h"


SelectClassLayerState::SelectClassLayerState(ApplicationState* parentState) : ApplicationState(parentState) {}
SelectClassLayerState::~SelectClassLayerState() {}

void SelectClassLayerState::setNextState() {
	this->setState(typeid(SelectClassPositionState).name());
}

void SelectClassLayerState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		this->setState(typeid(ViewState).name());
	}
}

void SelectClassLayerState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	InteractionManager::getInstance()->rayCast(arg.state, new InsertClassBookmark());
}

void SelectClassLayerState::initInternalStates() {
	currentInternalState = 0;
}
