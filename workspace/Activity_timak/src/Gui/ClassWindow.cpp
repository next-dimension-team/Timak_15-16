/*
 * ClassWindow.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#include "ClassWindow.h"

#include "MyGUI.h"
#include <OgreLogManager.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "../Core/Class.h"
#include "../ApplicationManagement/DataManager.h"
#include "../ApplicationManagement/ApplicationStateManager.h"
#include "MyGUI_Window.h"
#include "../ApplicationManagement/GuiManager.h"

using MyGUI::Window;


ClassWindow::ClassWindow(double width, double height)
{
    this->widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::Window>("ClassCreateResource", 0, 0, width, height, MyGUI::Align::Default, "Main", "ClassCreateWindow");

    this->widget->findWidget("ClassCreateButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &ClassWindow::notifyMouseButtonClick);
    //	this->widget->eventWindowButtonPressed += newDelegate(this, &ClassWindow::notifyWindowClose);
}


// TODO: not working!!
void ClassWindow::notifyWindowClose(MyGUI::Window* _sender, const std::string& _button)
{
    Ogre::LogManager::getSingleton().logMessage("NWMBC-1");
    if (_button == "close")
    {
        Ogre::LogManager::getSingleton().logMessage("NWMBC-2");
        this->widget->setVisible(false);
    }
}

void ClassWindow::notifyMouseButtonClick(MyGUI::Widget* _sender)
{
    if (_sender->getName() == "ClassCreateButton")
    {
        parse();

        Class* cla = DataManager::getInstance()->createClass(this->layer, this->className, this->position);

        unsigned int i;
        for(i = 0; i < this->attributes.size(); i++)
        {
            DataManager::getInstance()->createAttribute(cla, this->attributes[i]);
        }

        for(i = 0; i < this->methods.size(); i++)
        {
            DataManager::getInstance()->createMethod(cla, this->methods[i]);
        }

        // TODO: draw?
        //cla->draw();

        ApplicationStateManager::getInstance()->setNextState();
    }
}

MyGUI::WindowPtr ClassWindow::getWidget()
{
    return this->widget;
}

void ClassWindow::fillDefaultText()
{
    this->className = "";
    this->attributes.clear();
    this->methods.clear();

    std::ostringstream os;
    os << "New class\n";
    os << ">>A\n";
    os << "owner: String\n";
    os << "balance: Euro\n";
    os << "insufficientFundsFee: Euro\n";
    os << ">>M\n";
    os << "processCheck (checkToProcess : Check)\n";
    os << "deposit (amount : Euro)\n";
    os << "withdrawal (amount : Euro)";

    this->widget->findWidget("ClassCreateEditBox")->castType<MyGUI::EditBox>()->setCaption(os.str());
}

void ClassWindow::setData(Layer* layer, Ogre::Vector2* position)
{
    this->layer = layer;
    this->position = position;
}

void ClassWindow::parse()
{
    std::string s = this->widget->findWidget("ClassCreateEditBox")->castType<MyGUI::EditBox>()->getCaption();
    s = s.append("\n");

    int nlPos = s.find("\n");
    this->className = s.substr(0, nlPos);

    std::string attribute;
    if (s.find(">>A\n") != std::string::npos)
    {
        int attPos = s.find(">>A\n") + 4;
        while (s.find("\n", attPos) < s.find(">>M\n") && s.find("\n", attPos) < s.length())
        {
            nlPos = s.find("\n", attPos);

            attribute = s.substr(attPos, nlPos - attPos);
            attPos = nlPos + 1;
            if (attribute.length() < 1)
                break;

            this->attributes.push_back(attribute);
        }
    }

    if (s.find(">>M\n") != std::string::npos)
    {
        std::string method;
        int metPos = s.find(">>M\n") + 4;
        while (s.find("\n", metPos) < s.length())
        {
            nlPos = s.find("\n", metPos);

            method = s.substr(metPos, nlPos - metPos);
            metPos = nlPos + 1;
            if (method.length() < 1)
                break;

            this->methods.push_back(method);
        }
    }
}

