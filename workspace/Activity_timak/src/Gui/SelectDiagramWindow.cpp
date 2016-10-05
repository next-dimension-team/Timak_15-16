/*
 * SelectDiagramWindow.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "SelectDiagramWindow.h"

#include "MyGUI.h"
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "../ApplicationManagement/ApplicationStateManager.h"
#include "../ApplicationManagement/ApplicationStates/Message.h"
#include "MyGUI_Window.h"
#include "../ApplicationManagement/GuiManager.h"

using MyGUI::Window;


SelectDiagramWindow::SelectDiagramWindow(double width, double height)
{
    this->widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::Window>("SelectDiagramResource", 0, 0, width, height, MyGUI::Align::Default, "Main", "SelectDiagramWindow");

    this->widget->findWidget("ClassButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &SelectDiagramWindow::notifyMouseButtonClick);
    this->widget->findWidget("ActivityButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &SelectDiagramWindow::notifyMouseButtonClick);
    this->widget->findWidget("SequenceButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &SelectDiagramWindow::notifyMouseButtonClick);

}


void SelectDiagramWindow::notifyMouseButtonClick(MyGUI::Widget* _sender)
{
    if (_sender->getName() == "ClassButton")
    {
    	// TODO: Prepared for other type of diagram
        //ApplicationStateManager::getInstance()->sendMessageToState(Message(Message::Set_Class_Diagram));
    	assert("Prepared for other type of diagram");
    }
    else if (_sender->getName() == "ActivityButton")
    {
    	 ApplicationStateManager::getInstance()->sendMessageToState(Message(Message::Set_Activity_Diagram));
    }
    else if (_sender->getName() == "SequenceButton")
    {
    	ApplicationStateManager::getInstance()->sendMessageToState(Message(Message::Set_Sequence_Diagram));
        // TODO: Prepared for other type of diagram
    }
    else if (_sender->getName() == "UseCaseButton")
    {
    	assert("Prepared for other type of diagram");
        // TODO: Prepared for other type of diagram
    }
}

MyGUI::WindowPtr SelectDiagramWindow::getWidget()
{
    return this->widget;
}
