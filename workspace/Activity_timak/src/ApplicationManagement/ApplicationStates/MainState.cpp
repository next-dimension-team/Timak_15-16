/*
 * MainState.cpp
 *
 *  Created on: 6.10.2013
 *      Author: Schade
 */

#include "MainState.h"

#include <map>
#include <typeinfo>

#include "ActivityDiagramState.h"
#include "ClassDiagramState.h"
#include "SelectDiagramState.h"
#include "SequenceDiagramState.h"

MainState::MainState(ApplicationState* parentState) : ApplicationState(parentState) {}

MainState::~MainState() {}

void MainState::init() {
	this->setState(typeid(SelectDiagramState).name());
}

void MainState::setNextState() {
	currentInternalState->setNextState();
}

void MainState::processButton(OIS::KeyCode key) {
	currentInternalState->processButton(key);
}

void MainState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	currentInternalState->processClick(arg, id);
}

void MainState::initInternalStates() {
	internalStates[typeid(SelectDiagramState).name()] =			ApplicationState::initializator(new SelectDiagramState(this));
	internalStates[typeid(ClassDiagramState).name()] =			ApplicationState::initializator(new ClassDiagramState(this));
	internalStates[typeid(ActivityDiagramState).name()] =		ApplicationState::initializator(new ActivityDiagramState(this));
	internalStates[typeid(SequenceDiagramState).name()] =		ApplicationState::initializator(new SequenceDiagramState(this));

	init();
}

void MainState::processMessage(Message message) {
	currentInternalState->processMessage(message);
}
