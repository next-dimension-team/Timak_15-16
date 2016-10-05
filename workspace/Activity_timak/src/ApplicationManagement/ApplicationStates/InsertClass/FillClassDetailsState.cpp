/*
 * FillClassDetailsState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "FillClassDetailsState.h"

#include <MyGUI_InputManager.h>
#include <MyGUI_MouseButton.h>
#include <MyGUI_Singleton.h>
#include <OISPrereqs.h>
#include <typeinfo>

#include "../../ApplicationStateManager.h"
#include "../../DiagramContexts/ClassDiagramContext.h"

#include "../ViewState.h"


FillClassDetailsState::FillClassDetailsState(ApplicationState* parentState) : ApplicationState(parentState) {}
FillClassDetailsState::~FillClassDetailsState() {}

void FillClassDetailsState::setNextState() {
	static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeClassWindow();
	this->setState(typeid(ViewState).name());
}

void FillClassDetailsState::processButton(OIS::KeyCode key) {
	if (key == OIS::KC_ESCAPE) {
		static_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeClassWindow();
		this->setState(typeid(ViewState).name());
	}
}

void FillClassDetailsState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id) {
	MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void FillClassDetailsState::initInternalStates() {
	currentInternalState = 0;
}
