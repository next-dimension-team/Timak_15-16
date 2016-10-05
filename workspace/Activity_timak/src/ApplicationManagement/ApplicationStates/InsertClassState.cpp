/*
 * InsertClassState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "InsertClassState.h"

#include <map>
#include <typeinfo>

#include "InsertClass/FillClassDetailsState.h"
#include "InsertClass/SelectClassLayerState.h"
#include "InsertClass/SelectClassPositionState.h"

InsertClassState::InsertClassState(ApplicationState* parentState) : ApplicationState(parentState) {}

InsertClassState::~InsertClassState() {}

void InsertClassState::init() {
	this->setState(typeid(SelectClassLayerState).name());
}

void InsertClassState::setNextState() {
	currentInternalState->setNextState();
}

void InsertClassState::processButton(OIS::KeyCode key) {
	currentInternalState->processButton(key);
}

void InsertClassState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	currentInternalState->processClick(arg, id);
}

void InsertClassState::initInternalStates() {
	internalStates[typeid(SelectClassLayerState).name()] =		ApplicationState::initializator(new SelectClassLayerState(this));
	internalStates[typeid(SelectClassPositionState).name()] =	ApplicationState::initializator(new SelectClassPositionState(this));
	internalStates[typeid(FillClassDetailsState).name()] =		ApplicationState::initializator(new FillClassDetailsState(this));

	init();
}
