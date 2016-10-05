/*
 * Popup.cpp
 *
 *  Created on: 16.12.2013
 *      Author: Schade
 */

#include "Popup.h"
#include "../../ApplicationManagement/GuiManager.h"
#include "MyGUI.h"
#include "../../ApplicationManagement/ApplicationStates/Message.h"
#include "../../ApplicationManagement/ApplicationStateManager.h"
#include <OISMouse.h>
#include "../../ApplicationManagement/Mvc/Gui.h"

using MyGUI::MenuItemType;

MyGUI::PopupMenu* Popup::widget = 0;
int Popup::x = -1;
int Popup::y = -1;

Popup::Popup()
{
    // TODO Auto-generated constructor stub
}

Popup::~Popup()
{
    // TODO Auto-generated destructor stub
}

void Popup::displayPopup(int x, int y)
{
    Popup::widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::PopupMenu>("PopupMenu", x - 5, y - 5, 30, 50, MyGUI::Align::Default, "Overlapped");

    Popup::widget->eventMouseLostFocus.clear();
    Popup::widget->eventMouseLostFocus += MyGUI::newDelegate(Popup::lostFocus);

    Popup::x = x;
    Popup::y = y;

    MyGUI::MenuItem* mi = 0;
    /*mi = Popup::widget->addItem("Insert");
    mi->eventMouseButtonClick += MyGUI::newDelegate(Popup::notifyMouseButtonClick);
    mi->setUserString("ident", "INS");
    mi = Popup::widget->addItem("Modify");
    mi->eventMouseButtonClick += MyGUI::newDelegate(Popup::notifyMouseButtonClick);
    mi->setUserString("ident", "MOD");*/
    mi = Popup::widget->addItem("Delete");
    mi->eventMouseButtonClick += MyGUI::newDelegate(Popup::notifyMouseButtonClick);
    mi->setUserString("ident", "DEL");
}

bool Popup::isActive()
{
    return (Popup::widget != 0 && Popup::widget->isVisible());
}

void Popup::lostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
{
    // TODO: memory leak - destroy widget or (better) reuse it
    Popup::widget->setEnabled(false);
    Popup::widget->setVisibleSmooth(false);
}

void Popup::notifyMouseButtonClick(MyGUI::Widget* _sender)
{
    if (_sender->getUserString("ident") == "INS")
    {
        ApplicationStateManager::getInstance()->sendMessageToState(Message(Message::Popup_Insert));
    }
    else if (_sender->getUserString("ident") == "MOD")
    {
        ApplicationStateManager::getInstance()->sendMessageToState(Message(Message::Popup_Modify));
    }
    else if (_sender->getUserString("ident") == "DEL")
    {
    	std::cout << "mazem" << std::endl;
    	team4::Gui* ctxActivity = dynamic_cast<team4::Gui*>(ApplicationStateManager::getInstance()->getDiagramContext());
    	ctxActivity->DeleteSelecedItems();
        //ApplicationStateManager::getInstance()->sendMessageToState(Message(Message::Popup_Delete));
    }
}

OIS::MouseState Popup::getMouseState()
{
    OIS::MouseState ms = OIS::MouseState();
    ms.X.abs = Popup::x;
    ms.Y.abs = Popup::y;
    return ms;
}
