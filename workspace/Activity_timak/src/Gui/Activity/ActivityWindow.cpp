/*
 * ActivityWindow.cpp
 *
 *  Created on: 25.11.2013
 *      Author: Schade
 */

#include "ActivityWindow.h"

#include <OgreLogManager.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "MyGUI.h"
#include "../../Core/Association.h"
#include "../../Core/Aggregation.h"
#include "../../Core/Generalisation.h"
#include "../../ApplicationManagement/DataManager.h"
#include "../../ApplicationManagement/ApplicationStateManager.h"
#include "../../Core/Activity/Activity.h"
#include "../../ApplicationManagement/GuiManager.h"


ActivityWindow::ActivityWindow(double width, double height) {
	this->widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::Window>("ActivityCreateResource", 0, 0, width, height, MyGUI::Align::Center, "Main", "ActivityCreateWindow");

	this->widget->findWidget("ActivityCreateButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &ActivityWindow::notifyMouseButtonClick);
}


void ActivityWindow::notifyMouseButtonClick(MyGUI::Widget* _sender) {
	if (_sender->getName() == "ActivityCreateButton") {
		parse();

		//Activity* activity = DataManager::getInstance()->createActivity(this->container, this->activityName, this->position);

		// TODO: draw?
		//activity->draw();

		ApplicationStateManager::getInstance()->setNextState();
	}
}

MyGUI::WindowPtr ActivityWindow::getWidget() {
	return this->widget;
}

void ActivityWindow::setData(Container* container, Ogre::Vector2* position) {
	this->container = container;
	this->position = position;
}

void ActivityWindow::fillDefaultText() {
	this->activityName = "";

	this->widget->findWidget("ActivityCreateEditBox")->castType<MyGUI::EditBox>()->setCaption(this->activityName);
}

void ActivityWindow::parse() {
	this->activityName = this->widget->findWidget("ActivityCreateEditBox")->castType<MyGUI::EditBox>()->getCaption();
}


