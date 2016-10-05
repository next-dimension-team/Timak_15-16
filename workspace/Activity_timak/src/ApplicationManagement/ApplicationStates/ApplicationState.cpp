/*
 * ApplicationState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "ApplicationState.h"
#include <typeinfo>
#include "Message.h"

ApplicationState::ApplicationState(ApplicationState* parentState)
{
    this->parentState = parentState;
    this->initInternalStates();
}

ApplicationState::~ApplicationState()
{}

void ApplicationState::init()
{}
void ApplicationState::processButton(OIS::KeyCode key)
{}
void ApplicationState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id)
{}
void ApplicationState::setNextState()
{}

void ApplicationState::setState(std::string stateName)
{
    if (internalStates.find(stateName) == internalStates.end())
    {
        parentState->setState(stateName);
    }
    else
    {
        this->currentInternalState = internalStates[stateName];
        this->currentInternalState->init();
    }
}

ApplicationState* ApplicationState::initializator(ApplicationState* state)
{
    state->initInternalStates();
    return state;
}

void ApplicationState::processMessage(Message message)
{}

void ApplicationState::initInternalStates()
{}

