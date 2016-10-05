/*
 * FillConnectorDetailsState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "FillConnectorDetailsState.h"

#include <MyGUI_InputManager.h>
#include <MyGUI_MouseButton.h>
#include <MyGUI_Singleton.h>
#include <OISPrereqs.h>
#include <typeinfo>

#include "../../ApplicationStateManager.h"
#include "../../DiagramContexts/ClassDiagramContext.h"

#include "../ViewState.h"


FillConnectorDetailsState::FillConnectorDetailsState(ApplicationState* parentState) : ApplicationState(parentState) {}
FillConnectorDetailsState::~FillConnectorDetailsState() {}

void FillConnectorDetailsState::setNextState() {
	static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeConnectorWindow();
	this->setState(typeid(ViewState).name());
}

void FillConnectorDetailsState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeConnectorWindow();
		this->setState(typeid(ViewState).name());
	}
}

void FillConnectorDetailsState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void FillConnectorDetailsState::initInternalStates() {
	currentInternalState = 0;
}
