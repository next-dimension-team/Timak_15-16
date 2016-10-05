/*
 * SelectConnectorSourcePositionState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "SelectConnectorSourcePositionState.h"

#include <typeinfo>

#include "../../InteractionManager.h"
#include "../../RaycastCommands/InsertConnectorSourcePosition.h"
#include "SelectConnectorTargetLayerState.h"

#include "../ViewState.h"


SelectConnectorSourcePositionState::SelectConnectorSourcePositionState(ApplicationState* parentState) : ApplicationState(parentState) {}
SelectConnectorSourcePositionState::~SelectConnectorSourcePositionState() {}

void SelectConnectorSourcePositionState::setNextState() {
	this->setState(typeid(SelectConnectorTargetLayerState).name());
}

void SelectConnectorSourcePositionState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		this->setState(typeid(ViewState).name());
	}
}

void SelectConnectorSourcePositionState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	InteractionManager::getInstance()->rayCast(arg.state, new InsertConnectorSourcePosition());
}

void SelectConnectorSourcePositionState::initInternalStates() {
	currentInternalState = 0;
}
