/*
 * SequenceDiagramState.cpp
 *
 *  Created on: Nov 8, 2015
 *      Author: Matej
 */

#include "SequenceDiagramState.h"
#include "ModifyState.h"
#include "ViewState.h"

#include <typeinfo>

SequenceDiagramState::SequenceDiagramState(ApplicationState* parentState) : ApplicationState(parentState){

}

SequenceDiagramState::~SequenceDiagramState() {
	// TODO Auto-generated destructor stub
}


void SequenceDiagramState::init() {
	this->setState(typeid(ViewState).name());
}

void SequenceDiagramState::setNextState() {
	currentInternalState->setNextState();
}

void SequenceDiagramState::processButton(OIS::KeyCode key) {
	currentInternalState->processButton(key);
}

void SequenceDiagramState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	currentInternalState->processClick(arg, id);
}

void SequenceDiagramState::initInternalStates() {
	internalStates[typeid(ViewState).name()] =				ApplicationState::initializator(new ViewState(this));
	internalStates[typeid(ModifyState).name()] =			ApplicationState::initializator(new ModifyState(this));
	currentInternalState = 0;
}

void SequenceDiagramState::processMessage(Message message) {
	currentInternalState->processMessage(message);
}
