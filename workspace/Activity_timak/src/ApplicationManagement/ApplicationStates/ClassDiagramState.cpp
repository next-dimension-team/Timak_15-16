/*
 * ClassDiagramState.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "ClassDiagramState.h"

#include <map>
#include <typeinfo>

#include "InsertClassState.h"
#include "InsertConnectorState.h"
#include "ModifyState.h"
#include "ViewState.h"


ClassDiagramState::ClassDiagramState(ApplicationState* parentState) : ApplicationState(parentState) {}
ClassDiagramState::~ClassDiagramState() {}

void ClassDiagramState::init() {
	this->setState(typeid(ViewState).name());
}

void ClassDiagramState::setNextState() {
	currentInternalState->setNextState();
}

void ClassDiagramState::processButton(OIS::KeyCode key) {
	currentInternalState->processButton(key);
}

void ClassDiagramState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	currentInternalState->processClick(arg, id);
}

void ClassDiagramState::initInternalStates() {
	internalStates[typeid(ViewState).name()] =				ApplicationState::initializator(new ViewState(this));
	internalStates[typeid(ModifyState).name()] =			ApplicationState::initializator(new ModifyState(this));
	internalStates[typeid(InsertClassState).name()] =		ApplicationState::initializator(new InsertClassState(this));
	internalStates[typeid(InsertConnectorState).name()] =	ApplicationState::initializator(new InsertConnectorState(this));

	currentInternalState = 0;
}
