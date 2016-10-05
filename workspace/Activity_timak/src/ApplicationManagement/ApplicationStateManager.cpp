/*
 * ApplicationStateManager.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "ApplicationStateManager.h"

#include "ApplicationStates/MainState.h"
#include "ApplicationStates/Message.h"
#include "DiagramContexts/DiagramContext.h"

ApplicationStateManager* ApplicationStateManager::singletonObject = 0;


ApplicationStateManager::ApplicationStateManager()
{
    this->readyToShutdown = false;
    this->context = 0;
    this->mainState = 0;
}

ApplicationStateManager::~ApplicationStateManager()
{
}

ApplicationStateManager* ApplicationStateManager::getInstance()
{
    if (ApplicationStateManager::singletonObject == 0)
    {
        singletonObject = new ApplicationStateManager();

        singletonObject->mainState = ApplicationState::initializator(new MainState(0));
    }

    return singletonObject;
}

void ApplicationStateManager::processPressedButton(OIS::KeyCode key)
{
    mainState->processButton(key);
}

bool ApplicationStateManager::isReadyToShutdown()
{
    return this->readyToShutdown;
}

void ApplicationStateManager::setReadyToShutdown(bool readyToShutdown)
{
    this->readyToShutdown = readyToShutdown;
}

void ApplicationStateManager::processClickedMouse(OIS::MouseEvent arg, OIS::MouseButtonID id)
{
    mainState->processClick(arg, id);
}

void ApplicationStateManager::setNextState()
{
    return mainState->setNextState();
}

void ApplicationStateManager::sendMessageToState(Message message)
{
    mainState->processMessage(message);
}

void ApplicationStateManager::update(double deltaTime)
{
}

DiagramContext* ApplicationStateManager::getDiagramContext()
{
    return this->context;
}

void ApplicationStateManager::setDiagramContext(DiagramContext* context)
{
    if (this->context != 0)
    {
        this->context->releaseContent();
    }
    this->context = context;
    this->context->initContent();
}
