/*
 * ActivityDiagramState.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "ActivityDiagramState.h"

#include <map>
#include <typeinfo>

#include "Activity/InsertActivityState.h"
#include "ModifyState.h"
#include "ViewState.h"


ActivityDiagramState::ActivityDiagramState(ApplicationState* parentState) : ApplicationState(parentState) {}
ActivityDiagramState::~ActivityDiagramState() {}


void ActivityDiagramState::init() {
	this->setState(typeid(ViewState).name());
}

void ActivityDiagramState::setNextState() {
	currentInternalState->setNextState();
}

void ActivityDiagramState::processButton(OIS::KeyCode key) {
	currentInternalState->processButton(key);
}

void ActivityDiagramState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	currentInternalState->processClick(arg, id);
}

void ActivityDiagramState::initInternalStates() {
	internalStates[typeid(ViewState).name()] =				ApplicationState::initializator(new ViewState(this));
	internalStates[typeid(ModifyState).name()] =			ApplicationState::initializator(new ModifyState(this));
	internalStates[typeid(InsertActivityState).name()] =	ApplicationState::initializator(new InsertActivityState(this));

	currentInternalState = 0;
}

void ActivityDiagramState::processMessage(Message message) {
	currentInternalState->processMessage(message);
}
