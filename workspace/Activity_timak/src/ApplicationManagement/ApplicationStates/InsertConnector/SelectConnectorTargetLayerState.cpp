/*
 * SelectConnectorTargetLayerState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "SelectConnectorTargetLayerState.h"

#include <typeinfo>

#include "../../InteractionManager.h"
#include "../../RaycastCommands/InsertConnectorTargetBookmark.h"
#include "SelectConnectorTargetPositionState.h"

#include "../ViewState.h"


SelectConnectorTargetLayerState::SelectConnectorTargetLayerState(ApplicationState* parentState) : ApplicationState(parentState) {}
SelectConnectorTargetLayerState::~SelectConnectorTargetLayerState() {}

void SelectConnectorTargetLayerState::setNextState() {
	this->setState(typeid(SelectConnectorTargetPositionState).name());
}

void SelectConnectorTargetLayerState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		this->setState(typeid(ViewState).name());
	}
}

void SelectConnectorTargetLayerState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	InteractionManager::getInstance()->rayCast(arg.state, new InsertConnectorTargetBookmark());
}

void SelectConnectorTargetLayerState::initInternalStates() {
	currentInternalState = 0;
}
