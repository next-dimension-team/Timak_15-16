/*
 * SelectConnectorTargetPositionState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "SelectConnectorTargetPositionState.h"

#include <typeinfo>

#include "../../InteractionManager.h"
#include "../../RaycastCommands/InsertConnectorTargetPosition.h"
#include "FillConnectorDetailsState.h"

#include "../ViewState.h"

SelectConnectorTargetPositionState::SelectConnectorTargetPositionState(ApplicationState* parentState) : ApplicationState(parentState) {}
SelectConnectorTargetPositionState::~SelectConnectorTargetPositionState() {}

void SelectConnectorTargetPositionState::setNextState() {
	this->setState(typeid(FillConnectorDetailsState).name());
}

void SelectConnectorTargetPositionState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		this->setState(typeid(ViewState).name());
	}
}

void SelectConnectorTargetPositionState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	InteractionManager::getInstance()->rayCast(arg.state, new InsertConnectorTargetPosition());
}

void SelectConnectorTargetPositionState::initInternalStates() {
	currentInternalState = 0;
}
