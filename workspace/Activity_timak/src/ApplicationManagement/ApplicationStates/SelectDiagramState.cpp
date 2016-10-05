/*
 * SelectDiagramState.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "SelectDiagramState.h"
#include <iostream>
#include <OgreLogManager.h>
#include <WIN32/OgreTimerImp.h>
#include <sstream>
#include <typeinfo>

#include "../ApplicationStateManager.h"
#include "../DiagramContexts/ActivityDiagramContext.h"
#include "../Mvc/Gui.h"
#include "../DiagramContexts/ClassDiagramContext.h"
#include "../DiagramContexts/SelectDiagramContext.h"
#include "../DiagramContexts/SequenceDiagramContext.h"
#include "../DrawManager.h"
#include "../GuiManager.h"
#include "ActivityDiagramState.h"
#include "ClassDiagramState.h"
#include "SequenceDiagramState.h"


SelectDiagramState::SelectDiagramState(ApplicationState* parentState) : ApplicationState(parentState)
{}
SelectDiagramState::~SelectDiagramState()
{}


void SelectDiagramState::processMessage(Message message)
{

    //	Ogre::Timer timer = Ogre::Timer();
    //	timer.reset();
    //	unsigned long time = timer.getMillisecondsCPU();

    if (message.getEnumValue() == Message::Set_Class_Diagram)
    {
        static_cast<SelectDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeSelectDiagramWindow();
        ApplicationStateManager::getInstance()->setDiagramContext(new ClassDiagramContext());
        ApplicationStateManager::getInstance()->getDiagramContext()->activateGui();
        DrawManager::getInstance()->drawAll();
        this->setState(typeid(ClassDiagramState).name());
    }
    else if (message.getEnumValue() == Message::Set_Activity_Diagram)
    {
    	static_cast<SelectDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeSelectDiagramWindow();
        //ApplicationStateManager::getInstance()->setDiagramContext(new ActivityDiagramContext());
        ApplicationStateManager::getInstance()->setDiagramContext(new team4::Gui());
        ApplicationStateManager::getInstance()->getDiagramContext()->activateGui();
        DrawManager::getInstance()->drawAll();
        this->setState(typeid(ActivityDiagramState).name());
    }
    else if (message.getEnumValue() == Message::Set_Sequence_Diagram)
    {
    	static_cast<SelectDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext())->closeSelectDiagramWindow();
		ApplicationStateManager::getInstance()->setDiagramContext(new SequenceDiagramContext());
		ApplicationStateManager::getInstance()->getDiagramContext()->activateGui();
		DrawManager::getInstance()->drawAll();
		this->setState(typeid(SequenceDiagramState).name());
    }
    else if (message.getEnumValue() == Message::Set_Use_Case_Diagram)
    {
        // TODO: Prepared for other type of diagram
    }
    else
    {
        Ogre::LogManager::getSingleton().logMessage("SelectDiagramState: Unexisting state!!");
    }

    //	std::ostringstream os;
    //	os << "Test - drawing duration: ";
    //	os << ((double) (timer.getMillisecondsCPU() - time) / 1000);
    //	os << " sec.";
    //
    //	Ogre::LogManager::getSingleton().logMessage(os.str());
}

void SelectDiagramState::processButton(OIS::KeyCode key)
{
    if (key == OIS::KC_ESCAPE)
    {
        GuiManager::getInstance()->closeGui();
    }
}
