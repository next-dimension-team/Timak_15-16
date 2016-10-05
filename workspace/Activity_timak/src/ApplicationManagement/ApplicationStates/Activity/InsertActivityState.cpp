/*
 * InsertActivityState.cpp
 *
 *  Created on: 17.2.2014
 *      Author: Schade
 */

#include "InsertActivityState.h"

#include <MyGUI_InputManager.h>
#include <MyGUI_MouseButton.h>
#include <MyGUI_Singleton.h>
#include <OISPrereqs.h>
#include <typeinfo>

#include "../../../Gui/Activity/Popup.h"
#include "../../ApplicationStateManager.h"
#include "../../DiagramContexts/ActivityDiagramContext.h"
#include "../../Mvc/Gui.h"
#include "../../InteractionManager.h"
#include "../../RaycastCommands/Activity/InsertActivityPosition.h"

#include "../ViewState.h"


InsertActivityState::InsertActivityState(ApplicationState* parentState) : ApplicationState(parentState)
{}
InsertActivityState::~InsertActivityState()
{}

void InsertActivityState::init()
{
    InteractionManager::getInstance()->setActiveContainer(0);
    InteractionManager::getInstance()->rayCast(Popup::getMouseState(), new InsertActivityPosition());

    // if no container was raycasted
    if (InteractionManager::getInstance()->getActiveContainer() == 0)
    {
        setNextState();
    }
}

void InsertActivityState::setNextState()
{
    //static_cast<ActivityDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeActivityWindow();
    static_cast<team4::Gui*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeActivityWindow();

    this->setState(typeid(ViewState).name());
}

void InsertActivityState::processButton(OIS::KeyCode key)
{
    if (key == OIS::KC_ESCAPE)
    {
    	static_cast<team4::Gui*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeActivityWindow();
        //static_cast<ActivityDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeActivityWindow();
        this->setState(typeid(ViewState).name());
    }
}

void InsertActivityState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id)
{
    MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void InsertActivityState::initInternalStates()
{
    currentInternalState = 0;
}
