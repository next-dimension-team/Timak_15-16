/*
 * SelectClassPositionState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "SelectClassPositionState.h"

#include <typeinfo>

#include "../../InteractionManager.h"
#include "../../RaycastCommands/InsertClassPosition.h"
#include "FillClassDetailsState.h"

#include "../ViewState.h"


SelectClassPositionState::SelectClassPositionState(ApplicationState* parentState) : ApplicationState(parentState)
{}
SelectClassPositionState::~SelectClassPositionState()
{}

void SelectClassPositionState::setNextState()
{
    this->setState(typeid(FillClassDetailsState).name());
}

void SelectClassPositionState::processButton(OIS::KeyCode key)
{
    if (key == OIS::KC_ESCAPE)
    {
        this->setState(typeid(ViewState).name());
    }
}

void SelectClassPositionState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id)
{
    InteractionManager::getInstance()->rayCast(arg.state, new InsertClassPosition());
}

void SelectClassPositionState::initInternalStates()
{
    currentInternalState = 0;
}
