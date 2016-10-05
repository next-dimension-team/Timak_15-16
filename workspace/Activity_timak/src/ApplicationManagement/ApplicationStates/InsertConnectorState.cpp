/*
 * InsertConnectorState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "InsertConnectorState.h"

#include <map>
#include <typeinfo>

#include "InsertConnector/FillConnectorDetailsState.h"
#include "InsertConnector/SelectConnectorSourceLayerState.h"
#include "InsertConnector/SelectConnectorSourcePositionState.h"
#include "InsertConnector/SelectConnectorTargetLayerState.h"
#include "InsertConnector/SelectConnectorTargetPositionState.h"

InsertConnectorState::InsertConnectorState(ApplicationState* parentState) : ApplicationState(parentState) {}

InsertConnectorState::~InsertConnectorState() {}

void InsertConnectorState::init() {
	this->setState(typeid(SelectConnectorSourceLayerState).name());
}

void InsertConnectorState::setNextState() {
	currentInternalState->setNextState();
}

void InsertConnectorState::processButton(OIS::KeyCode key) {
	currentInternalState->processButton(key);
}

void InsertConnectorState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	currentInternalState->processClick(arg, id);
}

void InsertConnectorState::initInternalStates() {
	internalStates[typeid(SelectConnectorSourceLayerState).name()] =	ApplicationState::initializator(new SelectConnectorSourceLayerState(this));
	internalStates[typeid(SelectConnectorSourcePositionState).name()] =	ApplicationState::initializator(new SelectConnectorSourcePositionState(this));
	internalStates[typeid(SelectConnectorTargetLayerState).name()] =	ApplicationState::initializator(new SelectConnectorTargetLayerState(this));
	internalStates[typeid(SelectConnectorTargetPositionState).name()] =	ApplicationState::initializator(new SelectConnectorTargetPositionState(this));
	internalStates[typeid(FillConnectorDetailsState).name()] =			ApplicationState::initializator(new FillConnectorDetailsState(this));

	init();
}
