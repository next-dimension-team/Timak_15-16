/*
 * SelectConnectorSourceLayerState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "SelectConnectorSourceLayerState.h"

#include <typeinfo>

#include "../../InteractionManager.h"
#include "../../RaycastCommands/InsertConnectorSourceBookmark.h"
#include "SelectConnectorSourcePositionState.h"

#include "../ViewState.h"


SelectConnectorSourceLayerState::SelectConnectorSourceLayerState(ApplicationState* parentState) : ApplicationState(parentState) {}
SelectConnectorSourceLayerState::~SelectConnectorSourceLayerState() {}

void SelectConnectorSourceLayerState::setNextState() {
	this->setState(typeid(SelectConnectorSourcePositionState).name());
}

void SelectConnectorSourceLayerState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		this->setState(typeid(ViewState).name());
	}
}

void SelectConnectorSourceLayerState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	InteractionManager::getInstance()->rayCast(arg.state, new InsertConnectorSourceBookmark());
}

void SelectConnectorSourceLayerState::initInternalStates() {
	currentInternalState = 0;
}
